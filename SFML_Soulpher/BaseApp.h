#pragma once  

#include "Prerequisites.h"  
#include "Window.h"         
#include "Actor.h"          

/*
  Clase BaseApp
  - Actúa como la clase principal que controla la ejecución del programa.
  - Gestiona la creación de la ventana, la inicialización de los actores y el ciclo de vida de la aplicación.
  En el contexto de gráficas computacionales 3D, esta clase podría ser extendida para incluir sistemas de cámaras,
  gestión de escenas 3D, y otras funcionalidades avanzadas como sistemas de partículas y control de física.
 */
class BaseApp
{
public:
    /*
      Constructor por defecto.
     */
    BaseApp() = default;

    /*
      Destructor por defecto
     */
    ~BaseApp() = default;

    /*
      Función run:
      - Ciclo principal del programa.
      - Coordina la ejecución de la aplicación, gestionando la lógica, eventos y renderizado en cada ciclo.
      Explicada en códigos anteriores.
     */
    int run();

    /*
      Función initialize:
      - Realiza la inicialización de la ventana y actores.
      Explicada en códigos como BaseApp
     */
    bool initialize();

    /*
      Función update:

      - Lógica de actualización de la aplicación en cada frame.
      Explicada en códigos BaseApp
     */
    void update();

    /*
      Función render:
      - Renderiza los actores en la ventana y muestra el estado actual de la escena.
      Explicada en códigos como BaseApp
     */
    void render();

    /*
      Función cleanup:
      - Libera los recursos utilizados por la aplicación y destruye la ventana.
      Explicada en códigos como BaseApp
     */
    void cleanup();

private:
    Window* m_window;  // Puntero a la ventana de la aplicación.

    /*
      Actores gráficos en la escena:
      Circle y Triangle son punteros inteligentes que representan formas básicas en la ventana.
      En un contexto de gráficas 3D, estos actores podrían ser reemplazados por modelos tridimensionales
      con geometrías más complejas (como personajes o elementos del entorno).
     */
    EngineUtilities::TSharedPointer<Actor> Triangle;  // Actor de tipo triángulo.
    EngineUtilities::TSharedPointer<Actor> Circle;  // Actor de tipo círculo.

    sf::Clock Clock;  // Reloj para medir el tiempo de cada frame.

    /*
      Variable deltaTime:
      - Representa el tiempo transcurrido entre un frame y otro.
      - Utilizada para regular las velocidades de movimiento de los actores, asegurando un comportamiento
        coherente independientemente del hardware en el que se ejecute la aplicación.
      En gráficas 3D, deltaTime es crucial para simular la física de los objetos (gravedad, colisiones) y calcular
      el tiempo que tarda un objeto en trasladarse de un punto a otro en un espacio tridimensional.
     */
    sf::Time deltaTime; 
};
