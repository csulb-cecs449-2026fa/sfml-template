cmake_minimum_required(VERSION 3.21)

option(BUILD_GRAPHICS "Build the interactive SFML application" ON)
option(BUILD_TESTING "Build the unit tests" ON)

# Select vcpkg dependencies before project() loads the vcpkg toolchain.
if (BUILD_GRAPHICS)
  list(APPEND VCPKG_MANIFEST_FEATURES "graphics")
endif()
if (BUILD_TESTING)
  list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Graphics")

add_subdirectory("Common")

if (BUILD_GRAPHICS)
  add_executable(Graphics
    "src/main.cpp"
    "include/sfml_renderer.h"
    "src/sfml_renderer.cpp"
  )

  find_package(SFML COMPONENTS System Window Graphics CONFIG REQUIRED)
  target_link_libraries(Graphics PRIVATE
    common
    SFML::System
    SFML::Window
    SFML::Graphics
  )

  target_include_directories(Graphics PRIVATE "./include")
  target_compile_features(Graphics PRIVATE cxx_std_20)
endif()

include(CTest)
if (BUILD_TESTING)
  add_subdirectory("tests")
endif()
