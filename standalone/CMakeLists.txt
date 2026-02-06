cmake_minimum_required(VERSION 3.14...3.22)

# 1. Update the standalone project name
project(PolyMMStandalone LANGUAGES CXX)

# --- Import tools ----
include(../cmake/tools.cmake)

# ---- Dependencies ----
include(../cmake/CPM.cmake)

CPMAddPackage(
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 3.0.0
  OPTIONS "CXXOPTS_BUILD_EXAMPLES NO" "CXXOPTS_BUILD_TESTS NO" "CXXOPTS_ENABLE_INSTALL YES"
)

# 2. Update the local library name to PolyMM
# This points to the parent directory where your main library logic lives.
CPMAddPackage(NAME PolyMM SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
find_package(Boost REQUIRED)

add_executable(${PROJECT_NAME} ${sources})

# 3. Update the output binary name and standard
# This ensures the final file is called 'PolyMM' instead of 'Greeter'
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "PolyMM")

# 4. Update the link libraries
# We use PolyMM::PolyMM assuming you renamed the root project to PolyMM as well.
target_link_libraries(${PROJECT_NAME} 
  PRIVATE          
    PolyMM::PolyMM 
    cxxopts 
    Boost::boost
)