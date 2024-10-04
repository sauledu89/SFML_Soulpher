#pragma once  
#include "Prerequisites.h"  
#include "Component.h"  


class Window;

/*
  Clase Entity:
  - Clase base que representa cualquier objeto dentro del entorno gráfico.
  - Gestiona la actualización y renderizado de los componentes asociados a la entidad.
  En un entorno de gráficas computacionales 3D, Entity podría ser utilizada para manejar actores más complejos
  como personajes, cámaras, luces y objetos interactivos, permitiendo agregar y manipular componentes avanzados
  como transformaciones, sistemas de animación y colisiones físicas.
 */
class Entity
{
public:
    /*
      Destructor virtual por defecto.
      - Se utiliza default ya que los recursos asociados a los componentes se gestionan a través de punteros inteligentes.
     */
    virtual ~Entity() = default;

    /*
      Función update.
      - Función virtual pura que debe ser implementada en las clases derivadas.
      - Actualiza el estado de la entidad y sus componentes basándose en el tiempo delta (deltaTime).
      En gráficos 3D, esta función se encargaría de actualizar las posiciones, rotaciones y animaciones de los modelos.
     */
    virtual void update(float deltaTime) = 0;

    /*
      Función render.
      - Función virtual pura que debe ser implementada en las clases derivadas.
      - Encargada de renderizar los componentes gráficos de la entidad.
      En un entorno 3D, render se usaría para dibujar el modelo de la entidad en la pantalla,
      aplicar sombreado y calcular la iluminación en tiempo real.
     */
    virtual void render(Window& window) = 0;

    /*
      Función addComponent.
      - Permite agregar un nuevo componente a la entidad.
      - Utiliza TSharedPointer para manejar la memoria de los componentes de forma segura.
      En un entorno 3D, esta función podría utilizarse para agregar componentes de física, animaciones o efectos visuales.
     */
    template<typename T>
    void addComponent(EngineUtilities::TSharedPointer<T> component)
    {
        // Asegura que el tipo T derive de la clase base Component.
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

        // Convierte el componente a TSharedPointer<Component> y lo almacena en la lista de componentes.
        components.push_back(component.template dynamic_pointer_cast<Component>());
    }

    /*
      Función getComponent.
      - Recupera un componente específico de la entidad basado en su tipo.
      - Permite acceder a funcionalidades específicas de un componente sin necesidad de conocer su tipo exacto.
      En gráficos 3D, se podría usar para obtener componentes como transformaciones, animaciones o sistemas de colisión.
     */
    template<typename T>
    EngineUtilities::TSharedPointer<T> getComponent()
    {
        // Itera sobre los componentes de la entidad.
        for (auto& component : components)
        {
            // Intenta convertir cada componente al tipo específico `T`.
            EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();

            if (specificComponent)  // Si la conversión es exitosa, retornar el componente.
            {
                return specificComponent;
            }
        }

        return EngineUtilities::TSharedPointer<T>();  // Si no se encuentra, retornar un puntero nulo.
    }

protected:
    /*
      Variable "isActived":
      - Bandera que indica si la entidad está activa en la escena.
      - Si isActived es false, la entidad no se renderiza ni se actualiza.
      En gráficos 3D, esta bandera se podría utilizar para gestionar entidades fuera del campo de visión,
      optimizando el rendimiento al evitar calcular o dibujar objetos que no son visibles.
     */
    bool isActived;

    /*
      Variable id:
      - Idntificador único para cada entidad.
      - Se utiliza para diferenciar entre distintas entidades en la escena.
      En entornos 3D, el id puede ser útil para realizar búsquedas rápidas de entidades o para aplicar
      comportamientos específicos a grupos de objetos (por ejemplo, seleccionar todos los enemigos de un tipo específico).
     */
    int id;

    /*
      Vector components:
      - Almacena todos los componentes asociados a la entidad.
      - Cada componente define una funcionalidad específica que puede ser agregada o eliminada dinámicamente.
      En gráficos 3D, components podría contener transformaciones, sistemas de físicas, animaciones, o incluso
      emisores de partículas y fuentes de luz, permitiendo construir actores complejos a partir de componentes modulares.
     */
    std::vector<EngineUtilities::TSharedPointer<Component>> components;
};
