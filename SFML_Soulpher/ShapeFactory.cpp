#include "ShapeFactory.h"

/*
  Funci�n createShape
  - Crea y devuelve una nueva forma (sf::Shape) basada en el tipo de ShapeType proporcionado.
  - Almacena la forma en el miembro m_shape para su posterior manipulaci�n y renderizado.
  En el contexto de gr�ficos 3D, esta funci�n podr�a extenderse para crear diferentes tipos de geometr�as tridimensionales
  como cubos, esferas o modelos personalizados, utilizando clases como sf::Mesh o contextos OpenGL para almacenar
  los v�rtices y las propiedades de cada objeto.
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
        // Creaci�n del c�rculo, radio de 10 unidades.
        sf::CircleShape* circle = new sf::CircleShape(10.0f);
        circle->setFillColor(sf::Color::White);  // Color de relleno predeterminado.
        m_shape = circle;  // Almacena la referencia de la forma creada en `m_shape`.
        return circle;
    }

    case RECTANGLE:
    {
        // Crea un rect�ngulo con dimensiones 100x50.
        sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2(100.0f, 50.0f));
        rectangle->setFillColor(sf::Color::White);  // Color de relleno predeterminado.
        m_shape = rectangle;  // Almacena la referencia de la forma creada.
        return rectangle;
    }

    case TRIANGLE:
    {
        // Crea un tri�ngulo equil�tero usando `sf::CircleShape` con 3 puntos.
        sf::CircleShape* triangle = new sf::CircleShape(50.0f, 3);  // Radio y n�mero de lados.
        triangle->setFillColor(sf::Color::White);  // Color de relleno predeterminado.
        m_shape = triangle;  // Almacena la referencia de la forma creada.
        return triangle;
    }

    default:
        return nullptr;  // En caso de un tipo de forma desconocido, retornar nullptr.
    }
}

/*
  Funci�n setPosition
  - Establece la posici�n de la forma utilizando coordenadas float (x, y).
  La funci�n setPosition permite posicionar la forma en un punto espec�fico del espacio 2D.
  En gr�ficos 3D, se utilizar�an coordenadas 3D (x, y, z) para definir la posici�n del modelo en el espacio tridimensional.
 */
void ShapeFactory::setPosition(float x, float y)
{
    m_shape->setPosition(x, y);  // Establecer la posici�n usando coordenadas flotantes.
}

/*
  Sobrecarga de setPosition que acepta un vector `sf::Vector2f`.
  - Permite establecer la posici�n de la forma utilizando un vector en lugar de coordenadas individuales.
  En un entorno 3D, se utilizar�a un vector `Vector3f` para definir la posici�n en tres dimensiones.
 */
void ShapeFactory::setPosition(const sf::Vector2f& position)
{
    m_shape->setPosition(position);  // Establecer la posici�n usando un vector.
}

/*
  Funci�n setFillColor
  - Cambia el color de relleno de la forma.
  En gr�ficos 3D, esta funci�n podr�a estar asociada a la manipulaci�n de materiales y shaders que
  determinan el color, textura y apariencia de un objeto tridimensional.
 */
void ShapeFactory::setFillColor(const sf::Color& color)
{
    m_shape->setFillColor(color);  // Establecer el color de relleno de la forma.
}

/*
  Funci�n Seek
  - Mueve la forma hacia una posici�n objetivo a una velocidad determinada.
  Esta es una implementaci�n de un comportamiento de "persecuci�n" en gr�ficos 2D.
  En un entorno 3D, el c�lculo de direcci�n y distancia se realizar�a usando vectores 3D, y la forma se mover�a
  en el espacio tridimensional hacia la posici�n deseada.
 */
void ShapeFactory::Seek(const sf::Vector2f& targetPosition, float speed, float deltaTime, float range)
{
    sf::Vector2f shapePosition = m_shape->getPosition();  // Obtener la posici�n actual de la forma.

    sf::Vector2f direction = targetPosition - shapePosition;  // Calcular la direcci�n hacia el objetivo.

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);  // Calcular la distancia.

    if (length > range)  // Si la distancia es mayor que el rango definido...
    {
        direction /= length;  // Normalizar el vector de direcci�n.
        m_shape->move(direction * speed * deltaTime);  // Mover la forma hacia el objetivo.
    }
}

/*
  Funci�n update
  - Actualiza el estado del componente en cada ciclo de la aplicaci�n.
  En gr�ficos 3D, se podr�a utilizar para aplicar transformaciones, animaciones o cambios de estado
  en los modelos tridimensionales.
 */
void ShapeFactory::update(float deltaTime)
{
  
}

/*
  Funci�n render
  - Renderiza la forma en la ventana proporcionada.
  En un entorno 3D, esta funci�n se encargar�a de enviar las geometr�as y materiales a la GPU para
  que sean dibujados en pantalla usando t�cnicas como sombreado y texturizado.
 */
void ShapeFactory::render(Window& window)
{
    if (m_shape != nullptr)  // Si la forma no es nula...
    {
        window.draw(*m_shape);  // Dibujar la forma en la ventana.
    }
}
