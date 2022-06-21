#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <chrono>

#include "config.h"
#include "View/SDL_View.h"
#include "Controller/SDL_Controller.h"
#include "Model/Launcher.h"
#include "Model/ButtonFactory.h"
#include "View/ButtonViewTest.h"
#include "View/ButtonStyle.h"
#include "Model/ButtonLogic.h"



int main(int argc, char** argv)
{
    std::cout << "[" << PROJECT_NAME <<"] - Version: {"<< PROJECT_VER<<"}"<<"\n";

    bool isRunning = true;

    std::shared_ptr<IView>view = std::make_shared<SDLView>();
    std::shared_ptr<IController>controller=std::make_shared<SDLController>();
    std::shared_ptr<IModel> launcher = std::make_shared<Launcher>();

    if(int ret = launcher->Init(view.get(), controller.get()); ret != 0){
        return ret;
    }
    if(int ret = controller->Init(launcher.get(), view.get()); ret != 0){
        return ret;
    }
    if(int ret = view->Init(launcher.get()); ret != 0){
        return ret;
    }
    
    int exitCode = 0;
    if(launcher->CheckForUpdates())
    {
        std::cout << "new version found\n";
        /*
            Tests to check that buttons work (kinda).
        */
        ButtonStyle style;
        style.color = 0xFF00FFFF;
        style.hoverColor = 0x00FF00FF;
        style.clickedColor = 0x0000FFFF;
        style.text = "";
        std::pair<ButtonLogic*, IButtonView*> testButton = ButtonFactory::CreateButton<ButtonViewTest>(350, 250, 50, 25, style, 
        [&launcher, &isRunning, &exitCode]()
        {
            std::cout << "Downloading new patch....\n";
            launcher->DownloadUpdates();
            isRunning = false;
            exitCode = 2;
        });

        launcher.get()->AddButton(testButton.first);
        view.get()->AddButton(testButton.second);
    }
    else
        view->ShowSplashArt();

	auto lastFrame = std::chrono::steady_clock::now();
	auto curFrame = std::chrono::steady_clock::now();

    // Infinite loop
    while (launcher->Running()) 
    {
        curFrame = std::chrono::steady_clock::now();
		float deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(curFrame - lastFrame).count() / 1000.0f;

        controller->Update();
        launcher->Update(deltaTime);
        view->Animate(deltaTime);
        view->Render();

		lastFrame = curFrame;
    }

    return exitCode;
}

