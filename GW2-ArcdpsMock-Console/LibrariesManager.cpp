#include "LibrariesManager.h"

LibrariesManager::LibrariesManager()
{
}

LibrariesManager::~LibrariesManager()
{
    UnloadLibraries();
}

void LibrariesManager::LoadLibrary(const char* path)
{
#ifdef _WIN32
    HMODULE handle = ::LoadLibraryA(path);
    if (handle != NULL)
    {
        libraries.push_back(handle);
    }
#else
    void* handle = dlopen(path, RTLD_LAZY);
    if (handle != nullptr)
    {
        libraries.push_back(handle);
    }
#endif
}

void LibrariesManager::UnloadLibraries()
{
#ifdef _WIN32
    for (HMODULE handle : libraries)
    {
        ::FreeLibrary(handle);
    }
#else
    for (void* handle : libraries)
    {
        dlclose(handle);
    }
#endif
}
