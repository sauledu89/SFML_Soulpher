#include "Prerequisites.h"
#include "Actor.h"

/*
 * Actor.cpp
 * Implementaci�n de la clase Actor. Esta clase representa cualquier entidad gr�fica en el juego
 * que puede tener m�ltiples componentes como formas, transformaciones y comportamientos espec�ficos.
 * Cada actor tiene la capacidad de actualizarse y renderizarse, as� como almacenar y gestionar m�ltiples componentes.
 */

 // Constructor que inicializa un actor con un nombre espec�fico.
 // Aqu� se define el nombre del actor y se agregan componentes b�sicos como ShapeFactory y Transform.
 // @param actorName Nombre del actor que ser� utilizado para su identificaci�n.
Actor::Actor(std::string actorName)
{
    // Guardamos el nombre del actor para identificarlo f�cilmente durante el desarrollo y la depuraci�n.
    m_name = actorName;

    // Creaci�n del componente ShapeFactory que se encargar� de definir las formas geom�tricas del actor.
    EngineUtilities::TSharedPointer<ShapeFactory> shape = EngineUtilities::MakeShared<ShapeFactory>();
    addComponent(shape);  // A�adimos ShapeFactory a la lista de componentes del actor.

    // Creaci�n del componente Transform que gestiona la posici�n, rotaci�n y escala del actor.
    // Este componente permite manipular las transformaciones espaciales del actor.
    EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
    addComponent(transform);  // Agregamos el componente Transform al actor para manejar sus transformaciones.

    // Actualmente, el actor solo tiene dos componentes: ShapeFactory y Transform.
    // En el futuro, se pueden agregar otros componentes como Sprite, Physics, AudioSource, etc.,
    // para extender el comportamiento del actor seg�n sea necesario.
}

// Funci�n update que se llama en cada frame para actualizar la l�gica interna del actor.
// @param deltaTime El tiempo transcurrido desde la �ltima actualizaci�n.
// Este par�metro es �til para realizar animaciones y c�lculos basados en tiempo real.
void Actor::update(float deltaTime)
{
    // Esta funci�n est� vac�a en esta implementaci�n porque el actor actualmente no tiene l�gica espec�fica.
    // Se puede utilizar para mover al actor, cambiar sus propiedades o ejecutar comportamientos adicionales.
}

// Renderiza todos los componentes gr�ficos del actor en la ventana especificada.
// @param window Referencia a la ventana donde se dibujar�n los componentes gr�ficos del actor.
void Actor::render(Window& window)
{
    // Recorremos todos los componentes asociados al actor y verificamos si son de tipo ShapeFactory.
    // Si lo son, obtenemos la forma (Shape) y la dibujamos en la ventana.
    for (unsigned int i = 0; i < components.size(); i++)
    {
        // dynamic_pointer_cast se usa para convertir de manera segura el componente a ShapeFactory.
        // Si la conversi�n es exitosa, se dibuja la forma correspondiente.
        if (components[i].dynamic_pointer_cast<ShapeFactory>())
        {
            window.draw(*components[i].dynamic_pointer_cast<ShapeFactory>()->getShape());
        }
    }
}

// Destruye el actor y libera todos los recursos asociados a sus componentes.
// La liberaci�n de recursos es crucial para evitar fugas de memoria y mantener el rendimiento del juego.
// En esta implementaci�n, la gesti�n de memoria se realiza de manera autom�tica gracias a los punteros inteligentes.
void Actor::destroy()
{
    // Esta funci�n est� preparada para liberar cualquier recurso adicional si es necesario.
    // Actualmente, no es necesario liberar manualmente los componentes porque se manejan con TSharedPointer.
}