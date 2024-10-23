#pragma once 
#include "Prerequisites.h"  

/*
  Clase Window
  - Se encarga de la gesti�n de la ventana donde se renderizan los gr�ficos.
  - Proporciona m�todos para manejar eventos, limpiar la pantalla, dibujar y mostrar los elementos.
  En el contexto de gr�ficas computacionales 3D, esta clase podr�a ser extendida para manejar contextos OpenGL,
  sistemas de c�maras y otros elementos gr�ficos avanzados para renderizar modelos tridimensionales.
 */
class Window
{
public:
    /*
      Constructor por defecto.
    */
    Window() = default;

    /*
      Constructor parametrizado.
    */
    Window(int width, int height, const std::string& title);

    /*
      Destructor de la clase Window.
    */
    ~Window();

    void handleEvents();
 
    void clear();
   
    void display();

    /*
      Funci�n isOpen.
      - Comprueba si la ventana sigue abierta.
      - Explicado en c�digos anteriores.
    */
    bool isOpen() const;

    /*
      Funci�n draw.
      - Dibuja cualquier objeto derivado de sf::Drawable en la ventana.
      - Explicado en c�digos anteriores.
    */
    void draw(const sf::Drawable& drawable);

    /*
      Funci�n getWindow.
      - Devuelve un puntero a la ventana sf::RenderWindow.
      - Explicado en c�digos anteriores.
    */
    sf::RenderWindow* getWindow();

    /*
      Funci�n init.
      - Inicializa componentes adicionales de la ventana.
      Aunque en este proyecto no se implementa, en un entorno 3D se podr�a usar esta funci�n para inicializar
      contextos gr�ficos avanzados (como OpenGL) o cargar shaders, buffers de v�rtices y texturas para la escena.
    */
    void init();

    /*
      Funci�n updapte.
      - Se deja en blanco en este proyecto, pero normalmente se utilizar�a para actualizar
        la l�gica de la ventana, como el estado de la interfaz o la posici�n de la c�mara.
      En gr�ficos 3D, podr�a actualizar variables dependientes del tiempo, como la posici�n de los elementos de la escena.
    */
    void update();

    /*
      Funci�n render.
      - Encargada de dibujar los elementos en la ventana.
      Aunque no est� implementada aqu�, en un contexto 3D esta funci�n podr�a incluir el renderizado de modelos 3D,
      la aplicaci�n de efectos de sombreado y el c�lculo de iluminaci�n para cada objeto en la escena.
    */
    void render();

    /*
      Funci�n destroy.
      - Libera los recursos asociados a la ventana y destruye el puntero.
      Esta funci�n se asegura de que todos los elementos asociados a la ventana se liberen adecuadamente,
      evitando fugas de memoria que puedan ocurrir al destruir la ventana sin liberar sus recursos.
    */
    void destroy();

private:
    /*
      Puntero m_window a sf::RenderWindow.
      - Este puntero representa la ventana en la cual se renderizan todos los gr�ficos.
      En un contexto de gr�ficas computacionales 3D, m_window se podr�a usar para configurar el contexto OpenGL y
      gestionar directamente la memoria de la GPU, como la creaci�n de Framebuffers, Shaders y Texturas.
    */

    sf::RenderWindow* m_window;
    sf::View m_view;  // Vista de la ventana para manipular la c�mara o perspectiva.

    // Tiempo entre frames y medir tiempo entre frames.
public:
    sf::Time deltaTime;  
    sf::Clock clock;      
};
