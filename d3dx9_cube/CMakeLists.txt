cmake_minimum_required(VERSION 3.20)
project(d3dx9_cube)

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

set(SRC_FILES
    "src/cube.cpp"
    "src/d3dUtility.cpp"
    "src/d3dx9_cube.cpp"
)

add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} winmm ${DIRECTX_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${DIRECTX_INCLUDE_DIRS})

configure_file(${PROJECT_SOURCE_DIR}/../textures/cursor.dds
    ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/cursor.dds
    COPYONLY
)
