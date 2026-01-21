#pragma once

#ifndef _WIN32
#include <cstdint>
typedef unsigned int UINT;
typedef void* HWND;
typedef intptr_t LPARAM;
typedef uintptr_t WPARAM;
#endif

struct ImGuiContext
{
    char Reserved[16256];
};

namespace ImGui
{
    ImGuiContext* GetCurrentContext();
}

struct ImVec4
{
    float x;
    float y;
    float z;
    float w;
};
