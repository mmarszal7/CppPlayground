## [Linker notes](https://www.youtube.com/watch?v=H4s55GgAg0I):
- header files are used for storing declarations like those in one file programs: **void Log(string message);** <br>
\* you don't need .h files, **you can store your code whereever you want, you just need to include its declaration in files where you want to use it**
- in .h files you can store both decalarations and implementations, but you should **NOT** store implementations there - when in 2 different files you include header with implementation, linker will change it into 2 identical implementations of 2 identical functions and you will get "function already defined" error 

## [G++](http://qcd.phys.cmu.edu/QCDcluster/gnu/g++_man.html) notes:
-g++ is an alias for **gcc** with C++ specific options
-g - produces debugging information
-c - compiles or assembles the source files, but without linking (everything in separate files)

## References:
- [C++ in WSL with VS Code](https://code.visualstudio.com/docs/cpp/config-wsl)
- [Ultimate C++ tutorial](https://www.youtube.com/watch?v=6y0bp-mnYU0&list=PL17WHdN9gS1uXtfhSPjGwIxAGGUJqFPWx&index=73&t=0s)
- [g++ Manual Page](http://qcd.phys.cmu.edu/QCDcluster/gnu/g++_man.html)
- [vcpkg package manager](https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=vs-2019)