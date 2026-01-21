#pragma once

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
