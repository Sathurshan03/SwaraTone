# Source code CMakeLists.txt

# Create and define executable.
set(SourceExecutable "SwaraTone")
set(SourceLib "SwaraToneLib")

add_executable(${SourceExecutable}
    main.cpp
)
add_library(${SourceLib} STATIC)

# Include directories.
target_include_directories(${SourceLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add subdirectories (each adds sources/includes).
add_subdirectory(fft)
add_subdirectory(helper)
add_subdirectory(audio_file)

target_link_libraries(${SourceExecutable} PUBLIC ${SourceLib})
add_compile_definitions(ENABLE_LOGGING)
