# src/fft CMakeLists.txt

# Add source code to executable.
target_sources(${SourceExecutable} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/fft.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/frequencyDomain.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/windowing_functions.cpp
)

# Include directories.
target_include_directories(${SourceExecutable} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
