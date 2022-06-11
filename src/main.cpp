#include <SDL.h>
#include <curl/curl.h>

#include <iostream>
#include <functional>

#include <string>

#include "config.h"

int main(int argc, char** argv)
{
    std::cout << "[" << PROJECT_NAME <<"] - Version: {"<< PROJECT_VER<<"}"<<"\n";

    // Declaration
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning = true;

    // Initialisation
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Unable to init SDL : %s", SDL_GetError());
        return 1;
    } window = SDL_CreateWindow("Launchy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN|SDL_WINDOW_BORDERLESS);
    if (window == NULL) {
        printf("Unable to create window : %s", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Unable to create renderer : %s", SDL_GetError());
        return 1;
    }

    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/ChachiGames/launchy/main/README.md");

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYSTATUS, 1);
        curl_easy_setopt(curl, CURLOPT_CAINFO, ".\\cacert.pem");
        curl_easy_setopt(curl, CURLOPT_CAPATH, ".\\cacert.pem");

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

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

        // Clear screen
        SDL_RenderClear(renderer);

        // render code goes here.....

        // Render modification
        SDL_RenderPresent(renderer);
    }

    // Free
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}

