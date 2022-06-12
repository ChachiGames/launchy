#include <SDL.h>
#include <curl/curl.h>

#include <iostream>
#include <functional>
#include <filesystem>
#include <process.h>
#include <string>

#include "config.h"
#include "View/SDL_View.h"


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

int main(int argc, char** argv)
{
    std::cout << "[" << PROJECT_NAME <<"] - Version: {"<< PROJECT_VER<<"}"<<"\n";

    bool isRunning = true;

    SDLView* view = new SDLView();

    // Initializes and checks that the initialization went well.
    int viewInitialization = view->Init();
    if(viewInitialization != 0) return viewInitialization;
    
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

            std::string thisFile = argv[0];   if (thisFile.find(".exe") == std::string::npos) thisFile += ".exe";
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
                rename(thisFile.c_str(), "oldVersion.exe");
                view->Quit();
                curl_global_cleanup();

                return 2; //Exit with our own code for re-launch
            }
        }
        /* always cleanup */
        curl_easy_cleanup(curl);       
    }


    // Infinite loop
    while (isRunning) {

        SDL_Event event;

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }

        }

        view->Render();
    }

    // Free
    view->Quit();
    return 0;
}

