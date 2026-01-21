#pragma once

#ifdef _WIN32
#include <Windows.h>
typedef HMODULE LibraryHandle;
#define EXPORT extern "C" __declspec(dllexport)
#else
#include <dlfcn.h>
typedef void* LibraryHandle;
#define EXPORT extern "C" __attribute__((visibility("default")))
#endif
