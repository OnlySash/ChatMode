# ChatMode

Proyecto del curso Programación Paralela y Concurrente de la UCR.
El programa consiste en el diseño de una aplicación de mensajería utilizando el lenguaje C en la biblioteca OpenMPI, con la interfaz de Qt. Utilizando conocimientos previos de MPI (Ejemplo de Intersección) y usos anteriores de UI con Qt
El objetivo es crear un chat con estética 8 bits para mujeres con expectativa de crecimiento.   

## Estructura del proyecto

include/    Archivos .h  
src/        Código fuente  
tests/      Casos de prueba  
build/      Archivos compilados  
cli/	    Correr en terminal
ui/	    Correr con interfaz gráfica

## Compilación CLI

Compilar todo:

```sh
make 
```

Limpiar archivos compilados:

```sh
make clean
```

## Ejecución

Los ejecutables se generan en la carpeta build.

Parámetros:



Ejemplos:

```sh

```

## Ejecutar

```sh
make run
```

## Compilación UI

Compilarción  Inicial:

```sh
mkdir build
cd build
```

Compilar todo:

```sh
cmake ..

```

Limpiar archivos compilados:

```sh
cmake clean
```

## Ejecución

Los ejecutables se generan en la carpeta build.

Parámetros:



Ejemplos:

```sh

```

## Ejecutar

```sh
cmake --build .
```

## Logros obtenidos

- Diseño inicial basado en aplicaciones actuales de mensajería desde el punto del usuario
- Creación de proyecto funcional con la implementación de MPI
- Uso de contactos preestablecidos y máximo de caracteres para una mensajería correcta
- Creación de UI por medio de Qt con una aplicación básica donde el cliente representa el rank 1
- Implementación MPI_Init_Thread, Isend, Irecv
- Registro de usuarios conectados por medio del CLI
- Uso de estructuras de datos para manejo de mensajes y tablas asociadas a usuarios


## Dificultades 

- Creación de pruebas unitarias
- Uso de métricas de rendimiento y speedup
- UI robusta e intuitiva

## Referencias 
- https://doc.qt.io/ 
- https://doc.qt.io/qt-6/cmake-get-started.html
