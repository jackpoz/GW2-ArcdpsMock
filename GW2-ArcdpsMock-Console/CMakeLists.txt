# CMakeList.txt : CMake project for GW2-ArcdpsMock-Console, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (GW2-ArcdpsMock-Console "main.cpp"  "LibrariesManager.cpp" "Library.h" "ArcdpsExports.cpp")

find_package(magic_enum CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ArcdpsUnofficialExtras CONFIG REQUIRED)
find_package(CURL CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(ArcdpsExtension CONFIG REQUIRED)

target_link_libraries(GW2-ArcdpsMock-Console PRIVATE
  ArcdpsExtension::ArcdpsExtension)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GW2-ArcdpsMock-Console PROPERTY CXX_STANDARD 23)
endif()
