# CMake project for GW2-ArcdpsMock-Common static library

# Add source files for the static library
add_library(GW2-ArcdpsMock-Common STATIC
  "MockedTypes.h" "MockedTypes.cpp"
)

# Set C++ standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GW2-ArcdpsMock-Common PROPERTY CXX_STANDARD 20)
endif()

# Add include directory for public headers
target_include_directories(GW2-ArcdpsMock-Common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
