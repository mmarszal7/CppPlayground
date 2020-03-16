## **Projects:**
- **CMakeHelloWorld** - example of how to setup project with CMake
- **[OpenGL](/OpenGL/notes.md)** - overview of how to use OpenGL
- **Overview** - overview of C++ language features 
- **SFML** - demo project showing how to [configure VS](/SFML/README.md) and how to use SFML: shapes, textures, music, handling events (e.g. keyboard)
- **SFML_Game** - example of how to make animations, sprites, collision detection, jumping/gravitation, views/camera etc. in SGML - based on [Hilze Vonck's playlist](https://www.youtube.com/watch?v=axIgxBQVBg0&list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&index=1) 
- **SFML_OpenGL** - example of how to OpenGL shaders in SGML - based on SFML example /sfml/examples/shader/
- **WinBio_Fingerprint** - example of how to use Windows WinBio API with possibility to add and verify fingerprints

---
## **C++ notes:**

### [Linker](https://www.youtube.com/watch?v=H4s55GgAg0I):

- header files are used for storing declarations like those in one file programs: **void Log(string message);** <br> \* you don't need .h files, **you can store your code whereever you want, you just need to include its declaration in files where you want to use it**
- in .h files you can store both decalarations and implementations, but you should **NOT** store implementations there - when in 2 different files you include header with implementation, linker will change it into 2 identical implementations of 2 identical functions and you will get "function already defined" error
- if you use external "packages" you need to specify path to header files (e.g. in linker options in VS properties) 

### [G++](http://qcd.phys.cmu.edu/QCDcluster/gnu/g++_man.html):

- g++ is an alias for **gcc** with C++ specific options
    - g - produces debugging information
    - c - compiles or assembles the source files, but without linking (everything in separate files)

### How to add external projects with CMake:

```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../../vcpkg/scripts/buildsystems/vcpkg.cmake #-DVCPKG_TARGET_TRIPLET=x64-windows
cmake --build .
```

### Tolling:

- Compilers and builders:
  - Linux: build-essentials (gcc + gdb + make) + CMake
  - Windows: MinGW or MSVC
- Package managers: vcpkg or Conan.io
- IDEs: Visual Studio, VS Code (to make it work run it from Developer CMD for VS), Qt

## References:

- [C++ in WSL with VS Code](https://code.visualstudio.com/docs/cpp/config-wsl)
- [Ultimate C++ tutorial](https://www.youtube.com/watch?v=6y0bp-mnYU0&list=PL17WHdN9gS1uXtfhSPjGwIxAGGUJqFPWx&index=73&t=0s)
- [g++ Manual Page](http://qcd.phys.cmu.edu/QCDcluster/gnu/g++_man.html)
- [vcpkg package manager](https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=vs-2019)
- [CMake + vcpkd + VS Code example](https://github.com/microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md)
