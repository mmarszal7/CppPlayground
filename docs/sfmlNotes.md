## How to use SFML&GLM&GLEW in Visual Studio:

1. Open project Properties
2. Set up C++ version (e.g. C++ 17)
3. C++ > Headers - add **/glm**, **/sfml/include**, **/glew/include**
4. Linker > Libs - add **/sfml/lib**, **/glew/lib/Release/x64**
5. Linker input > bins - add:
   ```
   sfml-graphics.lib
   sfml-system.lib
   sfml-audio.lib
   sfml-window.lib
   sfml-network.lib
   glew32.lib
   ```
6. Debugging > Environment - add **PATH=%PATH%;/sfml/bin;/glew/bin/Release/x64**

## References:

Official docs: https://www.sfml-dev.org/tutorials/2.5/start-vc.php

Hopson97 guide: https://github.com/Hopson97/open-builder/blob/master/docs/building/Building_windows_vs.md#step-5-set-up-c17
