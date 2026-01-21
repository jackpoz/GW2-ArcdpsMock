# CMakeList.txt : CMake project for GW2-ArcdpsMock-Console, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (GW2-ArcdpsMock-Console "main.cpp"  "LibrariesManager.cpp" "arcdps_structs.h" "SharedTypes.h" "MockedTypes.h" "Library.h" "MockedTypes.cpp" "ArcdpsExports.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GW2-ArcdpsMock-Console PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
