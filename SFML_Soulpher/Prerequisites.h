#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>

#include <SFML/Graphics.hpp>                   // Inclusión de la librería gráfica SFML para trabajar con gráficos y ventanas.
#include "../Include/Memory/TWeakPointer.h"
#include "../Include/Memory/TSharedPointer.h"
#include "../Include/Memory/TStaticPtr.h"
#include "../Include/Memory/TUniquePtr.h"

// Implementación de la Biblioteca ImGui (Interfaz gráfica de usuario).
#include "../Include/IMGUI/imgui.h"       // Biblioteca principal de ImGui.
#include "../Include/IMGUI/imgui-SFML.h"  // Integración de ImGui con SFML.

/*
  Enumeración ShapeType
  - Define los diferentes tipos de formas que se pueden utilizar en la aplicación.
  En el contexto de gráficos 3D, una enumeración similar se podría utilizar para definir tipos de modelos
  como esferas, cubos y otros polígonos complejos. Este tipo de enumeración es útil para abstraer la creación
  de geometrías básicas y facilitar la manipulación de objetos.
*/

enum ShapeType
{
    EMPTY = 0,     // Sin forma definida.
    CIRCLE = 1,    // Círculo.
    RECTANGLE = 2, // Rectángulo.
    TRIANGLE = 3,  // Triángulo.
};

/*
  Macro SAFE_PTR_RELEASE
  - Libera de manera segura un puntero y establece su valor a nullptr para evitar errores de acceso.
  Esta macro es útil en la gestión de memoria en gráficos 3D, donde se utilizan numerosos punteros para almacenar
  objetos como modelos, texturas y buffers de GPU. Al establecer el puntero a nullptr, se evita el uso de
  punteros colgantes (dangling pointers) que podrían causar caídas del programa.
*/

#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

 /*
   Macro MESSAGE
   - Imprime un mensaje de información cuando se crea un recurso.
   Esta macro se utiliza para depurar el estado de creación de recursos, como ventanas o actores,
   mostrando en la consola el nombre de la clase y método donde se ejecuta.
   En gráficas computacionales 3D, este tipo de mensajes es útil para rastrear la creación de objetos
   complejos como mallas y texturas en tiempo real.
 */

#define MESSAGE(classObj, method, state)                      \
{                                                             \
    std::ostringstream os_;                                   \
    os_ << classObj << "::" << method << " : "                \
        << "[CREATION OF RESOURCE" << ": " << state << "] \n";\
    std::cerr << os_.str();                                   \
}

  /*
    Macro ERROR
    - Imprime un mensaje de error detallado y termina la ejecución del programa.
    Esta macro es crucial para detectar errores en tiempo de ejecución, mostrando el nombre de la clase,
    método y un mensaje de error específico. Si ocurre un error, se detiene la ejecución inmediatamente.
    En un entorno 3D, se puede utilizar para identificar fallos en la inicialización de objetos,
    como la carga de texturas, la creación de buffers de vértices, o problemas en el enlace de shaders.
  */

#define ERROR(classObj, method, errorMSG)                         \
{                                                                 \
    std::ostringstream os_;                                       \
    os_ << "ERROR : " << classObj << "::" << method << " : "      \
        << "  Error en los datos de los parámetros [" << errorMSG << "] \n"; \
    std::cerr << os_.str();                                       \
    exit(1);                                                      \
}
