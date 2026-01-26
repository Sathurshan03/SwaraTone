# src/features/repet CMakeLists.txt

# Add source code to executable.
target_sources(${SourceLib} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/beat_soft_mask.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/beat_spectrum.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/repeating_period.cpp
)

# Include directories.
target_include_directories(${SourceLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
