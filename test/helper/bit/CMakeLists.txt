# test/helper CMakeLists.txt

# Define test executable files.
target_sources(${TestExecutable} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/bit_property_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bit_reversal_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/endian_test.cpp
)
