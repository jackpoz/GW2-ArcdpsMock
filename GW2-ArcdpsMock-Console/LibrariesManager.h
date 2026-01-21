#pragma once

#ifdef _WIN32
#include <Windows.h>
typedef HMODULE LibraryHandle;
#else
#include <dlfcn.h>
typedef void* LibraryHandle;
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
    std::vector<LibraryHandle> libraries;
};
