#pragma once  
#include "Prerequisites.h"  

/*
  Declaraci�n adelantada de la clase Window.
  - Se usa para informar al compilador de la existencia de la clase Window sin necesidad de incluir todo el archivo de cabecera.
  - Esto ayuda a reducir dependencias innecesarias y acelera el tiempo de compilaci�n.
 */
class Window;

/*
  Enumeraci�n ComponentType:
  - Define los diferentes tipos de componentes que se pueden asignar a un actor.
  - Cada valor representa un tipo espec�fico de comportamiento o funcionalidad dentro de un actor.
  En un contexto de gr�ficos 3D, componentes como TRANSFORM y PHYSICS se usan para definir la posici�n y comportamiento f�sico de los objetos en la escena, mientras que otros como `SPRITE` o `SHAPE` se extienden para representar modelos 3D y fuentes de iluminaci�n.
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
  - Define una estructura com�n para componentes como ShapeFactory (explicada anteriormente), PhysicsComponent y otros.
  En gr�ficos computacionales 3D, una clase Component podr�a ser extendida para definir comportamientos avanzados
  como sistemas de part�culas, controladores de animaciones o c�maras.
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
      - Inicializa el componente con un tipo espec�fico (ComponentType).
      - Se utiliza para identificar el tipo de componente y ajustar la funcionalidad seg�n el valor de m_type
      En gr�ficos 3D, este valor se podr�a usar para identificar tipos de mallas, luces, c�maras o incluso efectos visuales.
     */
    Component(const ComponentType type) : m_type(type) {};

    /*
      Destructor por defecto.
      Se usa default ya que no se implementa ninguna operaci�n espec�fica de liberaci�n de recursos.
     */
    virtual ~Component() = default;

    /*
      Funci�n update
      - Funci�n virtual pura que debe ser sobrescrita en las clases derivadas.
      - Encargada de actualizar el estado del componente bas�ndose en el tiempo transcurrido (deltaTime).
      En el contexto de gr�ficos 3D, esta funci�n podr�a usarse para actualizar la posici�n de un modelo,
      calcular transformaciones de matrices o gestionar animaciones basadas en esqueletos.
     */
    virtual void update(float deltaTime) = 0;

    /*
      Funci�n render.
      - Funci�n virtual pura para dibujar el componente en la ventana.
      - Debe ser implementada por las clases derivadas como ShapeFactory.
      En gr�ficos 3D, render podr�a enviar los v�rtices del componente a la GPU, calcular la iluminaci�n y
      aplicar shaders personalizados.
     */
    virtual void render(Window& window) = 0;

    /*
      Funci�n getType.
      - Devuelve el tipo de componente (ComponentType).
      - Permite a los actores identificar y gestionar diferentes componentes asignados.
      En un entorno de gr�ficas computacionales 3D, se podr�a utilizar para identificar din�micamente
      qu� tipo de sistema gr�fico, f�sico o de entrada se est� usando en cada entidad.
     */
    ComponentType getType() const
    {
        return m_type;
    }

protected:
    /*
      Variable m_type:
      - Almacena el tipo de componente que se ha asignado a la instancia actual.
      - Utilizada para identificar el comportamiento espec�fico de cada componente dentro de un actor
      En gr�ficos 3D, m_type podr�a extenderse con valores adicionales para manejar componentes de animaci�n,
      sistemas de sombras, o emisores de part�culas.
     */
    ComponentType m_type;  // Tipo de componente asignado.
};
