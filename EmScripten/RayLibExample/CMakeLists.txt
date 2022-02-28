cmake_minimum_required(VERSION 3.0)
project(RayLibExample)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(FETCHCONTENT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/external CACHE STRING "Base dir for thirdparty libs" )

file(GLOB_RECURSE SRC_LIST ${CMAKE_SOURCE_DIR}/src/*.cpp
                         ${CMAKE_SOURCE_DIR}/src/*.h

)

add_subdirectory(${FETCHCONTENT_SOURCE_DIR})

MESSAGE("FETCHCONTENT_SOURCE_DIR: " ${FETCHCONTENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${SRC_LIST})

set(project_resources)

# Any any resources
file(GLOB resources ${CMAKE_SOURCE_DIR}/src/resources/*)
list(APPEND project_resources ${resources})

if (EMSCRIPTEN)
    MESSAGE(STATUS "EMSCRIPTEN is enabled")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
    # Since WASM is used, ALLOW_MEMORY_GROWTH has no extra overheads
    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ALLOW_MEMORY_GROWTH=1 --no-heap-copy")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --shell-file ${CMAKE_SOURCE_DIR}/src/shell.html")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s ALLOW_MEMORY_GROWTH=1 --no-heap-copy")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --shell-file ${CMAKE_SOURCE_DIR}/src/shell.html")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
   
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "--preload-file ${CMAKE_SOURCE_DIR}/src/resources@resources")

 endif ()

target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -Wno-c++11-narrowing)

# Copy all of the resource files to the destination
file(COPY ${project_resources} DESTINATION "resources/")


