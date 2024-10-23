#include "ShapeFactory.h"

/*
   Implementación del constructor parametrizado.
   Inicializa con un tipo específico de forma.
*/
ShapeFactory::ShapeFactory(ShapeType shapeType)
    : m_shape(nullptr), m_shapeType(shapeType), Component(ComponentType::SHAPE) {}

/* 
   Crea una nueva forma geométrica según el tipo indicado en shapeType
   Asigna la forma creada al puntero `m_shape` y devuelve un puntero a la forma.
   return -> Puntero a la forma creada  en `sf::Shape*`.
*/
sf::Shape* ShapeFactory::createShape(ShapeType shapeType) {
    m_shapeType = shapeType;

    switch (shapeType) {
    case ShapeType::EMPTY:
        return nullptr;

    case ShapeType::CIRCLE: {
        sf::CircleShape* circle = new sf::CircleShape(15.0f); // CircleShape(15.0f) -> Tamaño de los personajes 
        // circle->setFillColor(sf::Color::White); <- Para cuando el círculo era de color sólido
        m_shape = circle;
        return circle;
    }

    case ShapeType::RECTANGLE: {
        sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(100.0f, 50.0f));
        rectangle->setFillColor(sf::Color::White);
        m_shape = rectangle;
        return rectangle;
    }

    case ShapeType::TRIANGLE: {
        sf::CircleShape* triangle = new sf::CircleShape(50.0f, 3);  // Triángulo con 3 puntos.
        triangle->setFillColor(sf::Color::White);
        m_shape = triangle;
        return triangle;
    }

    default:
        return nullptr;
    }
}

/* 
   Actualiza el estado de la forma.
   Este método se ejecuta en cada frame para realizar cambios dinámicos si es necesario.
*/
void ShapeFactory::update(float deltaTime) {
    // Implementación futura: Añadir lógica de actualización si es necesario.
}

   // Renderiza la forma en la ventana proporcionada.
void ShapeFactory::render(Window& window) {
    if (m_shape != nullptr) {
        window.draw(*m_shape);  // Dibuja la forma en la ventana.
    }
}

//Establece la posición de la forma con coordenadas X & Y.
void ShapeFactory::setPosition(float x, float y) {
    if (m_shape != nullptr) {
        m_shape->setPosition(x, y);
    }
}

/*
   Se Establece la posición de la forma con un vector 2D.
   position Un vector con las coordenadas X & Y.
*/
void ShapeFactory::setPosition(const sf::Vector2f& position) {
    if (m_shape != nullptr) {
        m_shape->setPosition(position);
    }
}

/*
   Cambia el color de la forma.
   color El nuevo color a aplicar.
*/
void ShapeFactory::setFillColor(const sf::Color& color) {
    if (m_shape != nullptr) {
        m_shape->setFillColor(color);
    }
}

/*
   Establece la rotación de la forma en grados.
   angle Ángulo de rotación.
*/
void ShapeFactory::setRotation(float angle) {
    if (m_shape != nullptr) {
        m_shape->setRotation(angle);
    }
}

/*
   Establece la escala de la forma en los ejes X e Y.
   scl Vector con los valores de escala.
*/
void ShapeFactory::setScale(const sf::Vector2f& scl) {
    if (m_shape != nullptr) {
        m_shape->setScale(scl);
    }
}

/*
   Devuelve un puntero a la forma creada.
   Return -> Puntero a la forma : `sf::Shape*`.
*/
sf::Shape* ShapeFactory::getShape() {
    return m_shape;
}