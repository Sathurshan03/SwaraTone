# src/helper CMakeLists.txt

# Add subdirectories (each adds sources/includes).
add_subdirectory(bit)

# Include directories.
target_include_directories(${SourceLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
