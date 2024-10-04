#pragma once  
#include "Prerequisites.h"  
#include "Entity.h"  
#include "ShapeFactory.h"  

/*
  Clase `Actor`:
  - Hereda de la clase Entity y representa cualquier entidad gráfica dentro de la aplicación.
  - Los actores pueden tener múltiples componentes que definen sus características y comportamientos.
  En gráficos computacionales 3D, la clase Actor podría representar elementos más complejos como
  personajes con animaciones, vehículos, luces y cámaras, permitiendo gestionar el ciclo de vida y
  comportamiento de cada uno en la escena.
 */
class Actor : public Entity
{
public:
    /*
      Constructor por defecto.
      - Inicializa un actor con valores predeterminados.
      - En gráficos 3D, este constructor podría utilizarse para definir el tipo de actor (estático, dinámico, etc.)
        y preparar las variables iniciales de transformación y apariencia.
     */
    Actor() = default;

    /*
      Constructor parametrizado
      - Inicializa el actor con un nombre específico (actorName).
      - Este nombre se puede utilizar para identificar al actor en la escena o para fines de depuración.
      En gráficos 3D, los nombres de actores son útiles para gestionar entidades en jerarquías,
      como partes de un esqueleto, submodelos o nodos de una escena.
     */
    Actor(std::string actorName);

    /*
      Destructor por defecto.
     
      Se utiliza default ya que los recursos se gestionan de forma segura con punteros inteligentes.
     */
    ~Actor() = default;

    /*
      Función `update`.

      - Actualiza el estado del actor y sus componentes en cada ciclo del programa.
      En gráficos 3D, se podría utilizar para actualizar posiciones, rotaciones, animaciones y otros comportamientos
      como la simulación de físicas y la interacción con otros actores.
     */
    void update(float deltaTime) override;

    /*
      Función render.
      - Renderiza el actor en la ventana proporcionada.
      En un entorno de gráficos 3D, esta función se encargaría de enviar los vértices, aplicar shaders,
      calcular la iluminación y dibujar el modelo tridimensional en la pantalla.
     */
    void render(Window& window) override;

    /*
      Función `destroy`
      - Libera los recursos asociados al actor y sus componentes.
      En gráficos 3D, destroy podría usarse para eliminar modelos de la memoria, liberar texturas y
      otros recursos asociados a la GPU.
     */
    void destroy();

    /*
      Función getComponent.
      - Recupera un componente específico asociado al actor basado en su tipo.
      Esta función permite acceder a las funcionalidades de un componente sin necesidad de conocer su tipo exacto.
      En gráficos 3D, se podría usar para recuperar componentes de transformaciones, físicas, sistemas de animación,
      cámaras o cualquier otra funcionalidad asociada al actor.
     */
    template <typename T>
    EngineUtilities::TSharedPointer<T> getComponent();

private:
    /*
      Variable m_name:
      - Almacena el nombre del actor.
      - Útil para identificar actores en la escena, facilitar la depuración y realizar búsquedas.
      En gráficos 3D, los nombres de los actores pueden usarse para estructurar la jerarquía de objetos en la escena,
      definir nodos en un esqueleto de animación o identificar elementos de un sistema de partículas.
     */
    std::string m_name = "Actor";  // Nombre del actor.
};

/*
  Función getComponent.
  - Recupera un componente específico del actor basado en el tipo T.
  - Itera sobre los componentes del actor para encontrar uno que coincida con el tipo solicitado.
  En gráficos 3D, getComponent se puede usar para acceder a transformaciones (posición, rotación, escala),
  físicas (colisiones, gravedad) o comportamientos personalizados (IA, partículas).
 */
template<typename T>
inline EngineUtilities::TSharedPointer<T> Actor::getComponent()
{
    // Iterar sobre los componentes del actor.
    for (auto& component : components)
    {
        // Intentar convertir el componente actual al tipo específico T.
        EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();

        if (specificComponent)  // Si la conversión es exitosa, retornar el componente encontrado.
        {
            return specificComponent;
        }
    }

   // Si no se encuentra el componente del tipo solicitado, retornar un puntero nulo.
    return EngineUtilities::TSharedPointer<T>();
}
