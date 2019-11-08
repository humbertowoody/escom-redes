# Práctica 6

**Nombre:** Humberto Alejandro Ortega Alcocer

**Número de Boleta:** 20166304495

**Fecha:** 15/10/2019

## Tabla de Contenidos

- [Práctica 6](#pr%c3%a1ctica-6)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Introducción](#introducci%c3%b3n)
  - [Desarrollo](#desarrollo)
    - [Protocolo](#protocolo)
  - [Prueba](#prueba)
  - [Posibles Mejoras](#posibles-mejoras)
  - [Conclusiones](#conclusiones)
  - [Fuentes](#fuentes)

## Introducción

El objetivo de esta práctica es implementar nuestro propio protocolo de red. Para esto, nuestro protocolo se implementará sobre *Ethernet*, por lo que en general, nuestro proceso necesitará llenar los datos pertenecientes a la dirección MAC destino y a la dirección MAC origen, el tipo lo colocaremos a un valor predefinido en clase `0X1601` y, finalmente, el campo CRC será calculado por nuestra tarjeta de red. El objetivo será enviar un archivo con nuestro protocolo por lo que, para lograr la transmisión, deberemos diseñar nuestra estructura que permita enviar el archivo.

## Desarrollo

Lo primero que debemos tomar en consideración para realizar el desarrollo del programa, es la estructura con la que contará nuestro protocolo de comunicación, para ello, hemos definido la siguiente:

| Destino | Origen | Nombre de Archivo | # Secuencia |  # Ack  |   Y    |       *Datos*       |
| :-----: | :----: | :---------------: | :---------: | :-----: | :----: | :-----------------: |
| 1 byte  | 1 byte |      4 bytes      |   2 bytes   | 2 bytes | 1 byte | 1474 bytes (máximo) |

Esa estructura, será el PDU de la trama *Ethernet* que enviaremos. Cuenta con los campos suficientes para realizar un manejo correcto de la transmisión así como de otros aspectos relevantes para el manejo de la conexión.

### Protocolo

Teniendo la definición de la cabecera, ahora definiremos el modo de trabajar de nuestro protocolo. Para esto, tomaremos en consideración un modelo *Parar y Esperar*, dónde el archivo será dividido en los paquetes que sean necesarios y se enviarán de forma secuencial. En general el proceso será el siguiente:

1. Leer un archivo.
2. Dividirlo en `n` partes semi-iguales.
3. Comenzar a transmitir el archivo.
4. Esperar un *ACK* por cada *Sec* enviado.
5. En caso de no recibir ACK, marcar error... supongo?

## Prueba

\*_Nota: Si cuenta con Visual Studio Code (VSCode), se incluye una carpeta con las tareas de compilación por lo que únicamente se requiere usar el comando de compilación (`cmd + b` en Mac, `ctrl + b` en Windows/Linux) para compilar el programa._

## Posibles Mejoras

## Conclusiones

## Fuentes
