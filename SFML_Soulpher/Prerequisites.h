#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>

#include <SFML/Graphics.hpp>                   // Inclusi�n de la librer�a gr�fica SFML para trabajar con gr�ficos y ventanas.
#include "../Include/Memory/TWeakPointer.h"
#include "../Include/Memory/TSharedPointer.h"
#include "../Include/Memory/TStaticPtr.h"
#include "../Include/Memory/TUniquePtr.h"

// Implementaci�n de la Biblioteca ImGui (Interfaz gr�fica de usuario).
#include "../Include/IMGUI/imgui.h"       // Biblioteca principal de ImGui.
#include "../Include/IMGUI/imgui-SFML.h"  // Integraci�n de ImGui con SFML.

/*
  Enumeraci�n ShapeType
  - Define los diferentes tipos de formas que se pueden utilizar en la aplicaci�n.
  En el contexto de gr�ficos 3D, una enumeraci�n similar se podr�a utilizar para definir tipos de modelos
  como esferas, cubos y otros pol�gonos complejos. Este tipo de enumeraci�n es �til para abstraer la creaci�n
  de geometr�as b�sicas y facilitar la manipulaci�n de objetos.
*/

enum ShapeType
{
    EMPTY = 0,     // Sin forma definida.
    CIRCLE = 1,    // C�rculo.
    RECTANGLE = 2, // Rect�ngulo.
    TRIANGLE = 3,  // Tri�ngulo.
};

/*
  Macro SAFE_PTR_RELEASE
  - Libera de manera segura un puntero y establece su valor a nullptr para evitar errores de acceso.
  Esta macro es �til en la gesti�n de memoria en gr�ficos 3D, donde se utilizan numerosos punteros para almacenar
  objetos como modelos, texturas y buffers de GPU. Al establecer el puntero a nullptr, se evita el uso de
  punteros colgantes (dangling pointers) que podr�an causar ca�das del programa.
*/

#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

 /*
   Macro MESSAGE
   - Imprime un mensaje de informaci�n cuando se crea un recurso.
   Esta macro se utiliza para depurar el estado de creaci�n de recursos, como ventanas o actores,
   mostrando en la consola el nombre de la clase y m�todo donde se ejecuta.
   En gr�ficas computacionales 3D, este tipo de mensajes es �til para rastrear la creaci�n de objetos
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
    - Imprime un mensaje de error detallado y termina la ejecuci�n del programa.
    Esta macro es crucial para detectar errores en tiempo de ejecuci�n, mostrando el nombre de la clase,
    m�todo y un mensaje de error espec�fico. Si ocurre un error, se detiene la ejecuci�n inmediatamente.
    En un entorno 3D, se puede utilizar para identificar fallos en la inicializaci�n de objetos,
    como la carga de texturas, la creaci�n de buffers de v�rtices, o problemas en el enlace de shaders.
  */

#define ERROR(classObj, method, errorMSG)                         \
{                                                                 \
    std::ostringstream os_;                                       \
    os_ << "ERROR : " << classObj << "::" << method << " : "      \
        << "  Error en los datos de los par�metros [" << errorMSG << "] \n"; \
    std::cerr << os_.str();                                       \
    exit(1);                                                      \
}
