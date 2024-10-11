#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "Component.h"

// Clase que maneja la transformaci�n (posici�n, rotaci�n y escala) de un actor en la escena
class Transform : public Component
{
public:
    // Constructor por defecto
    Transform()
        : m_position(0.0f, 0.0f), m_rotation(0.0f), m_scale(1.0f, 1.0f), Component(ComponentType::TRANSFORM) {}

    // Constructor con par�metros para inicializar la transformaci�n
    Transform(const sf::Vector2f& position, float rotation = 0.0f, const sf::Vector2f& scale = sf::Vector2f(1.0f, 1.0f))
        : m_position(position), m_rotation(rotation), m_scale(scale), Component(ComponentType::TRANSFORM) {}

    // Destructor por defecto
    virtual ~Transform() = default;

    // M�todo de actualizaci�n de la transformaci�n (no se necesita l�gica adicional aqu�)
    void update(float deltaTime) override {}

    // M�todo de renderizado (sin implementaci�n porque Transform no se dibuja)
    void render(Window& window) override {}

    // Setters y Getters para modificar la posici�n, rotaci�n y escala
    void setPosition(float x, float y) { m_position = sf::Vector2f(x, y); }
    void setPosition(const sf::Vector2f& position) { m_position = position; }

    void setRotation(float rotation) { m_rotation = rotation; }

    void setScale(float scaleX, float scaleY) { m_scale = sf::Vector2f(scaleX, scaleY); }
    void setScale(const sf::Vector2f& scale) { m_scale = scale; }

    sf::Vector2f getPosition() const { return m_position; }
    float getRotation() const { return m_rotation; }
    sf::Vector2f getScale() const { return m_scale; }

private:
    sf::Vector2f m_position;  // Almacena la posici�n de la entidad en el mundo
    float m_rotation;         // Almacena la rotaci�n de la entidad en grados
    sf::Vector2f m_scale;     // Almacena la escala de la entidad (X, Y)
};