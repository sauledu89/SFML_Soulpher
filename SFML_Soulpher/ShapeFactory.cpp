#include "ShapeFactory.h"

/*
  Función createShape
  - Crea y devuelve una nueva forma (sf::Shape) basada en el tipo de ShapeType proporcionado.
  - Almacena la forma en el miembro m_shape para su posterior manipulación y renderizado.
  En el contexto de gráficos 3D, esta función podría extenderse para crear diferentes tipos de geometrías tridimensionales
  como cubos, esferas o modelos personalizados, utilizando clases como sf::Mesh o contextos OpenGL para almacenar
  los vértices y las propiedades de cada objeto.
 */
sf::Shape* ShapeFactory::createShape(ShapeType shapeType)
{
    m_shapeType = shapeType;  // Almacena el tipo de forma actual.

    switch (shapeType)
    {
    case EMPTY:
    {
        // Si el tipo de forma es EMPTY, no se crea ninguna forma.
        return nullptr;
    }

    case CIRCLE:
    {
        // Creación del círculo, radio de 10 unidades.
        sf::CircleShape* circle = new sf::CircleShape(10.0f);
        circle->setFillColor(sf::Color::White);  // Color de relleno predeterminado.
        m_shape = circle;  // Almacena la referencia de la forma creada en `m_shape`.
        return circle;
    }

    case RECTANGLE:
    {
        // Crea un rectángulo con dimensiones 100x50.
        sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2(100.0f, 50.0f));
        rectangle->setFillColor(sf::Color::White);  // Color de relleno predeterminado.
        m_shape = rectangle;  // Almacena la referencia de la forma creada.
        return rectangle;
    }

    case TRIANGLE:
    {
        // Crea un triángulo equilátero usando `sf::CircleShape` con 3 puntos.
        sf::CircleShape* triangle = new sf::CircleShape(50.0f, 3);  // Radio y número de lados.
        triangle->setFillColor(sf::Color::White);  // Color de relleno predeterminado.
        m_shape = triangle;  // Almacena la referencia de la forma creada.
        return triangle;
    }

    default:
        return nullptr;  // En caso de un tipo de forma desconocido, retornar nullptr.
    }
}

/*
  Función setPosition
  - Establece la posición de la forma utilizando coordenadas float (x, y).
  La función setPosition permite posicionar la forma en un punto específico del espacio 2D.
  En gráficos 3D, se utilizarían coordenadas 3D (x, y, z) para definir la posición del modelo en el espacio tridimensional.
 */
void ShapeFactory::setPosition(float x, float y)
{
    m_shape->setPosition(x, y);  // Establecer la posición usando coordenadas flotantes.
}

/*
  Sobrecarga de setPosition que acepta un vector `sf::Vector2f`.
  - Permite establecer la posición de la forma utilizando un vector en lugar de coordenadas individuales.
  En un entorno 3D, se utilizaría un vector `Vector3f` para definir la posición en tres dimensiones.
 */
void ShapeFactory::setPosition(const sf::Vector2f& position)
{
    m_shape->setPosition(position);  // Establecer la posición usando un vector.
}

/*
  Función setFillColor
  - Cambia el color de relleno de la forma.
  En gráficos 3D, esta función podría estar asociada a la manipulación de materiales y shaders que
  determinan el color, textura y apariencia de un objeto tridimensional.
 */
void ShapeFactory::setFillColor(const sf::Color& color)
{
    m_shape->setFillColor(color);  // Establecer el color de relleno de la forma.
}

/*
  Función Seek
  - Mueve la forma hacia una posición objetivo a una velocidad determinada.
  Esta es una implementación de un comportamiento de "persecución" en gráficos 2D.
  En un entorno 3D, el cálculo de dirección y distancia se realizaría usando vectores 3D, y la forma se movería
  en el espacio tridimensional hacia la posición deseada.
 */
void ShapeFactory::Seek(const sf::Vector2f& targetPosition, float speed, float deltaTime, float range)
{
    sf::Vector2f shapePosition = m_shape->getPosition();  // Obtener la posición actual de la forma.

    sf::Vector2f direction = targetPosition - shapePosition;  // Calcular la dirección hacia el objetivo.

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);  // Calcular la distancia.

    if (length > range)  // Si la distancia es mayor que el rango definido...
    {
        direction /= length;  // Normalizar el vector de dirección.
        m_shape->move(direction * speed * deltaTime);  // Mover la forma hacia el objetivo.
    }
}

/*
  Función update
  - Actualiza el estado del componente en cada ciclo de la aplicación.
  En gráficos 3D, se podría utilizar para aplicar transformaciones, animaciones o cambios de estado
  en los modelos tridimensionales.
 */
void ShapeFactory::update(float deltaTime)
{
  
}

/*
  Función render
  - Renderiza la forma en la ventana proporcionada.
  En un entorno 3D, esta función se encargaría de enviar las geometrías y materiales a la GPU para
  que sean dibujados en pantalla usando técnicas como sombreado y texturizado.
 */
void ShapeFactory::render(Window& window)
{
    if (m_shape != nullptr)  // Si la forma no es nula...
    {
        window.draw(*m_shape);  // Dibujar la forma en la ventana.
    }
}
