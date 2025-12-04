# Source code CMakeLists.txt

# Create and define executable.
set(SourceExecutable "SwaraTone")
add_executable(${SourceExecutable}
    main.cpp
)

# Include directories.
target_include_directories(${SourceExecutable} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add subdirectories (each adds sources/includes).
add_subdirectory(fft)
add_subdirectory(helper)
