#include "LibrariesManager.h"

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    // Check if a library path was provided
    if (argc < 2)
    {
        std::cout << "Usage: <library_path>" << std::endl;
        return 1;
    }

    const char* libraryPath = argv[1];
    
    // 1. Load the library from the specified input path, multiplatform (Windows and Linux)
    auto librariesManager = LibrariesManager();
    librariesManager.LoadLibrary(libraryPath);

    // 1.a. Initialize each library calling mod_init
    librariesManager.InitLibraries();

    // 2. Start UI thread. It will call mod_gui on the loaded libraries
    std::atomic<bool> running{true};
    std::thread uiThread([&librariesManager, &running]()
    {
        while(running)
        {
            librariesManager.UIUpdate();
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    });

    // 3. Start a loop that will:
    // 3.a. Ask for input: exit, repeat the previous log (if any was ran) or load and run the specified combat log
    // 3.b. Execute the requested action
    
    // 4. Set running = false to exit the UI thread
    std::this_thread::sleep_for(std::chrono::seconds(10));
    running = false;
    uiThread.join();

    // 5. Unload the libraries before exiting
    librariesManager.UnloadLibraries();

    return 0;
}
