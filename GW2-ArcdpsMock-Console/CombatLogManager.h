#pragma once
#include "Xevtc.h"
#include <memory>
#include <string>
#include <vector>

class CombatLogManager
{
public:
    CombatLogManager();
    ~CombatLogManager();

    uint32_t LoadLog(const char* path);
    void RunCombatLog(uint32_t threads, const std::vector<arcdps_exports>& exports);
private:
    bool IsSelfAgentDeregister(XevtcEvent& pEvent);
    void ExecuteXevtcEvent(const XevtcEvent& pEvent, const std::vector<std::string>& pStrings, const std::vector<arcdps_exports>& exports);

    std::vector<XevtcEvent> events;
    std::vector<std::string> xevtcStrings;
    XevtcHeader combatLogHeader;
    std::unique_ptr<XevtcEvent[]> combatLogEventQueue;
};
