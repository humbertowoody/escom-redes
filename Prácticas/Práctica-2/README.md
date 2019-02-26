# Práctica 2

Humberto Alejandro Ortega Alcocer
20166304495
Fecha: 12/02/2019

## Tabla de Contenidos

- [Práctica 2](#pr%C3%A1ctica-2)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Introducción](#introducci%C3%B3n)
  - [Desarrollo](#desarrollo)
    - [IP](#ip)
    - [TCP y UDP](#tcp-y-udp)
  - [Prueba](#prueba)
  - [Posibles Mejoras](#posibles-mejoras)
  - [Conclusiones](#conclusiones)
  - [Fuentes](#fuentes)

## Introducción

El objetivo de esta práctica es calcular y, de ser necesario, corregir el campo `Checksum` del encabezado
de **IP** y de **TCP** o **UDP**. El checksum es una de las funciones elementales para el correcto
funcionamiento de la pila de protocolos TCP/IP y por esto mismo es importante conocer el funcionamiento
así como las distintas variables que puede tener el procedimiento.

## Desarrollo

El proceso del cálculo de Checksum es simple:

1. Se toma el arreglo de datos que serán analizados.
2. Se dividen en _palabras_ de 16 bits.
3. Se realiza la suma tomando en cuenta los acarreos.

Para cada parte del paquete, se deben tomar distintas consideraciones, esto dependiendo de si es IP, TCP o UDP, lo que estemos analizando.

### IP

Para _IP_, lo único que debemos realizar es ejecutar el algoritmo de _Checksum_ sobre el encabezado de IP. El resultado será:

- 0 si el checksum es **correcto**.
- Diferente a 0 si el checksum es **incorrecto**.

Para corregirlo, colocamos el campo _Checksum_ del encabezado IP en 0's y ejecutamos el algoritmo.

### TCP y UDP

Para TCP y UDP es necesario formar algo llamado un **pseudo encabezado**. El _pseudo encabezado_ se conforma de una serie de datos que, añadidos al resto del paquete de la capa de transporte (llamados PDU), nos permiten verificar que los datos llegaron correctamente.

El esquema del _pseudo encabezado_ es:

![Pseudo Encabezado TCP/UDP](http://www.tcpipguide.com/free/diagrams/tcppseudoheader.png)

En la parte dónde dice _TCP Segment Length_, se refiere a la **longitud del PDU** que, básicamente, es la longitud total de los datos contenidos dentro del paquete IP, es decir, la longitud del encabezado TCP/UDP + los datos.

Para realizar el cálculo del checksum, lo que se hace es hacer un arreglo conteniendo el pseudo encabezado y el segmento TCP/UDP, y realizar la operación sobre el arreglo resultante. El resultado será:

![Pseudo Encabezado + Paquete TCP/UDP](http://www.tcpipguide.com/free/diagrams/tcppseudocalc.png)

Y el resultado de analizar dicho arreglo será:

- 0 si el checksum es **correcto**.
- Diferente a 0 si el checksum es **incorrecto**.

Para corregir el checksum, se coloca el campo _Checksum_ del encabezado TCP o UDP (según sea el caso), en 0 y se realiza la operación de nuevo con el arreglo que contiene el pseudo encabezado y el segmento TCP o UDP.

## Prueba

El código para la prueba se encuentra en el archivo `checksum.cpp` y se puede compilar con el comando:

`g++ checksum.cpp -lpcap -o Checksum.out`

El programa arroja una salida con análisis de cada paquete y sus respectivos campos de Checksum.

\*_Nota: Si cuenta con Visual Studio Code (VSCode), se incluye una carpeta con las tareas de compilación por lo que únicamente se requiere usar el comando de compilación (`cmd + b` en Mac, `ctrl + b` en Windows/Linux) para compilar el programa._

## Posibles Mejoras

El cálculo del Checksum es un elemento realmente simple que no requiere mejoras, sin embargo, el programa realizado durante la práctica puede sufrir mejoras en cuanto a desempeño analizando las operaciones a nivel de bits que se están ejecutando para ser optimizadas.

## Conclusiones

El cálculo de Checksum es un elemento fundamental para el correcto funcionamiento y operación de las redes de computadoras. El hecho de que sea una operación que se pueda programar a nivel de hardware aumenta mucho más la eficiencia y vuelve sencilla la detección de error en segmentos de TCP/UDP o paquetes IP.

## Fuentes

- Clase del Profesor.
- [TCP Checksum Calculation and the TCP "Pseudo Header"](http://www.tcpipguide.com/free/t_TCPChecksumCalculationandtheTCPPseudoHeader.htm)
- [How is TCP & UDP Checksum Calculated?](https://www.slashroot.in/how-is-tcp-and-udp-checksum-calculated)
