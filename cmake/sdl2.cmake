# Build static lib only
set(BUILD_SHARED_LIBS OFF)

include(FetchContent)

FetchContent_Declare(sdl2
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL"
    GIT_TAG "release-2.32.4"
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(sdl2)

set(SDL2_INCLUDE_DIRS ${sdl2_SOURCE_DIR}/include)
set(SDL2_LIBRARIES SDL2-static SDL2::SDL2main)
