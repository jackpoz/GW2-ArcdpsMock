#pragma once
#include "SharedTypes.h"
#include "Library.h"

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
