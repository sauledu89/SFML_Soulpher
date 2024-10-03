#pragma once
#include "Prerequisites.h"

class Window
{
public:
    
    Window() = default;

    Window(int width, int height, const std::string& title);
    
    ~Window();

    void handleEvents();

    void clear();

    void display();

    bool isOpen() const;

    void draw(const sf::Drawable& drawable);

    sf::RenderWindow* getWindow();

    void init();

    void updapte(); 

    void render();

    void destroy();

private:
    sf::RenderWindow* m_window; 
};
