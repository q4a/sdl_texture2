cmake_minimum_required(VERSION 3.20)
project(sdl_d3d9_cube)

include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/sdl2.cmake")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif()
if (NOT DXVK_TAG)
    set(DXVK_TAG "v2.6.1" CACHE STRING "" FORCE)
endif()
message("DXVK_TAG=${DXVK_TAG}")

### Set up output paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

option(USE_TEXTURE "Apply texture on 3D cube" ON)
option(USE_CUBE "Use CubeTexture (cubemap) instead of six 2D textures" ON)
if (NOT WIN32)
option(USE_OLD_DXVK "Use old DXVK Native for native D3D9 API" OFF)
endif()

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

# Dependencies

if (WIN32)
    message("Using Windows D3D9 API")
    set(DIRECTX_INCLUDE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/../external/dxsdk-june2010/Include"
    )
    set(DIRECTX_LIBS
        "${CMAKE_CURRENT_SOURCE_DIR}/../external/dxsdk-june2010/Lib/x64/d3d9.lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/../external/dxsdk-june2010/Lib/x64/d3dx9.lib"
    )
else()
    include(ExternalProject)
    if(USE_TEXTURE)
        ExternalProject_Add(gli
            GIT_REPOSITORY    https://github.com/g-truc/gli
            GIT_TAG           779b99ac6656e4d30c3b24e96e0136a59649a869
            GIT_SHALLOW       ON
            BUILD_ALWAYS      OFF
            CONFIGURE_COMMAND ""
            BUILD_COMMAND     ""
            BUILD_BYPRODUCTS  <SOURCE_DIR>/gli/gli.hpp
            INSTALL_COMMAND   ""
        )
        ExternalProject_Get_property(gli SOURCE_DIR)
        target_include_directories(${PROJECT_NAME} PRIVATE
             "${SOURCE_DIR}"
        )
        add_dependencies(${PROJECT_NAME} gli)
    endif()

    if (USE_OLD_DXVK)
        message("Using DXVK Native for D3D9 API")
        ExternalProject_Add(dxvk-native
            GIT_REPOSITORY    https://github.com/q4a/dxvk-native
            GIT_TAG           master
            GIT_SHALLOW       ON
            BUILD_ALWAYS      OFF
            CONFIGURE_HANDLED_BY_BUILD ON
            CONFIGURE_COMMAND meson setup ../dxvk-native --buildtype=release -Denable_d3d11=false -Denable_d3d10=false -Denable_dxgi=false
            BUILD_COMMAND     ninja
            BUILD_BYPRODUCTS  <BINARY_DIR>/src/d3d9/libdxvk_d3d9.so
            INSTALL_COMMAND   ""
        )
        ExternalProject_Get_property(dxvk-native SOURCE_DIR BINARY_DIR)
        add_dependencies(${PROJECT_NAME} dxvk-native)
    else() # for newer DXVK
        message("Using DXVK for D3D9 API")
        ExternalProject_Add(dxvk
            GIT_REPOSITORY    https://github.com/doitsujin/dxvk
            GIT_TAG           ${DXVK_TAG}
            GIT_SHALLOW       ON
            BUILD_ALWAYS      OFF
            CONFIGURE_HANDLED_BY_BUILD ON
            CONFIGURE_COMMAND meson setup ../dxvk --buildtype=debug -Denable_d3d11=false -Denable_d3d10=false -Denable_dxgi=false
            BUILD_COMMAND     ninja
            BUILD_BYPRODUCTS  <BINARY_DIR>/src/d3d9/libdxvk_d3d9.so
            INSTALL_COMMAND   ""
        )
        ExternalProject_Get_property(dxvk SOURCE_DIR BINARY_DIR)
        add_dependencies(${PROJECT_NAME} dxvk)
    endif()

    set(DIRECTX_INCLUDE_DIRS
        "${SOURCE_DIR}/include/native/directx"
        "${SOURCE_DIR}/include/native/windows"
    )
    set(DIRECTX_LIBS ${BINARY_DIR}/src/d3d9/libdxvk_d3d9.so)
endif()

target_link_libraries(${PROJECT_NAME} ${DIRECTX_LIBS} ${SDL2_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${DIRECTX_INCLUDE_DIRS})

configure_file(${PROJECT_SOURCE_DIR}/../textures/cursor.dds
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cursor.dds
    COPYONLY
)
configure_file(${PROJECT_SOURCE_DIR}/../textures/earth-cubemap.dds
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/earth-cubemap.dds
    COPYONLY
)
