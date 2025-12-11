# src/helper CMakeLists.txt

# Add subdirectories (each adds sources/includes).
add_subdirectory(bit)
add_subdirectory(math)

# Add source code to executable.
target_sources(${SourceLib} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/logging.cpp
)

# Include directories.
target_include_directories(${SourceLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
