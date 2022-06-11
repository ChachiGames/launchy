#include <iostream>
#include <stdio.h>
#include <filesystem>
#include <process.h>


// If there are pending updates, the launcher is updated:
// The newer version is downloaded, and the current and new version are switched
// The newer version is executed after the update
int main(int argc, char* argv[])
{
    std::string thisFile = argv[0];   if (thisFile.find(".exe") == std::string::npos) thisFile += ".exe";
    std::string oldVersion = std::filesystem::current_path().string() + "/oldVersion.exe";

    // If there is an old version, it is removed
    if (std::filesystem::exists(oldVersion))
    { 
        remove(oldVersion.c_str());
    }

    // TODO: download new version if possible
    std::string newVersion = std::filesystem::current_path().string() + "/newVersion.exe";

    // there is a newer version
    if (std::filesystem::exists(newVersion))
    {
        // Versions are switched
        rename(thisFile.c_str(), "oldVersion.exe");
        rename(newVersion.c_str(), thisFile.c_str());

        // The new version is executed
        _execv(thisFile.c_str(), argv);
    }

    return 0;
}