#pragma once
#include "Prerequisites.h"
#include "Entity.h"
#include "ShapeFactory.h"

class Actor : public Entity
{
public:

    Actor() = default;

    Actor(std::string actorName);

    ~Actor() = default;

    void update(float deltaTime) override;

    void render(Window& window) override;

    void destroy();

    template <typename T>
    EngineUtilities::TSharedPointer<T> getComponent();

private:
    std::string m_name = "Actor"; 
};

template<typename T>
inline EngineUtilities::TSharedPointer<T> Actor::getComponent()
{
  
    for (auto& component : components)
    {
       
        EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
        if (specificComponent)
        {
            return specificComponent; 
        }
    }
    
    return EngineUtilities::TSharedPointer<T>();
}
