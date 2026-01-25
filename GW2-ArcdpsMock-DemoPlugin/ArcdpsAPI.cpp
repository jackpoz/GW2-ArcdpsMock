#include "arcdps_structs.h"
#include "Dependencies.h"
#include "SharedTypes.h"
#include <cstdint>
#include <cstring>
#include <iostream>

arcdps_exports arc_exports;

EXPORT void* get_init_addr(char* arcversion, ImGuiContext* imguictx, void* id3dptr, LibraryHandle arcdll, void* mallocfn, void* freefn, uint32_t d3dversion);
EXPORT void* get_release_addr();
arcdps_exports* mod_init();
void mod_release();
void mod_options();
void mod_imgui(uint32_t not_charsel_or_loading, uint32_t hide_if_combat_or_ooc);
void mod_combat(cbtevent* ev, ag* src, ag* dst, const char* skillname, uint64_t id, uint64_t revision);

EXPORT void* get_init_addr(char* arcversion, ImGuiContext* imguictx, void* id3dptr, LibraryHandle arcdll, void* mallocfn, void* freefn, uint32_t d3dversion)
{
	/*
	ImGui::SetCurrentContext((ImGuiContext*)imguictx);
	ImGui::SetAllocatorFunctions((void* (*)(size_t, void*))mallocfn, (void (*)(void*, void*))freefn);
	*/
	return reinterpret_cast<void*>(mod_init);
}

EXPORT void* get_release_addr()
{
	return reinterpret_cast<void*>(mod_release);
}

arcdps_exports* mod_init()
{
    std::cout << "GW2-ArcdpsMock-DemoPlugin: mod_init called" << std::endl;
	TriggereDependenciesLoad();

	memset(&arc_exports, 0, sizeof(arcdps_exports));
	arc_exports.sig = 0x1B250F21; // CRC32 of "GW2-ArcdpsMock-DemoPlugin"
	arc_exports.imguivers = IMGUI_VERSION_NUM;
	arc_exports.size = sizeof(arcdps_exports);
	arc_exports.out_name = "GW2-ArcdpsMock-DemoPlugin";
	arc_exports.out_build = "1.0.0";
	arc_exports.options_end = mod_options;
	arc_exports.imgui = mod_imgui;
	//arc_exports.wnd_nofilter = mod_wnd;
	arc_exports.combat = mod_combat;
	//arc_exports.size = (uintptr_t)"error message if you decide to not load, sig must be 0";
	return &arc_exports;
}

void mod_release()
{
	std::cout << "GW2-ArcdpsMock-DemoPlugin: mod_release called" << std::endl;
}

void mod_options()
{
	std::cout << "GW2-ArcdpsMock-DemoPlugin: mod_options called" << std::endl;
}

void mod_imgui(uint32_t not_charsel_or_loading, uint32_t hide_if_combat_or_ooc)
{
	std::cout << "GW2-ArcdpsMock-DemoPlugin: mod_imgui called" << std::endl;
}

void mod_combat(cbtevent* ev, ag* src, ag* dst, const char* skillname, uint64_t id, uint64_t revision)
{
	std::cout << "GW2-ArcdpsMock-DemoPlugin: mod_combat called" << std::endl;
}
