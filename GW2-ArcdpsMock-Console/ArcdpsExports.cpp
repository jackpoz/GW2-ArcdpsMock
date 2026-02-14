#include <cstdint>
#include <ArcdpsExtension/arcdps_structs.h>
#include <CrossplatformMocks/Macro.h>
#include <imgui/imgui.h>
#include <magic_enum/magic_enum.hpp>
#include <array>

CROSSPLATFORM_MOCKS_EXPORT const wchar_t* e0();
CROSSPLATFORM_MOCKS_EXPORT void e3(const char* string);
CROSSPLATFORM_MOCKS_EXPORT void e5(ImVec4** colors);
CROSSPLATFORM_MOCKS_EXPORT uint64_t e6();
CROSSPLATFORM_MOCKS_EXPORT uint64_t e7();
CROSSPLATFORM_MOCKS_EXPORT void e8(const char* string);
CROSSPLATFORM_MOCKS_EXPORT void e9(cbtevent* event, uint32_t signature);

const wchar_t* e0()
{
	return nullptr;
}

// arcdps file log
void e3(const char* pString)
{
}

// Copied from https://github.com/Krappa322/arcdps_mock/blob/master/arcdps_mock/main.cpp
static std::array coreCols{ // size of enum `n_colours_core`
	ImVec4(1.000000f,1.000000f,1.000000f,0.000000f),
	ImVec4(1.000000f,1.000000f,1.000000f,1.000000f),
	ImVec4(0.800000f,0.800000f,0.830000f,1.000000f),
	ImVec4(0.690000f,0.650000f,0.660000f,1.000000f),
	ImVec4(1.000000f,1.000000f,0.380000f,1.000000f),
	ImVec4(0.380000f,1.000000f,0.380000f,1.000000f),
	ImVec4(1.000000f,0.380000f,0.380000f,1.000000f),
	ImVec4(0.380000f,1.000000f,1.000000f,1.000000f),
	ImVec4(0.500000f,0.470000f,0.480000f,1.000000f),
	ImVec4(0.250000f,0.220000f,0.230000f,1.000000f),
	ImVec4(0.000000f,0.000000f,5.688562f,-0.000000f)
};
static_assert(coreCols.size() == magic_enum::enum_count<ColorsCore>());
static std::array profColsBase{ // size of enum `Prof`
	ImVec4(0.340000f,0.300000f,0.360000f,0.490000f),
	ImVec4(0.040000f,0.870000f,1.000000f,0.430000f),
	ImVec4(1.000000f,0.830000f,0.240000f,0.430000f),
	ImVec4(0.890000f,0.450000f,0.160000f,0.430000f),
	ImVec4(0.530000f,0.870000f,0.040000f,0.430000f),
	ImVec4(0.890000f,0.370000f,0.450000f,0.450000f),
	ImVec4(0.970000f,0.220000f,0.220000f,0.430000f),
	ImVec4(0.800000f,0.230000f,0.820000f,0.430000f),
	ImVec4(0.020000f,0.890000f,0.490000f,0.430000f),
	ImVec4(0.630000f,0.160000f,0.160000f,0.450000f)
};
static_assert(profColsBase.size() == magic_enum::enum_count<Prof>());
static std::array profColsHighlight{ // size of enum `Prof`
	ImVec4(0.340000f,0.300000f,0.360000f,0.250000f),
	ImVec4(0.040000f,0.870000f,1.000000f,0.210000f),
	ImVec4(1.000000f,0.830000f,0.240000f,0.210000f),
	ImVec4(0.890000f,0.450000f,0.160000f,0.210000f),
	ImVec4(0.530000f,0.870000f,0.040000f,0.210000f),
	ImVec4(0.890000f,0.370000f,0.450000f,0.280000f),
	ImVec4(0.970000f,0.220000f,0.220000f,0.210000f),
	ImVec4(0.800000f,0.230000f,0.820000f,0.210000f),
	ImVec4(0.020000f,0.890000f,0.490000f,0.210000f),
	ImVec4(0.630000f,0.160000f,0.160000f,0.280000f)
};
static_assert(profColsHighlight.size() == magic_enum::enum_count<Prof>());
static std::array subgroupColsBase{ // max amount of subgroups (currently 15), defined by gw2
	ImVec4(0.340000f,0.300000f,0.360000f,0.490000f),
	ImVec4(0.970000f,0.140000f,0.140000f,0.430000f),
	ImVec4(0.140000f,0.450000f,0.970000f,0.430000f),
	ImVec4(0.640000f,0.140000f,0.970000f,0.430000f),
	ImVec4(0.140000f,0.970000f,0.970000f,0.430000f),
	ImVec4(0.970000f,0.970000f,0.140000f,0.430000f),
	ImVec4(0.970000f,0.470000f,0.140000f,0.430000f),
	ImVec4(0.140000f,0.970000f,0.140000f,0.430000f),
	ImVec4(0.970000f,0.140000f,0.970000f,0.430000f),
	ImVec4(0.470000f,0.400000f,0.190000f,0.430000f),
	ImVec4(1.000000f,0.140000f,0.640000f,0.430000f),
	ImVec4(0.800000f,1.000000f,0.000000f,0.430000f),
	ImVec4(1.000000f,0.800000f,0.000000f,0.430000f),
	ImVec4(0.000000f,0.800000f,1.000000f,0.430000f),
	ImVec4(1.000000f,0.470000f,0.800000f,0.430000f)
};
static_assert(subgroupColsBase.size() == 15);
static std::array subgroupColsHighlight{ // max amount of subgroups (currently 15), defined by gw2
	ImVec4(0.340000f,0.300000f,0.360000f,0.250000f),
	ImVec4(0.970000f,0.140000f,0.140000f,0.210000f),
	ImVec4(0.140000f,0.450000f,0.970000f,0.210000f),
	ImVec4(0.640000f,0.140000f,0.970000f,0.210000f),
	ImVec4(0.140000f,0.970000f,0.970000f,0.210000f),
	ImVec4(0.970000f,0.970000f,0.140000f,0.210000f),
	ImVec4(0.970000f,0.470000f,0.140000f,0.210000f),
	ImVec4(0.140000f,0.970000f,0.140000f,0.210000f),
	ImVec4(0.970000f,0.140000f,0.970000f,0.210000f),
	ImVec4(0.470000f,0.400000f,0.190000f,0.210000f),
	ImVec4(1.000000f,0.140000f,0.640000f,0.210000f),
	ImVec4(0.800000f,1.000000f,0.000000f,0.210000f),
	ImVec4(1.000000f,0.800000f,0.000000f,0.210000f),
	ImVec4(0.000000f,0.800000f,1.000000f,0.210000f),
	ImVec4(1.000000f,0.470000f,0.800000f,0.210000f)
};
static_assert(subgroupColsHighlight.size() == 15);

void e5(ImVec4** colors)
{
	colors[0] = coreCols.data();
	colors[1] = profColsBase.data();
	colors[2] = profColsHighlight.data();
	colors[3] = subgroupColsBase.data();
	colors[4] = subgroupColsHighlight.data();
}

uint64_t e6()
{
	return 0;
}

uint64_t e7()
{
	return 0;
}

void e8(const char* pString)
{
}

void e9(cbtevent*, uint32_t)
{
}
