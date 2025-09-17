Just a basic DFS maze generation program, I still have lots to improve on but it works so that's something.

  Compiling on windows:
    First get the raylib library installed on your machine with:
      "vcpkg install raylib:x64-windows"

  Second compile the program using:
    g++ main.cpp MazeOperations.cpp MazeData.cpp CellAndWallData.cpp VerifyInput.cpp \
    -std=c++20 -o maze.exe \
    -I C:\vcpkg\installed\x64-mingw-dynamic\include -L C:\vcpkg\installed\x64-mingw-dynamic\lib \
    -lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32

Note:
  raylib.lib, librarylib.dll, and glfw3.dll are included in the same folder.
  Not sure why they weren't working when they were on my PATH but this workaround fixed it...
