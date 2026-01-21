#include "MockedTypes.h"
#include <memory>

namespace ImGui
{
    static std::unique_ptr<ImGuiContext> context = std::make_unique<ImGuiContext>();

    ImGuiContext* GetCurrentContext()
    {
        return context.get();
    }
}
