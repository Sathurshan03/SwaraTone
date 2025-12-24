# src/fft CMakeLists.txt

# Add source code to executable.
target_sources(${SourceLib} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/fft.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ifft.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/frequencyDomain.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/windowingFunctions.cpp
)

# Include directories.
target_include_directories(${SourceLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
