gcc ^
   %= Input Files [Sadly, GCC requires a list of every single C file in your project] =% ^
   source/main.c ^
   source/glad.c ^
   ^
   %= Name of the output file =% ^
   -o target/main.exe ^
   ^
   %= Include debug symbols in the output binary =% ^
   -g ^
   ^
   %= Include "all" warnings [Not really all, but a reasonable enough substitute] =% ^
   -Wall ^
   ^
   %= Include even more warnings =% ^
   -Wextra ^
   ^
   %= Make all warnings be errors =% ^
   -Werror ^
   ^
   %= Add the "headers" directory to the folders to search for #include headers =% ^
   -Iheaders ^
   ^
   %= Add the "libraries" directory to the folders to search for object files =% ^
   -Llibraries ^
   ^
   %= Link to the GLFW library =% ^
   -lglfw3 ^
   ^
   %= Link to GDI32 - GLFW Dependency =% ^
   -lgdi32
