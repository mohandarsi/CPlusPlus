# EMScripten with CMake with Visual code on windows


### SetUp  
- Install Python
- Install Emscripten and place the SDK in C:/EmScripten/
- Install VS Code  
- Install CMake and Ninja 
- Install Extensions  (not mandatory)
      Microsoft c++  
      Cmake  
	  
### Build

Create an *build* folder  in the project directory if not exists.

Open VSCode  
From VS Code - Run following tasks  
1) Run Generate  - To generate project files in Build folder.  
2) Run Build - Produces webasm in Build directory


	  
### Execute	  
Run follwoing command in command promt from build directory.  
```
   python -m http.server 8000 --bind 127.0.0.1  
   From firefox browser browse to http://127.0.0.1:8000/helloworld.html
   
```
