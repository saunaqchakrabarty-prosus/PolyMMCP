cmake_minimum_required(VERSION 3.14...3.22)

project(PolyMMStandalone LANGUAGES CXX)

# ---- Dependencies ----
# cxxopts is only used here, so we keep it
include(../cmake/CPM.cmake)
CPMAddPackage(
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 3.0.0
  OPTIONS "CXXOPTS_BUILD_EXAMPLES NO" "CXXOPTS_BUILD_TESTS NO" "CXXOPTS_ENABLE_INSTALL YES"
)

# ---- Create standalone executable ----
file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

# We define the target
add_executable(${PROJECT_NAME} ${sources})

# Ensure we use C++20 to match the library
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 OUTPUT_NAME "PolyMM")

# ---- Link EVERYTHING ----
target_link_libraries(${PROJECT_NAME} 
  PRIVATE          
    PolyMM           # Links to the library defined in root
    cxxopts::cxxopts
    Boost::boost
)