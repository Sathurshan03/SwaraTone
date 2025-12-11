# Test code CMakeLists.txt

set(TestExecutable "SwaraToneTests")

# Enable testing support
enable_testing()

# Download and make GoogleTest available
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Prevent GoogleTest from forcing shared CRT on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create test executable
add_executable(${TestExecutable})
add_dependencies(${TestExecutable} SwaraToneLib)

# Add subdirectories (each adds sources/includes).
add_subdirectory(fft)
add_subdirectory(helper)

# Link test executable against your library + gtest
target_link_libraries(${TestExecutable} PRIVATE
    SwaraToneLib
    GTest::gtest_main
)

# Register tests with CTest
include(GoogleTest)

add_compile_definitions(ENABLE_LOGGING)
