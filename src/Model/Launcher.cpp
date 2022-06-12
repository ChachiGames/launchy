#include "Launcher.h"
#include "config.h"

#include <assert.h>
#include <iostream>
#include <functional>
#include <filesystem>
#include <process.h>
#include <string>
#include <curl/curl.h>


std::string global_string;
size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
    size_t realsize = size * nmemb;
    global_string.append(ptr, realsize);
    return realsize;
}

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

Launcher::Launcher()
{
}

Launcher::~Launcher()
{
}

int Launcher::Init(IView* view, IController* controller)
{
    assert((view != nullptr) &&  "view must be a valid memory address");
    assert((controller != nullptr) &&  "controller must be a valid memory address");

    _view = view;
    _controller = controller;
    
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://chachigames.github.io/launchy/manifest");

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYSTATUS, 1);
        curl_easy_setopt(curl, CURLOPT_CAINFO, ".\\cacert.pem");
        curl_easy_setopt(curl, CURLOPT_CAPATH, ".\\cacert.pem");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        
        auto split = [](std::string s, std::string delimiter) {
            size_t pos = 0;
            std::vector<std::string> tokens;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                std::string token = s.substr(0, pos);
                tokens.push_back(token);
                s.erase(0, pos + delimiter.length());

            };
            tokens.push_back(s);
            return tokens;
        };

        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
        else
        {
            auto splits = split(global_string, "\n");
            std::string version = splits[0];
            std::string link = splits[1];
            

            auto numbers = split(version, ".");
            if (numbers[0] > PROJECT_VER_MAJOR || numbers[1] > PROJECT_VER_MINOR || numbers[2] > PROJECT_VER_PATCH)
            {
                FILE* fp = fopen((std::filesystem::current_path().string() + "/newVersion.exe").c_str(), "wb");
                curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
                res = curl_easy_perform(curl);
                if (res != CURLE_OK)
                    fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));
            }

            std::string oldVersion = std::filesystem::current_path().string() + "/oldVersion.exe";

            // If there is an old version, it is removed
            if (std::filesystem::exists(oldVersion)){
                remove(oldVersion.c_str());
            }

            std::string newVersion = std::filesystem::current_path().string() + "/newVersion.exe";

            // there is a newer version
            if (std::filesystem::exists(newVersion))
            {
                // Versions are switched
                delete controller;
                delete view;
                curl_global_cleanup();

                std::cout << "Invalid arguments given to launcher initialization" << std::endl;
                return 2; //Exit with our own code for re-launch
            }
        }
        /* always cleanup */
        curl_easy_cleanup(curl);       
    }

    return 0;
}
void Launcher::Update()
{
    _state = LauncherState::POP_UP;
}

void Launcher::PointerMoved(int x, int y)
{
}

void Launcher::PointerClicked(int x, int y)
{
}

void Launcher::Moved(Direction direction)
{
}
