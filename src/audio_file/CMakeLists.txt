# src/audio_file CMakeLists.txt

# Add subdirectories (each adds sources/includes).
add_subdirectory(mp3)
add_subdirectory(wav)

# Include directories.
target_include_directories(${SourceLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
