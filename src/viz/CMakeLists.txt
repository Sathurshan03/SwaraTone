# src/viz CMakeLists.txt

add_library(${SourceVizLib} STATIC)

# Include Qt6 packages.
find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Charts
)

target_link_libraries(${SourceVizLib} PUBLIC
    Qt6::Widgets
    Qt6::Charts
)

# Add subdirectories (each adds sources/includes).
add_subdirectory(colours)
add_subdirectory(graphs)

# Include directories.
target_include_directories(${SourceVizLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${SourceVizLib} PUBLIC ${SourceHelperLib})
