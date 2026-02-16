#pragma once
#include "Library.h"
#include "CombatLogManager.h"
#include <CrossplatformMocks/Module.h>
#include <imgui/imgui.h>
#include <vector>

class LibrariesManager
{
public:
    LibrariesManager();
    ~LibrariesManager();

    void LoadLibrary(const char* path);
    void InitLibraries();
    void UIUpdate();
    bool LoadCombatLog(const char* logPath);
    void RunCombatLog(uint32_t threads = 0);
    void UnloadLibraries();
private:
    template <typename T>
    T GetFunctionAddress(LibraryHandle handle, const char* functionName);
    void SetupMockImGui();
    void CallModRelease();
    void CallDestroyImGuiContext();
    void CallUnloadLibraries();

    ImGuiContext* imguiContext;
    std::vector<Library> libraries;
    CombatLogManager combatLogManager;
};
