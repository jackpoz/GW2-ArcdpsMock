#pragma once
#include "Library.h"
#include <CrossplatformMocks/Module.h>
#include <vector>

class LibrariesManager
{
public:
    LibrariesManager();
    ~LibrariesManager();

    void LoadLibrary(const char* path);
    void UnloadLibraries();
private:
    template <typename T>
    T GetFunctionAddress(LibraryHandle handle, const char* functionName);

    std::vector<Library> libraries;
};
