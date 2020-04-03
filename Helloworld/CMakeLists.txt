cmake_minimum_required(VERSION 3.0)

set(**DCMAKE_BUILD_TYPE**** debug**)

IF(NOT DCMAKE_BUILD_TYPE)
    SET(DCMAKE_BUILD_TYPE Release)
ENDIF()

MESSAGE("Build type: " ${DCMAKE_BUILD_TYPE})

project(HelloWorld)

file(GLOB_RECURSE HELLOWORLD_SRC_LIST
    src/*.cpp
    src/*.h
    include/*.h)

add_executable(${PROJECT_NAME} ${HELLOWORLD_SRC_LIST})