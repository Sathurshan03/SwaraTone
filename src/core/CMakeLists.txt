# src/core CMakeLists.txt

# Add source code to executable.
target_sources(${SourceLib} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/argParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/coreLogic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sampleData.cpp
)

# Include directories.
target_include_directories(${SourceLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
