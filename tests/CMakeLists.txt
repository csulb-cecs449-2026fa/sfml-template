find_package(GTest CONFIG REQUIRED)

add_executable(framebuffer_tests
  src/framebuffer_tests.cpp
)

target_link_libraries(framebuffer_tests PRIVATE common GTest::gtest_main)
target_compile_features(framebuffer_tests PRIVATE cxx_std_20)

include(GoogleTest)
gtest_discover_tests(framebuffer_tests)
