#pragma once 
#include "Prerequisites.h"  

/*
  Clase Window
  - Se encarga de la gestión de la ventana donde se renderizan los gráficos.
  - Proporciona métodos para manejar eventos, limpiar la pantalla, dibujar y mostrar los elementos.
  En el contexto de gráficas computacionales 3D, esta clase podría ser extendida para manejar contextos OpenGL,
  sistemas de cámaras y otros elementos gráficos avanzados para renderizar modelos tridimensionales.
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
      Función isOpen.
      - Comprueba si la ventana sigue abierta.
      - Explicado en códigos anteriores.
    */
    bool isOpen() const;

    /*
      Función draw.
      - Dibuja cualquier objeto derivado de sf::Drawable en la ventana.
      - Explicado en códigos anteriores.
    */
    void draw(const sf::Drawable& drawable);

    /*
      Función getWindow.
      - Devuelve un puntero a la ventana sf::RenderWindow.
      - Explicado en códigos anteriores.
    */
    sf::RenderWindow* getWindow();

    /*
      Función init.
      - Inicializa componentes adicionales de la ventana.
      Aunque en este proyecto no se implementa, en un entorno 3D se podría usar esta función para inicializar
      contextos gráficos avanzados (como OpenGL) o cargar shaders, buffers de vértices y texturas para la escena.
    */
    void init();

    /*
      Función updapte.
      - Se deja en blanco en este proyecto, pero normalmente se utilizaría para actualizar
        la lógica de la ventana, como el estado de la interfaz o la posición de la cámara.
      En gráficos 3D, podría actualizar variables dependientes del tiempo, como la posición de los elementos de la escena.
    */
    void update();

    /*
      Función render.
      - Encargada de dibujar los elementos en la ventana.
      Aunque no está implementada aquí, en un contexto 3D esta función podría incluir el renderizado de modelos 3D,
      la aplicación de efectos de sombreado y el cálculo de iluminación para cada objeto en la escena.
    */
    void render();

    /*
      Función destroy.
      - Libera los recursos asociados a la ventana y destruye el puntero.
      Esta función se asegura de que todos los elementos asociados a la ventana se liberen adecuadamente,
      evitando fugas de memoria que puedan ocurrir al destruir la ventana sin liberar sus recursos.
    */
    void destroy();

private:
    /*
      Puntero m_window a sf::RenderWindow.
      - Este puntero representa la ventana en la cual se renderizan todos los gráficos.
      En un contexto de gráficas computacionales 3D, m_window se podría usar para configurar el contexto OpenGL y
      gestionar directamente la memoria de la GPU, como la creación de Framebuffers, Shaders y Texturas.
    */

    sf::RenderWindow* m_window;
    sf::View m_view;  // Vista de la ventana para manipular la cámara o perspectiva.

    // Tiempo entre frames y medir tiempo entre frames.
public:
    sf::Time deltaTime;  
    sf::Clock clock;      
};
