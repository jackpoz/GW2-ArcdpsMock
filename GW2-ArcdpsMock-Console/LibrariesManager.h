#pragma once
#include "Library.h"
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
    void UnloadLibraries();
private:
    template <typename T>
    T GetFunctionAddress(LibraryHandle handle, const char* functionName);

    ImGuiContext* imguiContext;
    std::vector<Library> libraries;
};
