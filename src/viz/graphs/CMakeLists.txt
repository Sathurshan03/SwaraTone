# src/viz/graph CMakeLists.txt

# Add source code to executable.
target_sources(${SourceVizLib} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lineGraph.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/plot.cpp
)

# Include directories.
target_include_directories(${SourceVizLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
