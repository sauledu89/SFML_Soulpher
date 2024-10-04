#include "Window.h"
#include "Prerequisites.h"

/*
  Constructor de la clase Window.
 - Este constructor recibe las dimensiones de la ventana (ancho y alto) y un t�tulo de la ventana.
 - Inicializa un objeto sf::RenderWindow` utilizando la librer�a SFML para gestionar la creaci�n y renderizado de gr�ficos 2D y 3D.
  En el contexto de gr�ficas computacionales 3D, esta ventana es el espacio donde se visualizan todos los elementos gr�ficos.
  A pesar de que SFML se orienta a gr�ficos 2D, esta ventana podr�a usarse como base para integrar gr�ficos 3D con OpenGL.
 */
Window::Window(int width, int height, const std::string& title)
{
    // Crear la ventana utilizando SFML, asign�ndola al puntero m_window.
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

    // Verificar si la ventana se cre� correctamente.
    if (!m_window) {
        // Si el puntero a la ventana es nulo, reportar un error.
        ERROR("Window", "Window", "CHECK CONSTRUCTOR");
    }
    else {
        // Mensaje de confirmaci�n en caso de que la ventana se haya creado exitosamente.
        MESSAGE("WIndow", "Window", "OK");
    }
}

/*
 * Destructor de la clase Window.
 Libera la memoria asignada a m_window cuando la instancia de la clase Window es destruida.
 En aplicaciones de gr�ficas computacionales 3D, la gesti�n de memoria es esencial, ya que una mala administraci�n
  de recursos puede causar fugas de memoria y degradar el rendimiento.
 */
Window::~Window() {
    delete m_window; // Eliminar la ventana para liberar los recursos asociados.
}

/*
  Funci�n handleEvents
  Captura y maneja los eventos de la ventana, como el cierre de la misma.
  Esta funci�n es esencial para manejar interacciones del usuario en un entorno gr�fico, como cerrar la ventana
  o capturar el movimiento del rat�n en aplicaciones 3D. Aqu� se utiliza un ciclo para capturar todos los eventos
  almacenados en la cola de eventos de la ventana.
 */

void Window::handleEvents()
{
    sf::Event event; // Crear un objeto de evento de SFML.

    // Mientras haya eventos en la cola, procesarlos uno por uno.
    while (m_window->pollEvent(event))
    {
        // Si el evento es de tipo cerrado, cerrar la ventana.
        if (event.type == sf::Event::Closed)
            m_window->close();
    }
}

/*
 * Funci�n clear
 - Limpia el contenido de la ventana para prepararla para el siguiente ciclo de renderizado.
 
  En gr�ficas computacionales 3D, esta funci�n es importante para eliminar artefactos visuales y
  asegurar que la nueva escena se dibuje correctamente en cada frame.
 */
void Window::clear()
{
    if (m_window != nullptr) {
        m_window->clear(); // Limpiar la ventana.
    }
    else {
        // Si el puntero a la ventana es nulo, reportar un error.
        ERROR("Window", "clear", "CHECK FOR WINDOW POINTER DATA");
    }
}

/*
  Funci�n display
  - Muestra en pantalla todo lo que ha sido dibujado en la ventana.
  Esta funci�n es equivalente a "presentar el buffer de pantalla" en contextos 3D, donde los elementos se
  almacenan en un buffer antes de mostrarse. Es la fase final del ciclo de renderizado.
 */
void Window::display()
{
    if (m_window != nullptr) {
        m_window->display(); // Mostrar el contenido en la pantalla.
    }
    else {
        ERROR("Window", "display", "CHECK FOR WINDOW POINTER DATA");
    }
}

/*
  Funci�n isOpen
  - Comprueba si la ventana a�n est� abierta.
  Esto se utiliza para mantener activo el ciclo principal de la aplicaci�n. En un contexto 3D, es importante
  para determinar si la aplicaci�n sigue ejecut�ndose y si se deben seguir renderizando las escenas.
 */
bool Window::isOpen() const
{
    if (m_window != nullptr) {
        return m_window->isOpen(); // Devolver el estado de la ventana.
    }
    else {
        ERROR("Window", "isOpen", "CHECK FOR WINDOW POINTER DATA");
        return false;
    }
}

/*
  Funci�n draw
 - Dibuja cualquier objeto gr�fico en la ventana.
  Aunque esta funci�n est� pensada para gr�ficos 2D, se puede extender para usar objetos 3D cuando se
  integra con OpenGL. En una aplicaci�n de gr�ficos 3D, se podr�a usar para renderizar modelos, texturas y
  otros elementos visuales.
 */
void Window::draw(const sf::Drawable& drawable)
{
    if (m_window != nullptr) {
        m_window->draw(drawable); // Dibujar el objeto en la ventana.
    }
    else {
        ERROR("Window", "draw", "CHECK FOR WINDOW POINTER DATA");
    }
}

/*
 Funci�n getWindow
 - Devuelve un puntero a la ventana `sf::RenderWindow`.
 Este m�todo permite acceder a la ventana desde otras partes de la aplicaci�n, facilitando la integraci�n
  con otros sistemas de renderizado o de entrada en un entorno 3D.
 */
sf::RenderWindow* Window::getWindow()
{
    if (m_window != nullptr) {
        return m_window; // Retorna el puntero a la ventana.
    }
    else {
        ERROR("Window", "getWindow", "CHECK FOR WINDOW POINTER DATA");
        return nullptr;
    }
}

/*
  Funci�n destroy
  - Libera y destruye los recursos asociados a la ventana.
 
  En proyectos grandes, es importante liberar manualmente los recursos cuando la ventana ya no es necesaria,
  para evitar consumir memoria innecesariamente.
 */
void Window::destroy()
{
    SAFE_PTR_RELEASE(m_window); // Macro para liberar de forma segura el puntero de la ventana.
}

/*Funci�n init
 Inicializa componentes adicionales de la ventana.
 Este m�todo se deja en blanco en este contexto, pero se puede usar para inicializar otros subsistemas gr�ficos.
 */
void Window::init()
{
}

/* Funci�n update
Realiza la actualizaci�n de la l�gica de la ventana en cada ciclo de renderizado.
 Se puede usar para implementar cambios en tiempo real en un contexto de gr�ficos 3D.
 */
void Window::updapte()
{
}

/*Funci�n render
 Realiza el renderizado de la escena dentro de la ventana.
 Este m�todo normalmente contendr�a las llamadas de dibujo de objetos 3D en un entorno gr�fico tridimensional.
 */

void Window::render()
{
}
