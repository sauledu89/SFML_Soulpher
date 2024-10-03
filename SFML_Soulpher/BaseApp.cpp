#include "Actor.h"
#include "BaseApp.h"


std::vector<sf::Vector2f> points = {
    sf::Vector2f(600.0f, 100.0f),
    sf::Vector2f(700.0f, 100.0f),
    sf::Vector2f(700.0f, 200.0f),
    sf::Vector2f(600.0f, 200.0f)
};

int currentTarget = 0; 
float actorSpeed = 100.0f; 
float range = 5.0f; 

bool isFollowingMouse = false; 

int BaseApp::run()
{
    if (!initialize()) 
    {
        ERROR("BaseApp", "run", "Initializes result on a false statement, check method validations.");
    }

    
    while (m_window->isOpen())
    {
        m_window->handleEvents();  

        deltaTime = Clock.restart();  

        update();  
        render(); 
    }

    cleanup();  

    return 0;
}

bool BaseApp::initialize()
{
   
    m_window = new Window(800, 600, "SFML-MAGIC-009");
    if (m_window == nullptr) 
    {
        ERROR("BaseApp", "initialize", "Error on window creation, var is null");
        return false;
    }

    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (!Circle.isNull())
    {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);  
        Circle->getComponent<ShapeFactory>()->setPosition(600.0f, 100.0f);  
        Circle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::Blue);  
    }

    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull())
    {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);  
        Triangle->getComponent<ShapeFactory>()->setPosition(0.0f, 0.0f); 
        Triangle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::White);  
    }

    return true;
}

void BaseApp::update()
{
    
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    if (!Circle.isNull())  
    {
        
        sf::Vector2f currentPosition = Circle->getComponent<ShapeFactory>()->getShape()->getPosition();

        float mouseDistance = std::sqrt((mousePosF.x - currentPosition.x) * (mousePosF.x - currentPosition.x) +
            (mousePosF.y - currentPosition.y) * (mousePosF.y - currentPosition.y));

        if (mouseDistance < 200.0f)
        {
            isFollowingMouse = true;
            Circle->getComponent<ShapeFactory>()->Seek(mousePosF, 200.0f, deltaTime.asSeconds(), 10.0f);
        }
        else
        {
            isFollowingMouse = false;  
        }

        if (!isFollowingMouse)
        {
            
            sf::Vector2f direction = points[currentTarget] - currentPosition;

           
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

           
            if (distance < range)
            {
                currentTarget = (currentTarget + 1) % points.size();  
            }

            
            Circle->getComponent<ShapeFactory>()->Seek(points[currentTarget], actorSpeed, deltaTime.asSeconds(), range);
        }
    }
}

void BaseApp::render()
{
    m_window->clear();  

    
    Circle->render(*m_window);  
    Triangle->render(*m_window);  

    m_window->display();  
}

void BaseApp::cleanup()
{
 
    m_window->destroy();  
    delete m_window;
}
