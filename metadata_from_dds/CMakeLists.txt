cmake_minimum_required(VERSION 3.20)
project(metadata_from_dds)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif()

### Set up output paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(SRC_FILES
    "src/metadata_from_dds.cpp"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

find_package(directxtex CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC Microsoft::DirectXTex)
