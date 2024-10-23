#pragma once
#include "Prerequisites.h"  // Importa las dependencias necesarias.
#include "Window.h"         // Maneja la ventana principal donde se renderiza el contenido.
#include "ShapeFactory.h"   // Provee utilidades para crear formas geom�tricas.
#include "Actor.h"          // Define los actores que se dibujar�n en pantalla.

/*
  Clase principal que controla el flujo de la aplicaci�n.
  Esta clase gestiona la ventana, los actores (como el tri�ngulo, c�rculo y pista),
  y contiene la l�gica para la actualizaci�n, renderizado, movimiento y liberaci�n de recursos.
*/
class BaseApp {
public:
    /*
      Constructor por defecto.
       No realiza ninguna inicializaci�n adicional en este caso.
    */
    BaseApp() = default;

    /*
      Destructor por defecto.
      No se realizan liberaciones manuales, ya que se usan punteros inteligentes.
    */
    ~BaseApp() = default;

    /* 
       Ejecuta la aplicaci�n desde la funci�n principal.
       Llama a las funciones de inicializaci�n, actualizaci�n por frame, renderizado
       y liberaci�n de recursos al final de la ejecuci�n.
    */
    int run();

    /*
      Inicializa los recursos necesarios para la aplicaci�n.
      Crea la ventana principal y los actores, estableciendo sus posiciones iniciales.
      true Si la inicializaci�n fue exitosa, false en caso de error.
    */
    bool initialize();

    /*
      Actualiza la l�gica de la aplicaci�n en cada frame.
      Se encarga de gestionar el movimiento de los actores, el seguimiento del rat�n,
      y cualquier otra actualizaci�n requerida por frame.
    */
    void update();

    /*
       Renderiza los actores en la ventana.
       Dibuja los actores en la pantalla en cada frame despu�s de la actualizaci�n.
    */
    void render();

    /*
       Libera los recursos utilizados por la aplicaci�n.
       Se encarga de limpiar la memoria y liberar los recursos al cerrar la aplicaci�n.
    */
    void cleanup();

    /*
       Actualiza el movimiento del c�rculo entre waypoints.
       Si el rat�n no est� cerca, el c�rculo regresa a la ruta entre waypoints.
       deltaTime = Tiempo entre frames utilizado para calcular el movimiento.
          circle = Puntero inteligente al actor del c�rculo.
    */
    void updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

private:
    Window* m_window;  // Puntero a la ventana principal de la aplicaci�n.

    EngineUtilities::TSharedPointer<Actor> Triangle;  // Actor que representa el tri�ngulo.
    EngineUtilities::TSharedPointer<Actor> Circle;    // Actor que representa el c�rculo.
    EngineUtilities::TSharedPointer<Actor> Track;     // Actor que representa la pista.

    // Actores para las cabezas de los personajes.
    EngineUtilities::TSharedPointer<Actor> MarioHead;

    // Texturas necesarias.
    sf::Texture texture;    // Textura para la pista.
    sf::Texture Mario;      // Textura para Mario.


    int currentWaypoint = 0;        // �ndice del waypoint actual en la trayectoria del c�rculo.
    bool isFollowingMouse = false;  //Indica si el c�rculo est� siguiendo al rat�n.

    /* 
       Lista de waypoints.
       Ruta desde la l�nea de salida
       Cada waypoint es un Vector 2d que representa una posici�n en la ventana.
    */
    std::vector<sf::Vector2f> waypoints = {
        {720.0f, 350.0f}, {720.0f, 260.0f}, {125.0f, 50.0f},
        {70.0f, 120.0f}, {70.0f, 450.0f}, {400.0f, 350.0f},
        {550.0f, 500.0f}, {650.0f, 550.0f}, {720.0f, 450.0f}
    };
};