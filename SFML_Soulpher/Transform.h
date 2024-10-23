#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

/*
   Transform.h
   Esta clase gestiona las transformaciones b�sicas de un actor en la escena, incluyendo su posici�n,
   rotaci�n y escala. Estas propiedades definen c�mo se representa y transforma el actor en el mundo 2D.
*/
class Transform : public Component
{
public:
    // Constructor por defecto que inicializa la posici�n, rotaci�n y escala a valores por defecto.
    Transform()
        : position(0.0f, 0.0f), rotation(0.0f), scale(1.0f, 1.0f), Component(ComponentType::TRANSFORM) {}

    // Constructor con par�metros que permite inicializar las propiedades de transformaci�n.
    Transform(const sf::Vector2f& position, float rotation = 0.0f, const sf::Vector2f& scale = sf::Vector2f(1.0f, 1.0f))
        : position(position), rotation(rotation), scale(scale), Component(ComponentType::TRANSFORM) {}

    // Destructor por defecto. No requiere liberaci�n de recursos especiales.
    virtual ~Transform() = default;

    // Actualiza el estado del componente (no hace nada en esta implementaci�n).
    void update(float deltaTime) override {}

    // Renderiza el componente (no aplicable para Transform).
    void render(Window& window) override {}

    // Establece la posici�n del actor.
    void setPosition(const sf::Vector2f& newPosition) {
        position = newPosition;
    }

    // Establece la rotaci�n del actor.
    void setRotation(float newRotation) {
        rotation = newRotation;
    }

    // Establece la escala del actor.
    void setScale(const sf::Vector2f& newScale) {
        scale = newScale;
    }

    // Devuelve la posici�n actual del actor.
    sf::Vector2f& getPosition() {
        return position;
    }

    // Devuelve la rotaci�n actual del actor.
    float getRotation() const {
        return rotation;
    }

    // Devuelve la escala actual del actor.
    sf::Vector2f& getScale() {
        return scale;
    }

    /*
       Para mover la entidad hacia un objetivo con una velocidad espec�fica.
        - targetPosition = La posici�n objetivo hacia la que se mover�.
        - speed = La velocidad a la que se mover� la entidad.
        - deltaTime = tiempo transcurrido entre frames para un movimiento suave.
        - range = La distancia m�nima antes de detener el movimiento.
    */
    void Seek(const sf::Vector2f& targetPosition, float speed, float deltaTime, float range) {
        // Calcular direcci�n hacia el objetivo.
        sf::Vector2f direction = targetPosition - position;

        // Calcular distancia al objetivo.
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // Si estamos dentro del rango, no realizamos m�s movimiento.
        if (distance < range) return;

        // Normalizamos la direcci�n.
        if (distance > 0.0f) {
            direction /= distance;
        }

        // Actualizar la posici�n seg�n direcci�n, velocidad y deltaTime.
        position += direction * speed * deltaTime;
    }

private:
    sf::Vector2f position;  // Posici�n del actor.
    float rotation;         // Rotaci�n del actor en grados.
    sf::Vector2f scale;     // Escala del actor en los ejes X e Y.
};