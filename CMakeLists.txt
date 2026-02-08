cmake_minimum_required(VERSION 3.30...3.31) # Updated for modern Boost policy

# ---- Project ----
project(
  PolyMM
  VERSION 1.0
  LANGUAGES C CXX # C is required for low-level crypto libs like secp256k1
)

# Silence the Boost warning we discussed
cmake_policy(SET CMP0167 NEW)

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. Create a 'build' folder and run from there.")
endif()

# ---- Add dependencies via CPM ----
include(cmake/CPM.cmake)

# PackageProject.cmake for installation
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.8.0")

# Polymarket Client
CPMAddPackage(
  NAME polymarket_client # Use underscore for internal consistency
  GITHUB_REPOSITORY SebastianBoehler/polymarket-cpp-client
  GIT_TAG main 
)

# fmt library
CPMAddPackage(
  NAME fmt
  GIT_TAG 10.2.1
  GITHUB_REPOSITORY fmtlib/fmt
  OPTIONS "FMT_INSTALL YES"
)

# 1. OpenSSL is a system dependency (installed via Brew)
find_package(OpenSSL REQUIRED)

# 2. Boost is a system dependency (installed via Brew)
# Using CONFIG ensures we use the modern Homebrew-provided config files
find_package(Boost CONFIG REQUIRED)

# ---- Add source files ----
# Note: Since you're creating a library, your headers should be in /include
# and your implementation logic should be in /src
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# DEBUG: Add these lines to see exactly what CMake found in your terminal
message(STATUS "Cmake source: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Headers found: ${headers}")
message(STATUS "Sources found: ${sources}")

# ---- Create library ----
add_library(${PROJECT_NAME} ${headers} ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20) # Upgraded to 20 for better tuple/map support

# Link dependencies
target_link_libraries(${PROJECT_NAME} 
  PUBLIC 
    fmt::fmt
    polymarket_client
    OpenSSL::SSL
    OpenSSL::Crypto
    Boost::boost # This makes Boost available to anything that links to PolyMM
)

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

# ---- Create an installable target ----
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)
add_subdirectory(standalone)

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  NAMESPACE ${PROJECT_NAME}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  COMPATIBILITY SameMajorVersion
  DEPENDENCIES "fmt 10.2.1"
)
