# Práctica 3

**Nombre:** Humberto Alejandro Ortega Alcocer

**Número de Boleta:** 20166304495

**Fecha:** 5/03/2019

## Tabla de Contenidos

- [Práctica 3](#pr%C3%A1ctica-3)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Introducción](#introducci%C3%B3n)
  - [Desarrollo](#desarrollo)
  - [Prueba](#prueba)
  - [Posibles Mejoras](#posibles-mejoras)
  - [Conclusiones](#conclusiones)
  - [Fuentes](#fuentes)

## Introducción

El objetivo de esta práctica es realizar un análisis sobre tramas predefinidas de *LLC* (802.3 IEEE) que se basan en el protocolo *HDLC*. Para esto, debemos leer los paquetes de un archivo (`paquetes.pcap`) debido a que los paquetes de *LLC* son descartados al llegar a la tarjeta de red por los que no serán detectados por nuestra librería.

Para desarrollar correctamente la práctica, se deben de conocer los distintos tipos de tramas que pueden presentarse. Primeramente, nos encontraremos con una trama de tipo **802.3** como se muestra a continuación:

|MAC Destino|MAC Origen|Longitud|DSAP|SSAP|Control|Datos|CRC|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|6 bytes|6 bytes|2 bytes|1 byte|1 byte|2 bytes|46 - 1500 bytes|4 bytes|

De dicho encabezado, extraeremos la siguiente información relevante:

- MAC Destino
- MAC Origen
- Longitud
- DSAP
- SSAP
- Control

El campo `longitud` tiene una especial tarea ya que especifica si la trama estará en modo **normal** o en modo **extendida**. La diferencia entre ambos tipos recae en la longitud de los campos, el modo **extendido** cuenta con el doble de bits, permitiendo un mayor número de banderas de control, esto se definió como una manera de mantener espacio para futuras implementaciones que requirieran dichos campos.

Cuando la `longitud` de la trama excede el valor (decimal) de 3, esto nos indica que la información de dicha trama se encuentra en modo **extendido**, si el valor es 3, será en modo **normal**, con las siguientes diferencias para el análisis:



## Desarrollo

Se comienza leyendo un archivo de paquetes, el cual, por default será `paquetes.pcap`, el cual podrá ser modificado pasando el nombre de otro archivo a analizar desde los argumentos del programa a modo:

`$ ./llc.out otros-paquetes-capturados.pcap` 

De esa forma, permitimos al usuario analizar el archivo que se desee analizar y tener un *default* para que pueda funcionar el programa en su forma más simple.

Después de realizar todo el procedimiento para abrir el archivo con la información así como manejar errores y demás, sse realiza la llamada a la función que iterará por cada paquete y realizará el análisis pertinente. Dicha función, realizará la tarea de extraer los datos e imprimirlos en pantalla con un formato que permita al usuario vislumbrar de forma clara el contenido del paquete así como el comportamiento que está teniendo. 

## Prueba

El código de la práctica se encuentra en el archivo: `llc.cpp` y, para compilarlo, se deberá ejecutar el siguiente comando (Linux o MacOS únicamente): 

`$ g++ llc.cpp -lpcap -o llc.out`

Una vez compilado el archivo, se podrá ejecutar de las siguientes maneras:

- `$ ./llc.out`: El cual ejecutará el programa con el archivo de paquetes *default* y procederá a realizar el análisis de los mismos.
- `$ ./llc.out mi-otro-archivo.pcap`: El cual ejecutará el programa analizando los paquetes contenidos dentro de `mi-otro-archivo.pcap` e imprimirá el análisis de los mismos. 

*Nota\*: Si cuenta con Visual Studio Code (VSCode), se incluye una carpeta con las tareas de compilación por lo que únicamente se requiere usar el comando de compilación (`cmd + b` en Mac, `ctrl + b` en Windows/Linux) para compilar el programa.*

## Posibles Mejoras

Para que el programa sea más eficiente, podría abstraerse la lógica implementada para el análisis de LLC dentro de una *cabecera* que permita el análisis de forma agnóstica, así como realizar una validación de los datos recibidos.

## Conclusiones

## Fuentes
