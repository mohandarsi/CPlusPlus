# C++ WebAssembly - EMScripten+CMake+Visual code+Windows

## SetUp

- Install Python
- Install [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) and place the SDK in C:/EmScripten/
- Install [VS Code](https://code.visualstudio.com/)
- Install [CMake](https://cmake.org/) and [Ninja](https://ninja-build.org/)
- Install Extensions  (not mandatory)
      Microsoft c++  
      Cmake  

## Build

Create an *build* folder  in the project directory if not exists.

Open VSCode  
From VS Code - Run following tasks from *Terminal* menu

1) Generate  - To generate project files in Build folder.  
2) Build - Produces webasm and associated js files in Build directory.

## Execute

Run follwoing command in command promt from build directory.  

```
   python -m http.server 8000 --bind 127.0.0.1  
   From firefox browser browse to http://127.0.0.1:8000/helloworld.html
   
```
