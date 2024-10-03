#include "ShapeFactory.h"

sf::Shape* ShapeFactory::createShape(ShapeType shapeType)
{
  
    m_shapeType = shapeType;

    switch (shapeType)
    {
    case EMPTY:
    {
       
        return nullptr;
    }

    case CIRCLE:
    {
  
        sf::CircleShape* circle = new sf::CircleShape(10.0f);
        circle->setFillColor(sf::Color::White);
        m_shape = circle;
        return circle;
    }

    case RECTANGLE:
    {
 
        sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2(100.0f, 50.0f));
        rectangle->setFillColor(sf::Color::White);
        m_shape = rectangle;
        return rectangle;
    }

    case TRIANGLE:
    {
      
        sf::CircleShape* triangle = new sf::CircleShape(50.0f, 3);
        triangle->setFillColor(sf::Color::White);
        m_shape = triangle;
        return triangle;
    }

    default:
        return nullptr;  
    }
}

void ShapeFactory::setPosition(float x, float y)
{
    m_shape->setPosition(x, y);
}

void ShapeFactory::setPosition(const sf::Vector2f& position)
{
    m_shape->setPosition(position);
}

void ShapeFactory::setFillColor(const sf::Color& color)
{
    m_shape->setFillColor(color);
}

void ShapeFactory::Seek(const sf::Vector2f& targetPosition, float speed, float deltaTime, float range)
{
  
    sf::Vector2f shapePosition = m_shape->getPosition();

    sf::Vector2f direction = targetPosition - shapePosition;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    
    if (length > range)
    {
        
        direction /= length;
    
        m_shape->move(direction * speed * deltaTime);
    }
}


void ShapeFactory::update(float deltaTime)
{
}

void ShapeFactory::render(Window& window)
{
    
    if (m_shape != nullptr)
    {
        window.draw(*m_shape);
    }
}
