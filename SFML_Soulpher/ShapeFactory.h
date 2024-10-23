#pragma once  
#include "Prerequisites.h"
#include "Component.h"  
#include "Window.h"  

/*
  Clase ShapeFactory:
  - Componente que gestiona la creación, manipulación y renderizado de formas en la aplicación.
  - Hereda de la clase Component y permite a los actores tener formas que se pueden visualizar en pantalla.
  En el contexto de gráficas computacionales 3D, una clase equivalente podría ser un MeshFactory que gestione
  la creación de mallas 3D y su integración con sistemas de materiales y shaders.
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
      - Inicializa la forma con un tipo específico (ShapeType) y asigna el tipo de componente a SHAPE.
    */
    ShapeFactory(ShapeType shapeType);

    /*
      Función createShape.
      - Crea una forma basada en el tipo de `ShapeType` proporcionado.
      Esta función se encarga de instanciar diferentes tipos de formas como círculos, triángulos o rectángulos
      según se especifique. En un entorno 3D, una función similar podría ser utilizada para instanciar diferentes
      tipos de geometrías (como esferas, cubos o modelos personalizados).
    */
    sf::Shape* createShape(ShapeType shapeType);

    /*
      Función update.
      - Sobrescribe la función base de Component para actualizar la posición o el estado de la forma.
      Aquí se manejarían las transformaciones de la forma, como la traslación, rotación o escalado.
      En gráficos 3D, se podría usar para actualizar animaciones de modelos.
    */
    void update(float deltaTime) override;

    /*
      Función render.
      - Dibuja la forma en la ventana proporcionada.
      Al igual que en aplicaciones 3D, esta función se encargaría de realizar el renderizado de cada
      componente gráfico, pero utilizando un contexto de gráficos 3D (como OpenGL o DirectX).
    */
    void render(Window& window) override;

    /*
      Función setPosition.
      - Establece la posición de la forma utilizando coordenadas (x, y) flotantes.
      En el contexto 3D, se utilizarían vectores de tres dimensiones (x, y, z) para definir la posición en el espacio.
    */
    void setPosition(float x, float y);

    /*
      Sobrecarga de la función setPosition.
      - Establece la posición utilizando un vector sf::Vector2f.
      En gráficos 3D, se podrían usar vectores 3D (sf::Vector3f) para manipular la ubicación de los modelos en el espacio.
    */
    void setPosition(const sf::Vector2f& position);

    /*
      Función setFillColor.
      - Cambia el color de relleno de la forma.
      En 3D, la manipulación de color se podría manejar a través de materiales y shaders que definan la apariencia de la superficie.
    */
    void setFillColor(const sf::Color& color);

    /*
      Función SeeK.
      - Mueve la forma hacia una posición objetivo a una velocidad definida.
      Este es un comportamiento básico de movimiento (ya mencionado anteriormente en ejemplos de uso),
      que en un entorno 3D se podría utilizar para mover modelos hacia un objetivo en el espacio 3D.
    */
    void Seek(const sf::Vector2f& targetPosition, 
        float speed, 
        float deltaTime, 
        float range){
    }

    /*
      Función getShape.
      - Devuelve un puntero a la forma (sf::Shape).
      Esta función permite acceder a la forma para modificar propiedades como posición, color y transformaciones.
    */

    // Establece la escala de la forma.
    // scl Vector con los valores de escala en X e Y.
    void setScale(const sf::Vector2f& scl);

    // Establece la rotación de la forma en grados.
    // angle = Ángulo de rotación en grados.
    void setRotation(float angle);

    sf::Shape* getShape();

private:
    sf::Shape* m_shape = nullptr;              // Puntero a la forma gestionada por esta shapeFactory.
    ShapeType m_shapeType = ShapeType::EMPTY;  // Tipo de forma gestionada.
};
