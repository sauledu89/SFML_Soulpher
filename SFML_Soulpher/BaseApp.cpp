#include "BaseApp.h"

/*
   Ejecuci�n de la aplicaci�n. 
   Este m�todo mantiene la aplicaci�n en un bucle continuo, manejando eventos,
   Llama constantemente a los m�todos update y render, hasta que se cierre la ventaana
   int, C�digo de salida (0 si la ejecuci�n fue exitosa).
*/
int BaseApp::run() {
    if (!initialize()) {
        ERROR("BaseApp", "run", "Initialization failed. Check method validations.");
    }
    while (m_window->isOpen()) {
        m_window->handleEvents();
        update();
        render();
    }
    cleanup();
    return 0;
}

/* 
   Inicializa los recursos necesarios, como actores y texturas.
   true para inicializaci�n exitosa, false si ocurri� un error.
*/

bool BaseApp::initialize() {
    // Crear la ventana principal.
    m_window = new Window(800, 600, "SFML_SOULPHER");
    if (!m_window) {
        ERROR("BaseApp", "initialize", "Error al crear la ventana.");
        return false;
    }

    // Cargar la textura del circuito.
    if (!texture.loadFromFile("C:/Users/chalu/OneDrive/Documentos/GitHub/SFML_Soulpher/bin/MarioKart sprite-png/Circuit.png")) {
        std::cout << "Error al cargar la textura del circuito" << std::endl;
        return false;
    }

    // Crear y configurar el Track (pista).
    Track = EngineUtilities::MakeShared<Actor>("Track");
    if (!Track.isNull()) {
        auto trackTransform = Track->getComponent<Transform>();
        Track->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);
        trackTransform->setPosition(sf::Vector2f(0.0f, 0.0f));
        trackTransform->setRotation(0.0f);
        trackTransform->setScale(sf::Vector2f(11.0f, 12.0f));
        Track->getComponent<ShapeFactory>()->getShape()->setTexture(&texture);
    }

    // Funci�n para cargar y asignar texturas a personajes.
    auto loadCharacter = [this](sf::Texture& texture, const std::string& path, const std::string& name) {
        if (!texture.loadFromFile(path)) {
            std::cout << "Error al cargar la textura de " << name << std::endl;
            return false;
        }
        return true;
        };

    // Personaje y su ruta de textura.
    std::vector<std::pair<sf::Texture*, std::string>> characters = {
        {&Mario, "tile000.png"},
    };

    // Cargar texturas de los personajes.
    for (const auto& [texture, path] : characters) {
        if (!loadCharacter(*texture, "C:/Users/chalu/OneDrive/Documentos/GitHub/SFML_Soulpher/bin/MarioKart sprite-png/" + path, path)) {
            return false;
        }
    }

    // Crear el actor Circle (ejemplo con Mario).
    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (!Circle.isNull()) {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
        auto circleTransform = Circle->getComponent<Transform>();
        circleTransform->setPosition(sf::Vector2f(720.0f, 350.0f)); // 720, 350 Para iniciar en la l�nea de salida.
        circleTransform->setRotation(0.0f);
        circleTransform->setScale(sf::Vector2f(1.0f, 1.0f));
        Circle->getComponent<ShapeFactory>()->getShape()->setTexture(&Mario);
    }

    return true;
}

/* 
   Actualiza la l�gica del juego cada frame.
   Actualizaci�n de los actores, posici�n del rat�n y movimiento del c�rculo.
*/
void BaseApp::update() {
    m_window->update();

    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    if (!Track.isNull()) Track->update(m_window->deltaTime.asSeconds());
    if (!Triangle.isNull()) Triangle->update(m_window->deltaTime.asSeconds());

    if (!Circle.isNull()) {
        Circle->update(m_window->deltaTime.asSeconds());

        sf::Vector2f currentPosition = Circle->getComponent<Transform>()->getPosition();
        float mouseDistance = std::sqrt(
            std::pow(mousePosF.x - currentPosition.x, 2) + std::pow(mousePosF.y - currentPosition.y, 2)
        );

        if (mouseDistance < 100.0f) {
            isFollowingMouse = true;
            sf::Vector2f newPos = currentPosition + (mousePosF - currentPosition) * m_window->deltaTime.asSeconds();
            Circle->getComponent<Transform>()->setPosition(newPos);
        }
        else {
            isFollowingMouse = false;
            updateMovement(m_window->deltaTime.asSeconds(), Circle);
        }
    }
}


   // Renderiza los actores y la interfaz gr�fica de ImGui.
 
void BaseApp::render() {
    m_window->clear();

    if (!Track.isNull()) Track->render(*m_window);
    if (!Circle.isNull()) Circle->render(*m_window);
    if (!Triangle.isNull()) Triangle->render(*m_window);
    
    //Texto en el recuadro de interfaz de IMGUI

    ImGui::Begin("MARIOKART MAP");
    ImGui::Text("PLAYER 1 --> MARIO");
    ImGui::End();

    m_window->render();
    m_window->display();
}

/*
   Cleanup para liberar los recursos utilizados por la aplicaci�n.
   Destruir la ventana y libera la memoria asignada.

*/
void BaseApp::cleanup() {
    m_window->destroy();
    delete m_window;
}

/*
   Controla el movimiento del c�rculo entre puntos predefinidos.
   Si el c�rculo no est� siguiendo al rat�n, se mueve autom�ticamente entre los  waypoints.
*/
void BaseApp::updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle) {
    if (circle.isNull()) return;

    auto transform = circle->getComponent<Transform>();
    sf::Vector2f currentPos = transform->getPosition();
    sf::Vector2f targetPos = waypoints[currentWaypoint];

    sf::Vector2f direction = targetPos - currentPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0.0f) direction /= distance;

    float speed = 150.0f;  // Velocidad del c�rculo.
    sf::Vector2f newPos = currentPos + direction * speed * deltaTime;

    if (distance < 10.0f) {
        currentWaypoint = (currentWaypoint + 1) % waypoints.size();
    }
    else {
        transform->setPosition(newPos);
    }
}