cmake_minimum_required(VERSION 3.20)
project(fragments_ffi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch a matching FlatBuffers version (index_generated.h requires 25.9.23)
# Disable FlatBuffers' own tests and flatc build so we only get the library
set(FLATBUFFERS_BUILD_TESTS OFF CACHE BOOL "Do not build flatbuffers tests" FORCE)
set(FLATBUFFERS_BUILD_FLATC OFF CACHE BOOL "Do not build the flatc compiler" FORCE)

FetchContent_Declare(
  flatbuffers
  GIT_REPOSITORY https://github.com/google/flatbuffers.git
  GIT_TAG v25.9.23
)
FetchContent_MakeAvailable(flatbuffers)

add_library(fragments STATIC fragments.cpp)

target_include_directories(fragments PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(fragments PUBLIC flatbuffers)

## Tests
enable_testing()
add_executable(serializer_test tests/serializer.cpp)
target_include_directories(serializer_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(serializer_test PRIVATE fragments flatbuffers)

add_test(NAME serializer COMMAND serializer_test)

# Provide a convenient target that runs tests on every build
add_custom_target(run_tests ALL
  # Run only our serializer test to avoid executing upstream project's tests.
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -R "^serializer$"
  DEPENDS serializer_test
  COMMENT "Running serializer test after build"
)
