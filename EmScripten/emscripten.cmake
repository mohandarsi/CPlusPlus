set(CMAKE_SYSTEM_NAME Emscripten)


if(EXISTS "C:/EmScripten/emsdk/upstream/emscripten/emcc.bat")
	file(TO_CMAKE_PATH "C:/EmScripten/emsdk/upstream/emscripten" EMSCRIPTEN_SDK_BIN)
elseif(EXISTS "C:/EmScripten/emsdk/fastcomp/emscripten/emcc.bat")
	file(TO_CMAKE_PATH "C:/EmScripten/emsdk/fastcomp/emscripten" EMSCRIPTEN_SDK_BIN)
endif()


MESSAGE("EMSCRIPTEN_SDK_BIN: " ${EMSCRIPTEN_SDK_BIN})

set(EMSCRIPTEN_TOOLCHAIN_PATH "${EMSCRIPTEN_SDK_BIN}/system")

MESSAGE("EMSCRIPTEN_TOOLCHAIN_PATH: " ${EMSCRIPTEN_TOOLCHAIN_PATH})

set(EMCC_SUFFIX ".bat")

set(CMAKE_C_COMPILER "${EMSCRIPTEN_SDK_BIN}/emcc${EMCC_SUFFIX}")
set(CMAKE_CXX_COMPILER "${EMSCRIPTEN_SDK_BIN}/em++${EMCC_SUFFIX}")
set(CMAKE_AR "${EMSCRIPTEN_SDK_BIN}/emar${EMCC_SUFFIX}" CACHE FILEPATH "Emscripten ar")
set(CMAKE_RANLIB "${EMSCRIPTEN_SDK_BIN}/emranlib${EMCC_SUFFIX}" CACHE FILEPATH "Emscripten ranlib")

set(CMAKE_FIND_ROOT_PATH ${CMAKE_FIND_ROOT_PATH}
    "${EMSCRIPTEN_TOOLCHAIN_PATH}"
    "${EMSCRIPTEN_SDK_BIN}")

