# src/colours CMakeLists.txt

# Add source code to executable.
target_sources(${SourceVizLib} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/colourFunctions.cpp
)

# Include directories.
target_include_directories(${SourceVizLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
