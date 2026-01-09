# src/features CMakeLists.txt

# Add subdirectories (each adds sources/includes).
add_subdirectory(repet)

# Add source code to executable.
target_sources(${SourceLib} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/hpss.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/signalReconstruction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/spectrum.cpp
)

# Include directories.
target_include_directories(${SourceLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
