#pragma once  

#include "Prerequisites.h"  
#include "Window.h"         
#include "Actor.h"          

/*
  Clase BaseApp
  - Act�a como la clase principal que controla la ejecuci�n del programa.
  - Gestiona la creaci�n de la ventana, la inicializaci�n de los actores y el ciclo de vida de la aplicaci�n.
  En el contexto de gr�ficas computacionales 3D, esta clase podr�a ser extendida para incluir sistemas de c�maras,
  gesti�n de escenas 3D, y otras funcionalidades avanzadas como sistemas de part�culas y control de f�sica.
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
      Funci�n run:
      - Ciclo principal del programa.
      - Coordina la ejecuci�n de la aplicaci�n, gestionando la l�gica, eventos y renderizado en cada ciclo.
      Explicada en c�digos anteriores.
     */
    int run();

    /*
      Funci�n initialize:
      - Realiza la inicializaci�n de la ventana y actores.
      Explicada en c�digos como BaseApp
     */
    bool initialize();

    /*
      Funci�n update:

      - L�gica de actualizaci�n de la aplicaci�n en cada frame.
      Explicada en c�digos BaseApp
     */
    void update();

    /*
      Funci�n render:
      - Renderiza los actores en la ventana y muestra el estado actual de la escena.
      Explicada en c�digos como BaseApp
     */
    void render();

    /*
      Funci�n cleanup:
      - Libera los recursos utilizados por la aplicaci�n y destruye la ventana.
      Explicada en c�digos como BaseApp
     */
    void cleanup();

private:
    Window* m_window;  // Puntero a la ventana de la aplicaci�n.

    /*
      Actores gr�ficos en la escena:
      Circle y Triangle son punteros inteligentes que representan formas b�sicas en la ventana.
      En un contexto de gr�ficas 3D, estos actores podr�an ser reemplazados por modelos tridimensionales
      con geometr�as m�s complejas (como personajes o elementos del entorno).
     */
    EngineUtilities::TSharedPointer<Actor> Triangle;  // Actor de tipo tri�ngulo.
    EngineUtilities::TSharedPointer<Actor> Circle;  // Actor de tipo c�rculo.

    sf::Clock Clock;  // Reloj para medir el tiempo de cada frame.

    /*
      Variable deltaTime:
      - Representa el tiempo transcurrido entre un frame y otro.
      - Utilizada para regular las velocidades de movimiento de los actores, asegurando un comportamiento
        coherente independientemente del hardware en el que se ejecute la aplicaci�n.
      En gr�ficas 3D, deltaTime es crucial para simular la f�sica de los objetos (gravedad, colisiones) y calcular
      el tiempo que tarda un objeto en trasladarse de un punto a otro en un espacio tridimensional.
     */
    sf::Time deltaTime; 
};
