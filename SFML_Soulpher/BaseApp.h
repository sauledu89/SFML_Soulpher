#pragma once

#include "Prerequisites.h"
#include "Window.h"
#include "Actor.h"

class BaseApp
{
public:
    BaseApp() = default;  
    ~BaseApp() = default;  

    int run();

    bool initialize();

    void update();

    void render();

    void cleanup();

private:
    Window* m_window;
    EngineUtilities::TSharedPointer<Actor> Triangle;  
    EngineUtilities::TSharedPointer<Actor> Circle;  

    sf::Clock Clock;  
    sf::Time deltaTime;  
};
