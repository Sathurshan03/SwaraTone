# test/mask CMakeLists.txt

# Define test executable files.
target_sources(${TestExecutable} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/hpss_mask_test.cpp
)

# Add include directories.
target_include_directories(${TestExecutable} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
