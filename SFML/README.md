https://github.com/Hopson97/open-builder/blob/master/docs/building/Building_windows_vs.md#step-5-set-up-c17
https://www.sfml-dev.org/tutorials/2.5/start-vc.php

1. Set up C++ version
2. C++ > Headers (/glm & /sfml/include)
3. Linker > Libs (/sfml/lib)
4. Linker input > bins (sfml-graphics.lib;sfml-system.lib;sfml-audio.lib;sfml-window.lib;sfml-network.lib)
5. Debugging > Environment > PATH=%PATH%;/sfml/bin
