#pragma once  
#include "Prerequisites.h"  
#include "Component.h"  


class Window;

/*
  Clase Entity:
  - Clase base que representa cualquier objeto dentro del entorno gr�fico.
  - Gestiona la actualizaci�n y renderizado de los componentes asociados a la entidad.
  En un entorno de gr�ficas computacionales 3D, Entity podr�a ser utilizada para manejar actores m�s complejos
  como personajes, c�maras, luces y objetos interactivos, permitiendo agregar y manipular componentes avanzados
  como transformaciones, sistemas de animaci�n y colisiones f�sicas.
 */
class Entity
{
public:
    /*
      Destructor virtual por defecto.
      - Se utiliza default ya que los recursos asociados a los componentes se gestionan a trav�s de punteros inteligentes.
     */
    virtual ~Entity() = default;

    /*
      Funci�n update.
      - Funci�n virtual pura que debe ser implementada en las clases derivadas.
      - Actualiza el estado de la entidad y sus componentes bas�ndose en el tiempo delta (deltaTime).
      En gr�ficos 3D, esta funci�n se encargar�a de actualizar las posiciones, rotaciones y animaciones de los modelos.
     */
    virtual void update(float deltaTime) = 0;

    /*
      Funci�n render.
      - Funci�n virtual pura que debe ser implementada en las clases derivadas.
      - Encargada de renderizar los componentes gr�ficos de la entidad.
      En un entorno 3D, render se usar�a para dibujar el modelo de la entidad en la pantalla,
      aplicar sombreado y calcular la iluminaci�n en tiempo real.
     */
    virtual void render(Window& window) = 0;

    /*
      Funci�n addComponent.
      - Permite agregar un nuevo componente a la entidad.
      - Utiliza TSharedPointer para manejar la memoria de los componentes de forma segura.
      En un entorno 3D, esta funci�n podr�a utilizarse para agregar componentes de f�sica, animaciones o efectos visuales.
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
      Funci�n getComponent.
      - Recupera un componente espec�fico de la entidad basado en su tipo.
      - Permite acceder a funcionalidades espec�ficas de un componente sin necesidad de conocer su tipo exacto.
      En gr�ficos 3D, se podr�a usar para obtener componentes como transformaciones, animaciones o sistemas de colisi�n.
     */
    template<typename T>
    EngineUtilities::TSharedPointer<T> getComponent()
    {
        // Itera sobre los componentes de la entidad.
        for (auto& component : components)
        {
            // Intenta convertir cada componente al tipo espec�fico `T`.
            EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();

            if (specificComponent)  // Si la conversi�n es exitosa, retornar el componente.
            {
                return specificComponent;
            }
        }

        return EngineUtilities::TSharedPointer<T>();  // Si no se encuentra, retornar un puntero nulo.
    }

protected:
    /*
      Variable "isActived":
      - Bandera que indica si la entidad est� activa en la escena.
      - Si isActived es false, la entidad no se renderiza ni se actualiza.
      En gr�ficos 3D, esta bandera se podr�a utilizar para gestionar entidades fuera del campo de visi�n,
      optimizando el rendimiento al evitar calcular o dibujar objetos que no son visibles.
     */
    bool isActived;

    /*
      Variable id:
      - Idntificador �nico para cada entidad.
      - Se utiliza para diferenciar entre distintas entidades en la escena.
      En entornos 3D, el id puede ser �til para realizar b�squedas r�pidas de entidades o para aplicar
      comportamientos espec�ficos a grupos de objetos (por ejemplo, seleccionar todos los enemigos de un tipo espec�fico).
     */
    int id;

    /*
      Vector components:
      - Almacena todos los componentes asociados a la entidad.
      - Cada componente define una funcionalidad espec�fica que puede ser agregada o eliminada din�micamente.
      En gr�ficos 3D, components podr�a contener transformaciones, sistemas de f�sicas, animaciones, o incluso
      emisores de part�culas y fuentes de luz, permitiendo construir actores complejos a partir de componentes modulares.
     */
    std::vector<EngineUtilities::TSharedPointer<Component>> components;
};
