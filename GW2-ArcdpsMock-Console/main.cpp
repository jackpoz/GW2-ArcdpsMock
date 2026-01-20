#include "LibrariesManager.h"

#include <iostream>

int main(int argc, char* argv[])
{
    // Check if a library path was provided
    if (argc < 2)
    {
        std::cout << "Usage: <library_path>" << std::endl;
        return 1;
    }

    const char* libraryPath = argv[1];
    
    // 1. Load library from the specified input path, multiplatform (Windows and Linux)
    auto librariesManager = LibrariesManager();
    librariesManager.LoadLibrary(libraryPath);

    // 1.a. Initialize each library calling mod_init
    // 2. Start UI thread. It will call mod_gui on the loaded libraries
    // 3. Start a loop that will:
    // 3.a. Ask for input: exit, repeat the previous log (if any was ran) or load and run the specified combat log
    // 3.b. Execute the requested action

    librariesManager.UnloadLibraries();

    return 0;
}
