# Source code CMakeLists.txt

# Create and define executable.
set(SourceExecutable "SwaraTone")
set(SourceLib "SwaraToneLib")
set(SourceHelperLib "SwaraToneHelperLib")
set(SourceVizLib "SwaraToneVizLib")

add_executable(${SourceExecutable}
    main.cpp
)
add_library(${SourceLib} STATIC)

find_package(Qt6 REQUIRED COMPONENTS Core Gui)
target_link_libraries(${SourceExecutable} PUBLIC Qt6::Core Qt6::Gui)

# Include directories.
target_include_directories(${SourceLib} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add subdirectories (each adds sources/includes).
add_subdirectory(audio_file)
add_subdirectory(core)
add_subdirectory(features)
add_subdirectory(fft)
add_subdirectory(helper)
add_subdirectory(mask)
add_subdirectory(viz)

target_link_libraries(${SourceExecutable} PUBLIC ${SourceLib})
target_link_libraries(${SourceLib} PUBLIC ${SourceHelperLib})
target_link_libraries(${SourceLib} PUBLIC ${SourceVizLib})
add_compile_definitions(ENABLE_LOGGING)
