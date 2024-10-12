#include "Actor.h"
#include "BaseApp.h"


/*
  Definici�n de puntos de movimiento para el actor Circle.
  Estos puntos representan las posiciones a las que el actor se mover� secuencialmente en el espacio 2D.
  En un contexto de gr�ficas computacionales 3D, los puntos podr�an utilizarse para definir trayectorias de movimiento en un espacio tridimensional.
  Por ejemplo, podr�an ser utilizados para patrullas de enemigos en un entorno 3D.
 */

std::vector<sf::Vector2f> points = {
    sf::Vector2f(250.0f, 100.0f), // Punto 1
    sf::Vector2f(500.0f, 100.0f), // Punto 2
    sf::Vector2f(500.0f, 200.0f), // Punto 3
    sf::Vector2f(250.0f, 200.0f)  // Punto 4
};

int currentTarget = 0;          // �ndice del objetivo actual en el vector de puntos.
float actorSpeed = 100.0f;      // Velocidad del actor en unidades por segundo.
float range = 5.0f;             // Rango de proximidad para considerar que el actor ha alcanzado un punto.

bool isFollowingMouse = false;  // Bandera que indica si el actor est� siguiendo el rat�n.

/*
  Funci�n run
  - Ciclo principal de la aplicaci�n.
  - Inicializa los recursos, maneja los eventos y actualiza el renderizado en cada iteraci�n.
  Este ciclo es equivalente al *Game Loop* en gr�ficos 3D, donde se controlan el estado de los objetos, la l�gica de movimiento, y el renderizado de la escena.
 */
int BaseApp::run()
{
    if (!initialize())
    {
        ERROR("BaseApp", "run", "Initializes result on a false statement, check method validations.");
    }

    // Bucle principal de la aplicaci�n.
    while (m_window->isOpen())
    {
        m_window->handleEvents();     // Capturar y manejar eventos de la ventana.
        deltaTime = Clock.restart();  // Calcular el tiempo delta para regular las velocidades de movimiento.

        update();  // Actualizar el estado de los actores y la l�gica del juego.
        render();  // Dibujar la escena en la ventana.
    }

    cleanup();  // Liberar los recursos utilizados.

    return 0;  // Indicar que el programa finaliz� correctamente.
}

/*
  Funci�n initialize
  - Inicializa la ventana y los actores utilizados en la aplicaci�n.
  En aplicaciones gr�ficas m�s complejas, esta funci�n podr�a ser utilizada para cargar modelos 3D,
  texturas o inicializar sistemas de iluminaci�n y c�maras.
 */
bool BaseApp::initialize()
{
    // Crear la ventana principal con las dimensiones especificadas y un t�tulo.
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
        // Crear un c�rculo con el componente ShapeFactory.
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
        Circle->getComponent<ShapeFactory>()->setPosition(600.0f, 100.0f);  // Posicionar en el primer punto.
        Circle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::Yellow);  // Establecer el color del c�rculo.
    }

    // Crear y configurar el actor Triangle.
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull())
    {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);  // Crear un tri�ngulo.
        Triangle->getComponent<ShapeFactory>()->setPosition(350.0f, 120.0f);  // Posicionarlo
        Triangle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::Cyan);  // Establecer el color del tri�ngulo.
    }

    return true;  // Inicializaci�n exitosa.
}

/*
  Funci�n update
  - L�gica de actualizaci�n de los actores en cada frame.
  - Controla el seguimiento del rat�n y el movimiento del actor entre puntos.
  En un entorno 3D, esta funci�n podr�a ser utilizada para actualizar la posici�n de las c�maras, manejar interacciones de personajes y simular
  f�sicas complejas.
 */
void BaseApp::update()
{
    // Obtener la posici�n actual del rat�n.
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    if (!Circle.isNull())
    {
        // Obtener la posici�n actual del c�rculo.
        sf::Vector2f currentPosition = Circle->getComponent<ShapeFactory>()->getShape()->getPosition();

        // Calcular la distancia entre el rat�n y el c�rculo.
        float mouseDistance = std::sqrt((mousePosF.x - currentPosition.x) * (mousePosF.x - currentPosition.x) +
            (mousePosF.y - currentPosition.y) * (mousePosF.y - currentPosition.y));

        // Si el rat�n est� a menos de 300 unidades de distancia, activar el seguimiento.
        if (mouseDistance < 300.0f)
        {
            isFollowingMouse = true;
            Circle->getComponent<ShapeFactory>()->Seek(mousePosF, 200.0f, deltaTime.asSeconds(), 10.0f);
        }
        else
        {
            isFollowingMouse = false;
        }

        // Si no est� siguiendo al rat�n, mover el actor entre los puntos predefinidos.
        if (!isFollowingMouse)
        {
            // Calcular la direcci�n hacia el siguiente punto objetivo.
            sf::Vector2f direction = points[currentTarget] - currentPosition;

            // Calcular la distancia al objetivo actual.
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            // Si la distancia al punto es menor al rango, avanzar al siguiente objetivo.
            if (distance < range)
            {
                currentTarget = (currentTarget + 1) % points.size();  // Pasar al siguiente punto.
            }

            // Mover el c�rculo hacia el siguiente objetivo.
            Circle->getComponent<ShapeFactory>()->Seek(points[currentTarget], actorSpeed, deltaTime.asSeconds(), range);
        }
    }
}

/*
  Funci�n render
  - Dibuja los actores en la ventana.
  - Se encarga de mostrar el estado actual de la escena en cada ciclo de renderizado.
  En un entorno de gr�ficas computacionales 3D, esta funci�n podr�a ser utilizada para dibujar modelos complejos,
  aplicar efectos de iluminaci�n y realizar c�lculos de sombreado en tiempo real.
 */
void BaseApp::render()
{
    m_window->clear();  // Limpiar el contenido previo de la ventana.

    Circle->render(*m_window);  // Dibujar el actor Circle.
    Triangle->render(*m_window);  // Dibujar el actor Triangle.

    m_window->display();  // Mostrar el contenido en la pantalla.
}

/*
  Funci�n cleanup
  - Libera los recursos de la ventana y destruye los actores.
  En un entorno 3D, esta funci�n ser�a utilizada para liberar modelos, texturas y buffers de la GPU, evitando
  fugas de memoria y garantizando una correcta liberaci�n de recursos.
 */
void BaseApp::cleanup()
{
    m_window->destroy();  // Destruir la ventana.
    delete m_window;      // Eliminar la instancia de la ventana.
}
