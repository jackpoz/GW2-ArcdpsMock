#include "LibrariesManager.h"
#include "arcdps_structs.h"

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
        Library library;
        library.GetInit = GetFunctionAddress<GetInitAddrSignature>(handle, "get_init_addr");
        library.GetRelease = GetFunctionAddress<GetReleaseAddrSignature>(handle, "get_release_addr");

        void* swapChain = nullptr;
        library.Init = library.GetInit("GW2-ArcdpsMock", ImGui::GetCurrentContext(), (void*)swapChain, selfHandle, malloc, free, dxMode);
        library.Exports = library.Init();

        libraries.push_back(library);
    }
}

void LibrariesManager::UnloadLibraries()
{
    for (Library library : libraries)
    {
        auto release = library.GetRelease();
        release();

#ifdef _WIN32
        ::FreeLibrary(library.Handle);
#else
        dlclose(library.Handle);
#endif
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
