#pragma once  
#include "Prerequisites.h"  
#include "Entity.h"  
#include "ShapeFactory.h"  

/*
  Clase `Actor`:
  - Hereda de la clase Entity y representa cualquier entidad gr�fica dentro de la aplicaci�n.
  - Los actores pueden tener m�ltiples componentes que definen sus caracter�sticas y comportamientos.
  En gr�ficos computacionales 3D, la clase Actor podr�a representar elementos m�s complejos como
  personajes con animaciones, veh�culos, luces y c�maras, permitiendo gestionar el ciclo de vida y
  comportamiento de cada uno en la escena.
 */
class Actor : public Entity
{
public:
    /*
      Constructor por defecto.
      - Inicializa un actor con valores predeterminados.
      - En gr�ficos 3D, este constructor podr�a utilizarse para definir el tipo de actor (est�tico, din�mico, etc.)
        y preparar las variables iniciales de transformaci�n y apariencia.
     */
    Actor() = default;

    /*
      Constructor parametrizado
      - Inicializa el actor con un nombre espec�fico (actorName).
      - Este nombre se puede utilizar para identificar al actor en la escena o para fines de depuraci�n.
      En gr�ficos 3D, los nombres de actores son �tiles para gestionar entidades en jerarqu�as,
      como partes de un esqueleto, submodelos o nodos de una escena.
     */
    Actor(std::string actorName);

    /*
      Destructor por defecto.
     
      Se utiliza default ya que los recursos se gestionan de forma segura con punteros inteligentes.
     */
    ~Actor() = default;

    /*
      Funci�n `update`.

      - Actualiza el estado del actor y sus componentes en cada ciclo del programa.
      En gr�ficos 3D, se podr�a utilizar para actualizar posiciones, rotaciones, animaciones y otros comportamientos
      como la simulaci�n de f�sicas y la interacci�n con otros actores.
     */
    void update(float deltaTime) override;

    /*
      Funci�n render.
      - Renderiza el actor en la ventana proporcionada.
      En un entorno de gr�ficos 3D, esta funci�n se encargar�a de enviar los v�rtices, aplicar shaders,
      calcular la iluminaci�n y dibujar el modelo tridimensional en la pantalla.
     */
    void render(Window& window) override;

    /*
      Funci�n `destroy`
      - Libera los recursos asociados al actor y sus componentes.
      En gr�ficos 3D, destroy podr�a usarse para eliminar modelos de la memoria, liberar texturas y
      otros recursos asociados a la GPU.
     */
    void destroy();

    /*
      Funci�n getComponent.
      - Recupera un componente espec�fico asociado al actor basado en su tipo.
      Esta funci�n permite acceder a las funcionalidades de un componente sin necesidad de conocer su tipo exacto.
      En gr�ficos 3D, se podr�a usar para recuperar componentes de transformaciones, f�sicas, sistemas de animaci�n,
      c�maras o cualquier otra funcionalidad asociada al actor.
     */
    template <typename T>
    EngineUtilities::TSharedPointer<T> getComponent();

private:
    /*
      Variable m_name:
      - Almacena el nombre del actor.
      - �til para identificar actores en la escena, facilitar la depuraci�n y realizar b�squedas.
      En gr�ficos 3D, los nombres de los actores pueden usarse para estructurar la jerarqu�a de objetos en la escena,
      definir nodos en un esqueleto de animaci�n o identificar elementos de un sistema de part�culas.
     */
    std::string m_name = "Actor";  // Nombre del actor.
};

/*
  Funci�n getComponent.
  - Recupera un componente espec�fico del actor basado en el tipo T.
  - Itera sobre los componentes del actor para encontrar uno que coincida con el tipo solicitado.
  En gr�ficos 3D, getComponent se puede usar para acceder a transformaciones (posici�n, rotaci�n, escala),
  f�sicas (colisiones, gravedad) o comportamientos personalizados (IA, part�culas).
 */
template<typename T>
inline EngineUtilities::TSharedPointer<T> Actor::getComponent()
{
    // Iterar sobre los componentes del actor.
    for (auto& component : components)
    {
        // Intentar convertir el componente actual al tipo espec�fico T.
        EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();

        if (specificComponent)  // Si la conversi�n es exitosa, retornar el componente encontrado.
        {
            return specificComponent;
        }
    }

   // Si no se encuentra el componente del tipo solicitado, retornar un puntero nulo.
    return EngineUtilities::TSharedPointer<T>();
}
