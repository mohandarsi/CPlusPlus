
#Add Raygui

include(ExternalProject)

set(HAS_raylib OFF)

# if(IS_DIRECTORY "${FETCHCONTENT_SOURCE_DIR}/raylib")
#     if(EXISTS "${FETCHCONTENT_SOURCE_DIR}/raylib/CMakeLists.txt")
#         set (HAS_raylib   ON)
#     endif()
# endif()

MESSAGE("HAS_raylib: " ${HAS_raylib})
if (NOT HAS_raylib)
    include(FetchContent)
        FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 4.0.0
        SOURCE_DIR          ${FETCHCONTENT_SOURCE_DIR}/raylib-src
        SUBBUILD_DIR        ${FETCHCONTENT_SOURCE_DIR}/raylib-subbuild
        UPDATE_COMMAND      ""
        CONFIGURE_COMMAND   ""
        BUILD_COMMAND       ""
        INSTALL_COMMAND     ""
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
        set(BUILD_TESTING  OFF CACHE BOOL "" FORCE)
    endif()
endif()

find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG v4.0.4
        SOURCE_DIR          ${FETCHCONTENT_SOURCE_DIR}/raylib_cpp-src
        SUBBUILD_DIR        ${FETCHCONTENT_SOURCE_DIR}/raylib_cpp-subbuild
        UPDATE_COMMAND      ""
        CONFIGURE_COMMAND   ""
        BUILD_COMMAND       ""
        INSTALL_COMMAND     ""
    )
    FetchContent_GetProperties(raylib_cpp)
    if (NOT raylib_cpp_POPULATED) # Have we downloaded raylib-cpp yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib_cpp)
    endif()
endif()

add_subdirectory(${raylib_cpp_SOURCE_DIR} ${raylib_cpp_BINARY_DIR})
add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})