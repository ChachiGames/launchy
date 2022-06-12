#include <iostream>
#include <filesystem>
#include <process.h>
#include <iostream>

#include <Windows.h>

int exc(std::string cmd, const char* v[]) {
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    int i = 0;
    while (v[i+1])
        cmd.append(v[++i]);

    CreateProcessA(0, cmd.data(), 0, 0, 0, 0, 0, 0, &si, &pi);

    WaitForSingleObject(pi.hProcess, INFINITE);
    DWORD exit_code;
    if (FALSE == GetExitCodeProcess(pi.hProcess, &exit_code))
    {
        std::cerr << "GetExitCodeProcess() failure: " <<
            GetLastError() << "\n";
    }
    else if (STILL_ACTIVE == exit_code)
    {
        std::cout << "Still running\n";
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return exit_code;
}

int main(int argc, char** argv)
{
    std::cout << "Checking for updates..."<<std::endl;
    std::string newVersion = std::filesystem::current_path().string() + "/newVersion.exe";
    std::string oldVersion = std::filesystem::current_path().string() +"/oldVersion.exe";
    std::string launchy = std::filesystem::current_path().string() + "/launchy.exe";
    int res = 0;
    while (res == 0 || res == 2)
    {
        if (std::filesystem::exists(newVersion))
        {
            std::cout << "New version found!"<<std::endl;
            if (std::filesystem::exists(oldVersion))
                remove(oldVersion.c_str());
            if (std::filesystem::exists(launchy))
                remove(launchy.c_str());

            if (rename(newVersion.c_str(), "launchy.exe") != 0)
            {
                std::cout << "Could not rename new version to launchy.exe" << errno << std::endl;
                return 1;
            };
            const char* v[] = { launchy.c_str(), nullptr };
            int lRes = exc(launchy.c_str(), v);
            return 0;
        }
        else if (std::filesystem::exists(launchy))
        {
            const char* v[] = { launchy.c_str(), nullptr };
            int lRes = exc(launchy.c_str(), v);
            if (lRes == 0)
                return 0;
            else if (res == 0)
                res = lRes;
            else
                return 0;
        }
    }
    std::cout << "Error: launchy not found";
    return 1;
}
