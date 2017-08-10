gcc ^
   %= Input Files [Sadly, GCC requires a list of every single C file in your project] =% ^
   source/main.c ^
   source/glad.c ^
   source/assertion/assertion.c ^
   source/texture/texture.c ^
   source/shader_program/shader_program.c ^
   %= Name of the output file =% ^
   -o target/main.exe ^
   %= Include debug symbols in the output binary =% ^
   -g ^
   %= Include "all" warnings [Not really all, but a reasonable enough substitute] =% ^
   -Wall ^
   %= Include even more warnings =% ^
   -Wextra ^
   %= Make all warnings be errors =% ^
   -Werror ^
   %= Add the "libraries" directory to the folders to search for #include headers =% ^
   -Ilibraries ^
   %= Add the "binaries" directory to the folders to search for object files =% ^
   -Lbinaries ^
   %= Link to the GLFW library =% ^
   -lglfw3 ^
   %= Link to GDI32 - GLFW Dependency =% ^
   -lgdi32

