#include <iostream>
#include <string>
#include <memory>
#include <utility>

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

    std::unique_ptr<IView>view = std::make_unique<SDLView>();
    std::unique_ptr<IController>controller=std::make_unique<SDLController>();
    std::unique_ptr<IModel> launcher = std::make_unique<Launcher>();

    if(int ret = view->Init(); ret != 0){
        return ret;
    }
    if(int ret = launcher->Init(view.get(), controller.get()); ret != 0){
        std::cout<<"EY"<<std::endl;
        return ret;
    }
    if(int ret = controller->Init(launcher.get(), view.get()); ret != 0){
        return ret;
    }
    
/*
    Tests to check that buttons work (kinda).
*/
    ButtonStyle style;
    style.color = 0xFF0000FF;
    style.hoverColor = 0x00FF00FF;
    style.clickedColor = 0x0000FFFF;
    style.text = "";
    std::pair<ButtonLogic*, IButtonView*> testButton = ButtonFactory::CreateButton<ButtonViewTest>(250, 250, 50, 25, style, [](){std::cout << "Hello\n";});

    view.get()->AddButton(testButton.second);
    
    // Infinite loop
    while (isRunning) {
        isRunning = controller->Update();
        launcher->Update();
        view->Render();
    }

    return 0;
}

