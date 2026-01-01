# src/helper/bit CMakeLists.txt

# Add source code to executable.
target_sources(${SourceHelperLib} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/bit_reversal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/endian.cpp
)

# Include directories.
target_include_directories(${SourceHelperLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
