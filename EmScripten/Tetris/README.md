# C++ Tetris - CMake+Visual code (Web/Desktop)

<span style="color:red"> **Development under progress.** </span> 
 
Inspired from [Tetris in Nelua](https://github.com/edubart/nelua-tetris)  

## SetUp

- Install Python
- Install [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) and place the SDK in C:/EmScripten/
- Install [VS Code](https://code.visualstudio.com/)
- Install [CMake](https://cmake.org/) and [Ninja](https://ninja-build.org/)
- Install [Calng](https://releases.llvm.org/download.html) to build as desktop executable.
- Install Extensions
      Microsoft c++  
      Cmake
      CodeLLDB - to debug in windows Clang c++

## Build

Create an *build* folder  in the project directory if not exists.

Open VSCode  
From VS Code - Run following tasks from *Terminal* menu

1) Generate Web - To generate project files in Build folder.  
2) Build - Produces webasm and associated js files in Build directory.

## Execute

Run follwoing command in command promt from build directory.  

```
   python -m http.server 8000 --bind 127.0.0.1  
   From firefox browser browse to http://127.0.0.1:8000/ and select html file
   
```
