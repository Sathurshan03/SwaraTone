# src/helper/bit CMakeLists.txt

# Add source code to executable.
target_sources(${SourceExecutable} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/bit_reversal.cpp
)

# Include directories.
target_include_directories(${SourceExecutable} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
