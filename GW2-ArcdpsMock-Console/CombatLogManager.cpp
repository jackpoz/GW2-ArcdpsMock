#include "CombatLogManager.h"
#include <cassert>
#include <cstring>
#include <memory>
#include <thread>

#define LOG(...)

CombatLogManager::CombatLogManager() : combatLogHeader(), combatLogEventQueue(nullptr)
{
}

CombatLogManager::~CombatLogManager()
{
}

// Copied from https://github.com/Krappa322/arcdps_mock/blob/master/arcdps_mock/CombatMock.cpp
bool CombatLogManager::IsSelfAgentDeregister(XevtcEvent& pEvent)
{
	return pEvent.ev.present == false && pEvent.source_ag.elite == 0 && pEvent.source_ag.prof == 0 && pEvent.destination_ag.self != 0;
}

uint32_t CombatLogManager::LoadLog(const char* path)
{
	events.clear();
	xevtcStrings.clear();

	const char* pFilePath = path;
	std::vector<std::string> mXevtcStrings;
	uint32_t pMaxFuzzWidth = 0;

    // Copied from https://github.com/Krappa322/arcdps_mock/blob/master/arcdps_mock/CombatMock.cpp
	std::string buffer;
	buffer.reserve(128 * 1024);

	FILE* file = fopen(pFilePath, "rb");
	if (file == nullptr)
	{
		LOG("Opening '%s' failed - %u", pFilePath, errno);
		return errno;
	}

	XevtcHeader header;
	size_t read = fread(&header, sizeof(header), 1, file);
	if (ferror(file) != 0)
	{
		LOG("Reading header from '%s' failed - %u", pFilePath, errno);
		return errno;
	}
	else if (read != 1)
	{
		LOG("Reading header from '%s' failed - file is too short (read %zu)", pFilePath, read);
		return UINT32_MAX;
	}

	mXevtcStrings.clear();
	mXevtcStrings.reserve(header.StringCount);
	for (uint32_t i = 0; i < header.StringCount; i++)
	{
		uint16_t size;
		read = fread(&size, sizeof(size), 1, file);
		if (ferror(file) != 0)
		{
			LOG("Reading string header %u from '%s' failed - %u", i, pFilePath, errno);
			return errno;
		}
		else if (read != 1)
		{
			LOG("Reading string header %u from '%s' failed - file is too short (read %zu)", i, pFilePath, read);
			return UINT32_MAX;
		}

		std::string& newString = mXevtcStrings.emplace_back();
		newString.resize(size);

		if (size != 0) // null strings are allowed in the xevtc
		{
			read = fread(newString.data(), size, 1, file);
			if (ferror(file) != 0)
			{
				LOG("Reading string data %u (size %hu) from '%s' failed - %u", i, size, pFilePath, errno);
				return errno;
			}
			else if (read != 1)
			{
				LOG("Reading string data %u (size %hu) from '%s' failed - file is too short (read %zu)", i, size, pFilePath, read);
				return UINT32_MAX;
			}
		}

		LOG("Parsed string %u %hu %s", i, size, newString.c_str());
	}

	auto eventsVector = std::make_unique<XevtcEvent[]>(header.EventCount);
	read = fread(eventsVector.get(), sizeof(XevtcEvent), header.EventCount, file);
	if (ferror(file) != 0)
	{
		LOG("Reading events (size %hu) from '%s' failed - %u", header.EventCount, pFilePath, errno);
		return errno;
	}
	else if (read != header.EventCount)
	{
		LOG("Reading events (size %hu) from '%s' failed - file is too short (read %zu)", header.EventCount, pFilePath, read);
		return UINT32_MAX;
	}

	if (fclose(file) == EOF)
	{
		LOG("Closing '%s' failed - %u", pFilePath, errno);
		return errno;
	}

	auto queuedEvents = std::make_unique<bool[]>(header.EventCount);
	memset(queuedEvents.get(), 0x00, header.EventCount * sizeof(bool));
	uint32_t queuedEventCount = 0;

	bool sentFirstEvent = false;

	auto eventQueue = std::make_unique<XevtcEvent[]>(header.EventCount);
	std::vector<uint32_t> junctions;

	uint32_t globalIndex = 0;
	while (globalIndex < header.EventCount)
	{
		// Use UINT64_MAX as a marker to determine if events have been sent
		if (queuedEvents[globalIndex] == true)
		{
			globalIndex++;
			continue;
		}

		uint32_t fuzzSize = 0;
		if (pMaxFuzzWidth > 0 && sentFirstEvent == true)
		{
			fuzzSize = rand() % (pMaxFuzzWidth + 1);
		}

		uint32_t localIndex = globalIndex;
		while ((localIndex + 1) < header.EventCount && localIndex < (globalIndex + fuzzSize))
		{
			if (IsSelfAgentDeregister(eventsVector[localIndex]) == true)
			{
				break;
			}
			localIndex++;
		}

		while (queuedEvents[localIndex] == true)
		{
			assert(localIndex > globalIndex);
			localIndex--;
		}
		assert(queuedEvents[localIndex] == false);

		memcpy(&eventQueue[queuedEventCount], &eventsVector[localIndex], sizeof(eventQueue[queuedEventCount]));
		if (IsSelfAgentDeregister(eventsVector[localIndex]) == true)
		{
			junctions.push_back(queuedEventCount);
		}
		else if (eventsVector[localIndex].id != 0 && sentFirstEvent == false)
		{
			junctions.push_back(queuedEventCount);
			sentFirstEvent = true;
		}

		queuedEvents[localIndex] = true;
		queuedEventCount += 1;
	}

    combatLogHeader = header;
    xevtcStrings = std::move(mXevtcStrings);
	combatLogEventQueue = std::move(eventQueue);

	return 0;

}

