# EMScripten with CMake with Visual code on windows

Create an build folder  after cloning

Open VSCode  
From VS Code - Run tasks  
1) Run Ninja Task - To generate project files in Build folder.  
2) TODO Run Ninja build

###SetUp  
- Install Emscripten and place the SDK in C:/EmScripten/
- Install VS Code  
- Install Extensions  
      Microsoft c++  
      Cmake  
	  
###Execute	  
Run follwoing command in command promt from build directory.  
```
   python -m http.server 8000 --bind 127.0.0.1  
   From firefox browser browse to http://127.0.0.1:8000/helloworld.html
   
```