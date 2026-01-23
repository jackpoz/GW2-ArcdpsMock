#pragma once
#include "MockedTypes.h"
#include "SharedTypes.h"
#include <cstdint>

typedef struct cbtevent
{
	uint64_t time;
	uintptr_t src_agent;
	uintptr_t dst_agent;
	int32_t value;
	int32_t buff_dmg;
	uint32_t overstack_value;
	uint32_t skillid;
	uint16_t src_instid;
	uint16_t dst_instid;
	uint16_t src_master_instid;
	uint16_t dst_master_instid;
	uint8_t iff;
	uint8_t buff;
	uint8_t result;
	uint8_t is_activation;
	uint8_t is_buffremove;
	uint8_t is_ninety;
	uint8_t is_fifty;
	uint8_t is_moving;
	uint8_t is_statechange;
	uint8_t is_flanking;
	uint8_t is_shields;
	uint8_t is_offcycle;
	uint8_t pad61;
	uint8_t pad62;
	uint8_t pad63;
	uint8_t pad64;
} cbtevent;

typedef struct ag
{
	const char* name;
	uintptr_t id;
	uint32_t prof;
	uint32_t elite;
	uint32_t self;
	uint16_t team;
} ag;

typedef UINT(*WindowCallbackSignature)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
typedef void (*CombatCallbackSignature)(cbtevent* ev, ag* src, ag* dst, const char* skillname, uint64_t id, uint64_t revision);
typedef void (*ImguiCallbackSignature)(uint32_t not_charsel_or_loading, uint32_t hide_if_combat_or_ooc);
typedef void (*OptionsEndCallbackSignature)();
typedef void (*OptionsWindowsCallbackSignature)(const char* windowname);

typedef struct arcdps_exports
{
	uintptr_t size;
	uint32_t sig;
	uint32_t imguivers;
	const char* out_name;
	const char* out_build;
	WindowCallbackSignature wnd_nofilter;
	CombatCallbackSignature combat;
	ImguiCallbackSignature imgui;
	OptionsEndCallbackSignature options_end;
	CombatCallbackSignature combat_local;
	WindowCallbackSignature wnd_filter;
	OptionsWindowsCallbackSignature options_windows;
} arcdps_exports;

typedef arcdps_exports* (*ModInitSignature)();
typedef uintptr_t(*ModReleaseSignature)();
typedef void* (*MallocSignature)(size_t);
typedef void (*FreeSignature)(void*);
typedef ModInitSignature(*GetInitAddrSignature)(const char* arcversion, ImGuiContext* imguictx, void* dxptr, LibraryHandle arcdll, MallocSignature mallocfn, FreeSignature freefn, UINT dxver);
typedef ModReleaseSignature(*GetReleaseAddrSignature)();
