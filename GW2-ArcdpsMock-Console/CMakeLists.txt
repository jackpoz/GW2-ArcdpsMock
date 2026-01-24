# CMakeList.txt : CMake project for GW2-ArcdpsMock-Console, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (GW2-ArcdpsMock-Console "main.cpp"  "LibrariesManager.cpp" "Library.h" "ArcdpsExports.cpp")

target_link_libraries(GW2-ArcdpsMock-Console PRIVATE GW2-ArcdpsMock-Common)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GW2-ArcdpsMock-Console PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
