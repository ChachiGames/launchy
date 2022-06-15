#include "Launcher.h"
#include "config.h"
#include "NetworkManager.h"
#include "ButtonLogic.h"
#include "View/IButtonView.h"

#include <assert.h>
#include <iostream>
#include <functional>
#include <filesystem>
#include <process.h>
#include <string>
#include <curl/curl.h>



Launcher::Launcher()
{
}

Launcher::~Launcher()
{
}

std::vector<std::string> split(std::string s, std::string delimiter) {
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

int Launcher::Init(IView* view, IController* controller)
{
    assert(view);
    assert(controller);

    _view = view;
    _controller = controller;
    
    _networkManager = new NetworkManager();
    if(int res = _networkManager->Init(); res !=0)
    {
        std::cout << "Error initializing NetworkManager" << std::endl;
        return res;
    }
    return 0;
}

void Launcher::Quit()
{
    std::cout << "Me cieeeeeeeeerro\n";
}

bool Launcher::CheckForUpdates()
{
    std::cout << "Checking for new version...\n";

    std::string buffer;
    try{
        buffer = _networkManager->DownloadToString("https://chachigames.github.io/launchy/manifest");
    }
    catch (std::exception e){
        std::cout << e.what()<<std::endl;
        return false;
    }
    auto splits = split(buffer, "\n");
    std::string version = splits[0];
    auto numbers = split(version, "."); 
    _updateLink = splits[1];

    return  numbers[0] > PROJECT_VER_MAJOR ||numbers[1] > PROJECT_VER_MINOR || numbers[2]  > PROJECT_VER_PATCH;
}

int Launcher::DownloadUpdates()
{
    std::cout << "Downloading new version...\n";

    _networkManager->DownloadToFile(_updateLink, std::filesystem::current_path().string() + "/newVersion.exe");
    std::string oldVersion = std::filesystem::current_path().string() + "/oldVersion.exe";

    // If there is an old version, it is removed
    if (std::filesystem::exists(oldVersion)){
        remove(oldVersion.c_str());
    }

    std::string newVersion = std::filesystem::current_path().string() + "/newVersion.exe";

    // There is a newer version
    if (std::filesystem::exists(newVersion))
    {
        std::cout << "New version found" << std::endl;
        return 2; //Exit with our own code for re-launch
    }

    return 0;    
}

void Launcher::Update()
{
    _state = LauncherState::POP_UP;
}

void Launcher::AddButton(ButtonLogic* button)
{
    _buttons.push_back(button);
}

void Launcher::PointerMoved(int x, int y)
{
    for(ButtonLogic* bl : _buttons)
        if(bl->GetView()->IsOver(x,y)){
            bl->OnHover();
            break;
        }
        else if (bl->GetState() != ButtonState::BTN_IDLE)
        {
            bl->Idle();
        }
}

void Launcher::PointerClicked(int x, int y)
{
    for(ButtonLogic* bl : _buttons)
        if(bl->GetView()->IsOver(x,y)){
            bl->OnClicked();
            break;
        }
        else if (bl->GetState() != ButtonState::BTN_IDLE)
        {
            bl->Idle();
        }
}

void Launcher::Moved(Direction direction)
{
}
