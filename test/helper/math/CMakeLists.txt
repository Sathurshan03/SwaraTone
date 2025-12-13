# test/helper/math CMakeLists.txt

# Define test executable files.
target_sources(${TestExecutable} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/stats_median_test.cpp
)

# Add include directories.
target_include_directories(${TestExecutable} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
