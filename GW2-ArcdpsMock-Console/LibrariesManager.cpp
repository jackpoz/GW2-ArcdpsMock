#include "LibrariesManager.h"
#include <cstdlib>

LibrariesManager::LibrariesManager() : combatLogManager()
{
    imguiContext = ImGui::CreateContext();
    SetupMockImGui();
}

LibrariesManager::~LibrariesManager()
{
}

void LibrariesManager::LoadLibrary(const char* path)
{
#ifdef _WIN32
    LibraryHandle handle = ::LoadLibraryA(path);
    LibraryHandle selfHandle = GetModuleHandle(NULL);
    // ToDo: implement this and change to 11
    int dxMode = 0;
#else
    LibraryHandle handle = dlopen(path, RTLD_LAZY);
    LibraryHandle selfHandle = dlopen(NULL, RTLD_LAZY);
    // ToDo: implement this as magic numbers for linux
    int dxMode = -1;
#endif

    if (handle != nullptr)
    {
        Library library{};
        library.Handle = handle;
        library.GetInit = GetFunctionAddress<GetInitAddrSignature>(handle, "get_init_addr");
        library.GetRelease = GetFunctionAddress<GetReleaseAddrSignature>(handle, "get_release_addr");

        void* swapChain = nullptr;
        library.Init = library.GetInit("GW2-ArcdpsMock", ImGui::GetCurrentContext(), (void*)swapChain, selfHandle, malloc, free, dxMode);

        libraries.push_back(library);
    }
}

void LibrariesManager::InitLibraries()
{
    for (Library& library : libraries)
    {
        library.Exports = library.Init();
    }
}

void LibrariesManager::SetupMockImGui()
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(100, 100);
    io.Fonts->AddFontDefault();
    io.Fonts->Build();
}

void LibrariesManager::UIUpdate()
{
    ImGui::NewFrame();
    for (Library& library : libraries)
    {
        if (library.Exports->imgui != nullptr)
        {
            library.Exports->imgui(true, false);
        }
    }
    ImGui::EndFrame();
    ImGui::Render();
}

bool LibrariesManager::LoadCombatLog(const char* logPath)
{
    return combatLogManager.LoadLog(logPath) == 0;
}

void LibrariesManager::RunCombatLog(uint32_t threads)
{
    if (threads == 0)
    {
        threads = 1;
    }

    std::vector<arcdps_exports> exports;
    for (const auto& library : libraries)
    {
        exports.push_back(*library.Exports);
    }

    combatLogManager.RunCombatLog(threads, exports);
}

void LibrariesManager::UnloadLibraries()
{
    for (const auto& library : libraries)
    {
        auto release = library.GetRelease();
        release();
    }

    // ToDo: re-enable this
    //ImGui::DestroyContext();

    for (const auto& library : libraries)
    {
        // ToDo: re-enable this
        /*
#ifdef _WIN32
        ::FreeLibrary(library.Handle);
#else
        dlclose(library.Handle);
#endif
        */
    }

    libraries.clear();
}

template<typename T>
T LibrariesManager::GetFunctionAddress(LibraryHandle handle, const char* functionName)
{
#ifdef _WIN32
    return reinterpret_cast<T>(::GetProcAddress(handle, functionName));
#else
    return reinterpret_cast<T>(dlsym(handle, functionName));
#endif
}
