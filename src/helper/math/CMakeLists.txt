# src/helper/math CMakeLists.txt

# Add source code to executable.
target_sources(${SourceLib} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/matrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/powers.cpp
)

# Include directories.
target_include_directories(${SourceLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
