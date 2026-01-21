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
    LibraryHandle handle = ::LoadLibraryA(path);
#else
    LibraryHandle handle = dlopen(path, RTLD_LAZY);
#endif

    if (handle != nullptr)
    {
        libraries.push_back(handle);
    }
}

void LibrariesManager::UnloadLibraries()
{
    for (LibraryHandle handle : libraries)
    {
#ifdef _WIN32
        ::FreeLibrary(handle);
#else
        dlclose(handle);
#endif
    }
}
