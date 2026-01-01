# src/helper/filters CMakeLists.txt

# Add source code to executable.
target_sources(${SourceHelperLib} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/highPass.cpp
)

# Include directories.
target_include_directories(${SourceHelperLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
