#pragma once

#include <string>
#include <curl/curl.h>



//Simple class that handles all online stuff, downloading files
class NetworkManager{
public:
    NetworkManager();
    virtual ~NetworkManager();
    int Init();

    void DownloadToFile(std::string URL, std::string pathToFile);
    std::string DownloadToString(std::string URL);
    
private:
    CURL* _curl;
};