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
    std::string logPath = "";
    std::string input = "";
    bool exitRequested = false;

    while (!exitRequested)
    {
        std::cout << "\n=== Menu ===" << std::endl;
        std::cout << "1. Exit" << std::endl;
        std::cout << "2. Load and run a combat log" << std::endl;
        if (!logPath.empty())
        {
            std::cout << "3. Repeat previous log (" << logPath << ")" << std::endl;
        }

        std::cout << "Enter your choice: ";

        std::getline(std::cin, input);

        if (input == "1")
        {
            exitRequested = true;
        }
        else if (input == "2")
        {
            std::cout << "Enter combat log path: ";
            std::getline(std::cin, logPath);
            
            if (!logPath.empty())
            {
                std::cout << "Loading combat log: " << logPath << std::endl;
                if (librariesManager.LoadCombatLog(logPath.c_str()))
                {
                    std::cout << "Running combat log" << std::endl;
                    librariesManager.RunCombatLog(2);
                    std::cout << "Run completed" << std::endl;
                }
                else
                {
                    std::cout << "An error occurred loading the combat log";
                }
            }
            else
            {
                std::cout << "Invalid path provided." << std::endl;
            }
        }
        else if (input == "3" && !logPath.empty())
        {
            std::cout << "Running previous log: " << logPath << std::endl;
            librariesManager.RunCombatLog();
        }
        else
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    // 4. Set running = false to exit the UI thread
    running = false;
    uiThread.join();

    // 5. Unload the libraries before exiting
    librariesManager.UnloadLibraries();

    return 0;
}
