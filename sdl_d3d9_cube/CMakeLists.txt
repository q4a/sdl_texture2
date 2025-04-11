cmake_minimum_required(VERSION 3.20)
project(sdl_d3d9_cube)

include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/sdl2.cmake")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif()

### Set up output paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)

if (WIN32)
    set(DIRECTX_INCLUDE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/../external/dxsdk-june2010/Include"
    )
    set(DIRECTX_LIBS
        "${CMAKE_CURRENT_SOURCE_DIR}/../external/dxsdk-june2010/Lib/x64/d3d9.lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/../external/dxsdk-june2010/Lib/x64/d3dx9.lib"
    )
endif()

option(USE_TEXTURE "Apply texture on 3D cube" ON)
option(USE_CUBE "Use CubeTexture (cubemap) instead of six 2D textures" ON)
if(USE_TEXTURE)
    add_definitions(-DUseTexture)
endif()
if (USE_CUBE)
    add_definitions(-DUseCubeTexture)
endif()

set(SRC_FILES
    "src/cube.cpp"
    "src/d3d_utility.cpp"
    "src/sdl_d3d9_cube.cpp"
)

add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} ${DIRECTX_LIBS} ${SDL2_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${DIRECTX_INCLUDE_DIRS})

configure_file(${PROJECT_SOURCE_DIR}/../textures/cursor.dds
    ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/cursor.dds
    COPYONLY
)
configure_file(${PROJECT_SOURCE_DIR}/../textures/earth-cubemap.dds
    ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/earth-cubemap.dds
    COPYONLY
)
