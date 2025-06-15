cmake_minimum_required(VERSION 3.16)

project(MinorCraft)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories("Include/")

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/MinorCraft-Game")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# Adding Source Files
# add_executable(MinorCraft "Source/main.cpp"
#               "Source/mb_logger.cpp")

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    Source/*.cpp
    Source/*.c
)

add_executable(MinorCraft ${SRC_FILES})

# macOS config
if(APPLE)
    link_directories("${CMAKE_SOURCE_DIR}/Libs/macOS")
    target_compile_definitions(MinorCraft PRIVATE MACOS)
    # Link against glfw3 library and the apple default frameworks
    target_link_libraries(MinorCraft
        "${CMAKE_SOURCE_DIR}/Libs/macOS/libglfw3.a"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreFoundation"
        "-framework CoreVideo")
elseif(WIN32)
    target_compile_definitions(MinorCraft PRIVATE WINDOWS)
elseif(UNIX)
    target_compile_definitions(MinorCraft PRIVATE LINUX)
endif()

target_compile_definitions(MinorCraft PRIVATE DEBUG)

add_custom_command(TARGET MinorCraft POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Assets"
        "${OUTPUT_DIR}/assets"
)
