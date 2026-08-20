add_library(common STATIC
  src/framebuffer.cpp
)

find_package(glm CONFIG REQUIRED)
target_link_libraries(common PUBLIC glm::glm)

target_include_directories(common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(common PUBLIC cxx_std_20)
