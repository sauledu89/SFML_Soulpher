#pragma once  
#include "Prerequisites.h"
#include "Component.h"  
#include "Window.h"  

/*
  Clase ShapeFactory:
  - Componente que gestiona la creaci�n, manipulaci�n y renderizado de formas en la aplicaci�n.
  - Hereda de la clase Component y permite a los actores tener formas que se pueden visualizar en pantalla.
  En el contexto de gr�ficas computacionales 3D, una clase equivalente podr�a ser un MeshFactory que gestione
  la creaci�n de mallas 3D y su integraci�n con sistemas de materiales y shaders.
*/
class ShapeFactory : public Component
{
public:
    //Constructor por defecto.
    ShapeFactory() = default;

    //Destructor por defecto.
    virtual ~ShapeFactory() = default;

    /*
      Constructor parametrizado.
      - Inicializa la forma con un tipo espec�fico (ShapeType) y asigna el tipo de componente a SHAPE.
    */
    ShapeFactory(ShapeType shapeType);

    /*
      Funci�n createShape.
      - Crea una forma basada en el tipo de `ShapeType` proporcionado.
      Esta funci�n se encarga de instanciar diferentes tipos de formas como c�rculos, tri�ngulos o rect�ngulos
      seg�n se especifique. En un entorno 3D, una funci�n similar podr�a ser utilizada para instanciar diferentes
      tipos de geometr�as (como esferas, cubos o modelos personalizados).
    */
    sf::Shape* createShape(ShapeType shapeType);

    /*
      Funci�n update.
      - Sobrescribe la funci�n base de Component para actualizar la posici�n o el estado de la forma.
      Aqu� se manejar�an las transformaciones de la forma, como la traslaci�n, rotaci�n o escalado.
      En gr�ficos 3D, se podr�a usar para actualizar animaciones de modelos.
    */
    void update(float deltaTime) override;

    /*
      Funci�n render.
      - Dibuja la forma en la ventana proporcionada.
      Al igual que en aplicaciones 3D, esta funci�n se encargar�a de realizar el renderizado de cada
      componente gr�fico, pero utilizando un contexto de gr�ficos 3D (como OpenGL o DirectX).
    */
    void render(Window& window) override;

    /*
      Funci�n setPosition.
      - Establece la posici�n de la forma utilizando coordenadas (x, y) flotantes.
      En el contexto 3D, se utilizar�an vectores de tres dimensiones (x, y, z) para definir la posici�n en el espacio.
    */
    void setPosition(float x, float y);

    /*
      Sobrecarga de la funci�n setPosition.
      - Establece la posici�n utilizando un vector sf::Vector2f.
      En gr�ficos 3D, se podr�an usar vectores 3D (sf::Vector3f) para manipular la ubicaci�n de los modelos en el espacio.
    */
    void setPosition(const sf::Vector2f& position);

    /*
      Funci�n setFillColor.
      - Cambia el color de relleno de la forma.
      En 3D, la manipulaci�n de color se podr�a manejar a trav�s de materiales y shaders que definan la apariencia de la superficie.
    */
    void setFillColor(const sf::Color& color);

    /*
      Funci�n SeeK.
      - Mueve la forma hacia una posici�n objetivo a una velocidad definida.
      Este es un comportamiento b�sico de movimiento (ya mencionado anteriormente en ejemplos de uso),
      que en un entorno 3D se podr�a utilizar para mover modelos hacia un objetivo en el espacio 3D.
    */
    void Seek(const sf::Vector2f& targetPosition, 
        float speed, 
        float deltaTime, 
        float range){
    }

    /*
      Funci�n getShape.
      - Devuelve un puntero a la forma (sf::Shape).
      Esta funci�n permite acceder a la forma para modificar propiedades como posici�n, color y transformaciones.
    */

    // Establece la escala de la forma.
    // scl Vector con los valores de escala en X e Y.
    void setScale(const sf::Vector2f& scl);

    // Establece la rotaci�n de la forma en grados.
    // angle = �ngulo de rotaci�n en grados.
    void setRotation(float angle);

    sf::Shape* getShape();

private:
    sf::Shape* m_shape = nullptr;              // Puntero a la forma gestionada por esta shapeFactory.
    ShapeType m_shapeType = ShapeType::EMPTY;  // Tipo de forma gestionada.
};
