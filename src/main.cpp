#include <iostream>
#include <string>
#include <memory>

#include "config.h"
#include "View/SDL_View.h"
#include "Controller/SDL_Controller.h"
#include "Model/Launcher.h"



int main(int argc, char** argv)
{
    std::cout << "[" << PROJECT_NAME <<"] - Version: {"<< PROJECT_VER<<"}"<<"\n";

    bool isRunning = true;

    std::unique_ptr<IView>view = std::make_unique<SDLView>();
    std::unique_ptr<IController>controller=std::make_unique<SDLController>();
    std::unique_ptr<IModel> launcher = std::make_unique<Launcher>();

    if(int ret = view->Init(); ret != 0){
        return ret;
    }
    if(int ret = launcher->Init(view.get(), controller.get()); ret != 0){
        return ret;
    }
    if(int ret = controller->Init(launcher.get(), view.get()); ret != 0){
        return ret;
    }
    
    // Infinite loop
    while (isRunning) {
        isRunning = controller->Update();
        launcher->Update();
        view->Render();
    }

    return 0;
}

