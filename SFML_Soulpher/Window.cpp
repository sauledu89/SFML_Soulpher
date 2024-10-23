#include "Window.h"

/*
   Constructor parametrizado.
   Crea una ventana con las dimensiones y título proporcionados en BaseApp.cpp. 
   También inicializa ImGui.
*/
Window::Window(int width, int height, const std::string& title) {
    // Crear la ventana con SFML.
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

    // Verificar si la ventana se creó correctamente.
    if (!m_window) {
        ERROR("Window", "Window", "CHECK CONSTRUCTOR");
    }
    else {
        MESSAGE("Window", "Window", "OK");
    }

    // Inicializar ImGui con la ventana de SFML.
    ImGui::SFML::Init(*m_window);
}

/* 
   Destructor.
   Libera los recursos utilizados por la ventana y apaga ImGui.
*/
Window::~Window() {
    // Apagar ImGui.
    ImGui::SFML::Shutdown();
    // Liberar la memoria de la ventana.
    delete m_window;
}

/* 
   Maneja los eventos de la ventana.
   Procesa los eventos del usuario, como cerrar la ventana o cambiar su tamaño.
*/

void Window::handleEvents() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        // Procesar los eventos para ImGui.
        ImGui::SFML::ProcessEvent(event);

        switch (event.type) {
        case sf::Event::Closed:
            // Cerrar la ventana si se detecta el evento de cierre.
            m_window->close();
            break;

        case sf::Event::Resized:
            // Obtener el nuevo tamaño de la ventana.
            unsigned int width = event.size.width;
            unsigned int height = event.size.height;

            // Ajustar la vista de la ventana al nuevo tamaño.
            m_view = m_window->getView();
            m_view.setSize(static_cast<float>(width), static_cast<float>(height));
            m_window->setView(m_view);
            break;
        }
    }
}

/*
   Limpia la ventana para preparar un nuevo frame.
   Borra todo lo que se muestra actualmente en la ventana.
   De otra manera, informa de error.
*/
void Window::clear() {
    if (m_window != nullptr) {
        m_window->clear();
    }
    else {
        ERROR("Window", "clear", "CHECK FOR WINDOW POINTER DATA");
    }
}

/*
   Muestra en pantalla el contenido dibujado.
   Actualiza la ventana con el contenido más reciente.
*/
void Window::display() {
    if (m_window != nullptr) {
        m_window->display();
    }
    else {
        ERROR("Window", "display", "CHECK FOR WINDOW POINTER DATA");
    }
}

/*
   Verifica si la ventana sigue abierta.
   true si la ventana está abierta, false si se ha cerrado.
*/
bool Window::isOpen() const {
    if (m_window != nullptr) {
        return m_window->isOpen();
    }
    else {
        ERROR("Window", "isOpen", "CHECK FOR WINDOW POINTER DATA");
        return false;
    }
}

/*
  Dibuja un objeto en la ventana.
  Recibe cualquier objeto que herede de `sf::Drawable` y lo muestra en la ventana.
  drawable El objeto a dibujar (como un círculo o rectángulo).
*/
void Window::draw(const sf::Drawable& drawable) {
    if (m_window != nullptr) {
        m_window->draw(drawable);
    }
    else {
        ERROR("Window", "draw", "CHECK FOR WINDOW POINTER DATA");
    }
}

/*
   Obtiene un puntero a la ventana interna de SFML.
   Esto permite realizar operaciones directas sobre la ventana de SFML.
   Puntero a `sf::RenderWindow`.
 */
sf::RenderWindow* Window::getWindow() {
    if (m_window != nullptr) {
        return m_window;
    }
    else {
        ERROR("Window", "getWindow", "CHECK FOR WINDOW POINTER DATA");
        return nullptr;
    }
}

/*
  Actualiza la ventana cada frame.
   Calcula el `deltaTime` y actualiza ImGui con ese valor.
 */
void Window::update() {
    // Reiniciar el reloj y obtener el tiempo transcurrido desde el último frame.
    deltaTime = clock.restart();

    // Actualizar ImGui con el nuevo deltaTime.
    ImGui::SFML::Update(*m_window, deltaTime);
}

//Renderiza el contenido de ImGui en la ventana.
void Window::render() {
    ImGui::SFML::Render(*m_window);
}

/* 
   Libera los recursos de la ventana y apaga ImGui.
   Usa la macro `SAFE_PTR_RELEASE` para liberar la memoria de forma segura.
 */
void Window::destroy() {
    ImGui::SFML::Shutdown();
    SAFE_PTR_RELEASE(m_window);
}