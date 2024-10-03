#include "Prerequisites.h"
#include "Actor.h"

Actor::Actor(std::string actorName)
{
  
    m_name = actorName;

    EngineUtilities::TSharedPointer<ShapeFactory> shape = EngineUtilities::MakeShared<ShapeFactory>();
    addComponent(shape); 

}

void Actor::update(float deltaTime)
{

}

void Actor::render(Window& window)
{
   
    for (unsigned int i = 0; i < components.size(); i++)
    {
       
        window.draw(*components[i].dynamic_pointer_cast<ShapeFactory>()->getShape());
    }
}