void CombatLogManager::RunCombatLog(uint32_t threads, const std::vector<arcdps_exports>& exports)
{
	uint32_t threadsCount = threads;
	XevtcHeader& header = combatLogHeader;
    std::vector<std::string>& mXevtcStrings = xevtcStrings;
	std::unique_ptr<XevtcEvent[]>& eventQueue = combatLogEventQueue;

	// Partially copied from https://github.com/Krappa322/arcdps_mock/blob/master/arcdps_mock/CombatMock.cpp

	std::vector<std::vector<XevtcEvent>> threadEventQueues;
	threadEventQueues.resize(threadsCount);

	for (uint32_t i = 0; i < threadsCount; i++)
	{
		threadEventQueues[i].reserve(header.EventCount / threadsCount + 1);
	}

	// Split the events
	for (uint32_t i = 0; i < header.EventCount; i++)
	{
		uint32_t threadIndex = i % threadsCount;
		threadEventQueues[threadIndex].push_back(eventQueue[i]);
	}

	std::vector<std::vector<XevtcEvent>> eventQueues = std::move(threadEventQueues);
	std::vector<std::thread> workers;
	for (uint32_t i = 0; i < threadsCount; i++)
	{
		auto worker = std::thread([this, &eventQueue = eventQueues[i], &mXevtcStrings, &exports]() {
			for (uint32_t i = 0; i < eventQueue.size(); i++)
			{
				ExecuteXevtcEvent(eventQueue.at(i), mXevtcStrings, exports);
				std::this_thread::sleep_for(std::chrono::milliseconds(0));
			}
			});
		workers.emplace_back(std::move(worker));
	}

	for (auto& worker : workers)
	{
		worker.join();
	}
}

void CombatLogManager::ExecuteXevtcEvent(const XevtcEvent& pEvent, const std::vector<std::string>& pStrings, const std::vector<arcdps_exports>& exports)
{
	// Copied from https://github.com/Krappa322/arcdps_mock/blob/master/arcdps_mock/CombatMock.cpp
	ag source;
	ag destination;
	cbtevent ev;

	ag* source_arg = nullptr;
	ag* destination_arg = nullptr;
	cbtevent* ev_arg = nullptr;
	const char* skillname = nullptr;

	if (pEvent.ev.present == true)
	{
		ev = *static_cast<const cbtevent*>(&pEvent.ev);
		ev_arg = &ev;
	}

	if (pEvent.source_ag.present == true)
	{
		source.id = pEvent.source_ag.id;
		source.prof = pEvent.source_ag.prof;
		source.elite = pEvent.source_ag.elite;
		source.self = pEvent.source_ag.self;
		if (pEvent.source_ag.name.Index != UINT32_MAX)
		{
			source.name = pStrings[pEvent.source_ag.name.Index - 1].c_str();
		}
		else
		{
			source.name = nullptr;
		}
		source.team = pEvent.source_ag.team;

		source_arg = &source;
	}

	if (pEvent.destination_ag.present == true)
	{
		destination.id = pEvent.destination_ag.id;
		destination.prof = pEvent.destination_ag.prof;
		destination.elite = pEvent.destination_ag.elite;
		destination.self = pEvent.destination_ag.self;
		if (pEvent.destination_ag.name.Index != UINT32_MAX)
		{
			destination.name = pStrings[pEvent.destination_ag.name.Index - 1].c_str();
		}
		else
		{
			destination.name = nullptr;
		}
		destination.team = pEvent.destination_ag.team;

		destination_arg = &destination;
	}

	if (pEvent.skillname.Index != UINT32_MAX)
	{
		skillname = pStrings[pEvent.skillname.Index - 1].c_str();
	}

	// Change from https://github.com/Krappa322/arcdps_mock/blob/master/arcdps_mock/CombatMock.cpp
	for (const auto& pCallbacks : exports)
	{
		switch (pEvent.collector_source)
		{
		case XevtcEventSource::Area:
			if (pCallbacks.combat != nullptr)
			{
				pCallbacks.combat(ev_arg, source_arg, destination_arg, skillname, pEvent.id, pEvent.revision);
			}
			break;
		case XevtcEventSource::Local:
			if (pCallbacks.combat_local != nullptr)
			{
				pCallbacks.combat_local(ev_arg, source_arg, destination_arg, skillname, pEvent.id, pEvent.revision);
			}
			break;
		default:
			LOG("Invalid event source %u", pEvent.collector_source);
			break;
		}
	}
}

