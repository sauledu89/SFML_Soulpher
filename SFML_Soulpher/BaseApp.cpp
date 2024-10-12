#include "Actor.h"
#include "BaseApp.h"


/*
  Definición de puntos de movimiento para el actor Circle.
  Estos puntos representan las posiciones a las que el actor se moverá secuencialmente en el espacio 2D.
  En un contexto de gráficas computacionales 3D, los puntos podrían utilizarse para definir trayectorias de movimiento en un espacio tridimensional.
  Por ejemplo, podrían ser utilizados para patrullas de enemigos en un entorno 3D.
 */

std::vector<sf::Vector2f> points = {
    sf::Vector2f(250.0f, 100.0f), // Punto 1
    sf::Vector2f(500.0f, 100.0f), // Punto 2
    sf::Vector2f(500.0f, 200.0f), // Punto 3
    sf::Vector2f(250.0f, 200.0f)  // Punto 4
};

int currentTarget = 0;          // Índice del objetivo actual en el vector de puntos.
float actorSpeed = 100.0f;      // Velocidad del actor en unidades por segundo.
float range = 5.0f;             // Rango de proximidad para considerar que el actor ha alcanzado un punto.

bool isFollowingMouse = false;  // Bandera que indica si el actor está siguiendo el ratón.

/*
  Función run
  - Ciclo principal de la aplicación.
  - Inicializa los recursos, maneja los eventos y actualiza el renderizado en cada iteración.
  Este ciclo es equivalente al *Game Loop* en gráficos 3D, donde se controlan el estado de los objetos, la lógica de movimiento, y el renderizado de la escena.
 */
int BaseApp::run()
{
    if (!initialize())
    {
        ERROR("BaseApp", "run", "Initializes result on a false statement, check method validations.");
    }

    // Bucle principal de la aplicación.
    while (m_window->isOpen())
    {
        m_window->handleEvents();     // Capturar y manejar eventos de la ventana.
        deltaTime = Clock.restart();  // Calcular el tiempo delta para regular las velocidades de movimiento.

        update();  // Actualizar el estado de los actores y la lógica del juego.
        render();  // Dibujar la escena en la ventana.
    }

    cleanup();  // Liberar los recursos utilizados.

    return 0;  // Indicar que el programa finalizó correctamente.
}

/*
  Función initialize
  - Inicializa la ventana y los actores utilizados en la aplicación.
  En aplicaciones gráficas más complejas, esta función podría ser utilizada para cargar modelos 3D,
  texturas o inicializar sistemas de iluminación y cámaras.
 */
bool BaseApp::initialize()
{
    // Crear la ventana principal con las dimensiones especificadas y un título.
    m_window = new Window(800, 600, "SFML_Soulpher");
    if (m_window == nullptr)
    {
        ERROR("BaseApp", "initialize", "Error on window creation, var is null");
        return false;
    }

    // Crear y configurar el actor Circle.
    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (!Circle.isNull())
    {
        // Crear un círculo con el componente ShapeFactory.
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
        Circle->getComponent<ShapeFactory>()->setPosition(600.0f, 100.0f);  // Posicionar en el primer punto.
        Circle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::Yellow);  // Establecer el color del círculo.
    }

    // Crear y configurar el actor Triangle.
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull())
    {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);  // Crear un triángulo.
        Triangle->getComponent<ShapeFactory>()->setPosition(350.0f, 120.0f);  // Posicionarlo
        Triangle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::Cyan);  // Establecer el color del triángulo.
    }

    return true;  // Inicialización exitosa.
}

/*
  Función update
  - Lógica de actualización de los actores en cada frame.
  - Controla el seguimiento del ratón y el movimiento del actor entre puntos.
  En un entorno 3D, esta función podría ser utilizada para actualizar la posición de las cámaras, manejar interacciones de personajes y simular
  físicas complejas.
 */
void BaseApp::update()
{
    // Obtener la posición actual del ratón.
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    if (!Circle.isNull())
    {
        // Obtener la posición actual del círculo.
        sf::Vector2f currentPosition = Circle->getComponent<ShapeFactory>()->getShape()->getPosition();

        // Calcular la distancia entre el ratón y el círculo.
        float mouseDistance = std::sqrt((mousePosF.x - currentPosition.x) * (mousePosF.x - currentPosition.x) +
            (mousePosF.y - currentPosition.y) * (mousePosF.y - currentPosition.y));

        // Si el ratón está a menos de 300 unidades de distancia, activar el seguimiento.
        if (mouseDistance < 300.0f)
        {
            isFollowingMouse = true;
            Circle->getComponent<ShapeFactory>()->Seek(mousePosF, 200.0f, deltaTime.asSeconds(), 10.0f);
        }
        else
        {
            isFollowingMouse = false;
        }

        // Si no está siguiendo al ratón, mover el actor entre los puntos predefinidos.
        if (!isFollowingMouse)
        {
            // Calcular la dirección hacia el siguiente punto objetivo.
            sf::Vector2f direction = points[currentTarget] - currentPosition;

            // Calcular la distancia al objetivo actual.
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            // Si la distancia al punto es menor al rango, avanzar al siguiente objetivo.
            if (distance < range)
            {
                currentTarget = (currentTarget + 1) % points.size();  // Pasar al siguiente punto.
            }

            // Mover el círculo hacia el siguiente objetivo.
            Circle->getComponent<ShapeFactory>()->Seek(points[currentTarget], actorSpeed, deltaTime.asSeconds(), range);
        }
    }
}

/*
  Función render
  - Dibuja los actores en la ventana.
  - Se encarga de mostrar el estado actual de la escena en cada ciclo de renderizado.
  En un entorno de gráficas computacionales 3D, esta función podría ser utilizada para dibujar modelos complejos,
  aplicar efectos de iluminación y realizar cálculos de sombreado en tiempo real.
 */
void BaseApp::render()
{
    m_window->clear();  // Limpiar el contenido previo de la ventana.

    Circle->render(*m_window);  // Dibujar el actor Circle.
    Triangle->render(*m_window);  // Dibujar el actor Triangle.

    m_window->display();  // Mostrar el contenido en la pantalla.
}

/*
  Función cleanup
  - Libera los recursos de la ventana y destruye los actores.
  En un entorno 3D, esta función sería utilizada para liberar modelos, texturas y buffers de la GPU, evitando
  fugas de memoria y garantizando una correcta liberación de recursos.
 */
void BaseApp::cleanup()
{
    m_window->destroy();  // Destruir la ventana.
    delete m_window;      // Eliminar la instancia de la ventana.
}
