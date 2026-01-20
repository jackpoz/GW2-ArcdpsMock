#pragma once

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include <vector>

class LibrariesManager
{
public:
    LibrariesManager();
    ~LibrariesManager();

    void LoadLibrary(const char* path);
    void UnloadLibraries();
private:
#ifdef _WIN32
    std::vector<HMODULE> libraries;
#else
    std::vector<void*> libraries;
#endif
};
