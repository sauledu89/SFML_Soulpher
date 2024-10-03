#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>

#include <SFML/Graphics.hpp>
#include "../Include/Memory/TWeakPointer.h"
#include "../Include/Memory/TSharedPointer.h"
#include "../Include/Memory/TStaticPtr.h"
#include "../Include/Memory/TUniquePtr.h"


enum ShapeType
{
    EMPTY = 0,    
    CIRCLE = 1,   
    RECTANGLE = 2,
    TRIANGLE = 3, 
};

#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

#define MESSAGE(classObj, method, state)                      \
{                                                             \
    std::ostringstream os_;                                   \
    os_ << classObj << "::" << method << " : "                \
        << "[CREATION OF RESOURCE" << ": " << state << "] \n";\
    std::cerr << os_.str();                                   \
}

#define ERROR(classObj, method, errorMSG)                         \
{                                                                 \
    std::ostringstream os_;                                       \
    os_ << "ERROR : " << classObj << "::" << method << " : "      \
        << "  Error en los datos de los parámetros [" << errorMSG << "] \n"; \
    std::cerr << os_.str();                                       \
    exit(1);                                                      \
}
