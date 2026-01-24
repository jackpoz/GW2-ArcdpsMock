# CMakeList.txt : CMake project for GW2-ArcdpsMock-DemoPlugin, include source and define
# project specific logic here.
#

# Add source to this project's shared library.
add_library(GW2-ArcdpsMock-DemoPlugin SHARED "dllmain.cpp" "ArcdpsAPI.cpp")

target_link_libraries(GW2-ArcdpsMock-DemoPlugin PRIVATE GW2-ArcdpsMock-Common)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GW2-ArcdpsMock-DemoPlugin PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
