# CMakeList.txt : CMake project for GW2-ArcdpsMock-DemoPlugin, include source and define
# project specific logic here.
#

# Add source to this project's shared library.
add_library(GW2-ArcdpsMock-DemoPlugin SHARED "dllmain.cpp" "ArcdpsAPI.cpp" "Dependencies.cpp" "Dependencies.h")

find_package(magic_enum CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ArcdpsUnofficialExtras CONFIG REQUIRED)
find_package(CURL CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(ArcdpsExtension CONFIG REQUIRED)

target_link_libraries(GW2-ArcdpsMock-DemoPlugin PRIVATE
  ArcdpsExtension::ArcdpsExtension)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GW2-ArcdpsMock-DemoPlugin PROPERTY CXX_STANDARD 23)
endif()
