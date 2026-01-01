# src/helper CMakeLists.txt

add_library(${SourceHelperLib} STATIC)

# Add subdirectories (each adds sources/includes).
add_subdirectory(bit)
add_subdirectory(filters)
add_subdirectory(math)

# Add source code to executable.
target_sources(${SourceHelperLib} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/logging.cpp
)

# Include directories.
target_include_directories(${SourceHelperLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
