#pragma once  
#include "Prerequisites.h"  

/*
  Declaración adelantada de la clase Window.
  - Se usa para informar al compilador de la existencia de la clase Window sin necesidad de incluir todo el archivo de cabecera.
  - Esto ayuda a reducir dependencias innecesarias y acelera el tiempo de compilación.
 */
class Window;

/*
  Enumeración ComponentType:
  - Define los diferentes tipos de componentes que se pueden asignar a un actor.
  - Cada valor representa un tipo específico de comportamiento o funcionalidad dentro de un actor.
  En un contexto de gráficos 3D, componentes como TRANSFORM y PHYSICS se usan para definir la posición y comportamiento físico de los objetos en la escena, mientras que otros como `SPRITE` o `SHAPE` se extienden para representar modelos 3D y fuentes de iluminación.
 */
enum ComponentType
{
    NONE = 0,        
    TRANSFORM = 1,  
    SPRITE = 3,      
    PHYSICS = 4,     
    AUDIOSOURCE = 5, 
    SHAPE = 6        
};

/*
  Clase Component:
  - Clase base para todos los componentes que se pueden asociar a un actor.
  - Define una estructura común para componentes como ShapeFactory (explicada anteriormente), PhysicsComponent y otros.
  En gráficos computacionales 3D, una clase Component podría ser extendida para definir comportamientos avanzados
  como sistemas de partículas, controladores de animaciones o cámaras.
 */
class Component
{
public:
    /*
      Constructor 
     */
    Component() = default;

    /*
      Constructor parametrizado.
      - Inicializa el componente con un tipo específico (ComponentType).
      - Se utiliza para identificar el tipo de componente y ajustar la funcionalidad según el valor de m_type
      En gráficos 3D, este valor se podría usar para identificar tipos de mallas, luces, cámaras o incluso efectos visuales.
     */
    Component(const ComponentType type) : m_type(type) {};

    /*
      Destructor por defecto.
      Se usa default ya que no se implementa ninguna operación específica de liberación de recursos.
     */
    virtual ~Component() = default;

    /*
      Función update
      - Función virtual pura que debe ser sobrescrita en las clases derivadas.
      - Encargada de actualizar el estado del componente basándose en el tiempo transcurrido (deltaTime).
      En el contexto de gráficos 3D, esta función podría usarse para actualizar la posición de un modelo,
      calcular transformaciones de matrices o gestionar animaciones basadas en esqueletos.
     */
    virtual void update(float deltaTime) = 0;

    /*
      Función render.
      - Función virtual pura para dibujar el componente en la ventana.
      - Debe ser implementada por las clases derivadas como ShapeFactory.
      En gráficos 3D, render podría enviar los vértices del componente a la GPU, calcular la iluminación y
      aplicar shaders personalizados.
     */
    virtual void render(Window& window) = 0;

    /*
      Función getType.
      - Devuelve el tipo de componente (ComponentType).
      - Permite a los actores identificar y gestionar diferentes componentes asignados.
      En un entorno de gráficas computacionales 3D, se podría utilizar para identificar dinámicamente
      qué tipo de sistema gráfico, físico o de entrada se está usando en cada entidad.
     */
    ComponentType getType() const
    {
        return m_type;
    }

protected:
    /*
      Variable m_type:
      - Almacena el tipo de componente que se ha asignado a la instancia actual.
      - Utilizada para identificar el comportamiento específico de cada componente dentro de un actor
      En gráficos 3D, m_type podría extenderse con valores adicionales para manejar componentes de animación,
      sistemas de sombras, o emisores de partículas.
     */
    ComponentType m_type;  // Tipo de componente asignado.
};
