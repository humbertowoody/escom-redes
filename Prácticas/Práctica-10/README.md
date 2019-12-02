# Práctica 10

**Nombre:** Humberto Alejandro Ortega Alcocer

**Número de Boleta:** 20166304495

**Fecha:** 10/10/2019

## Tabla de Contenidos

- [Práctica 10](#pr%c3%a1ctica-10)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Introducción](#introducci%c3%b3n)
  - [Desarrollo](#desarrollo)
  - [Prueba](#prueba)
  - [Posibles Mejoras](#posibles-mejoras)
  - [Conclusiones](#conclusiones)
  - [Fuentes](#fuentes)

## Introducción

En esta práctica, realizamos la implementación de una topología de red que será ruteada con OSPF y RIP. Esto implica configurar la interconexión entre ambos protocolos para la redistribución de las rutas y que puedan operar ambos de forma correcta dentro de la aplicación.

## Desarrollo

Para el desarrollo de esta práctica, tendremos que replicar la siguiente topología física:

![Topología][topology-img]

## Prueba

Para probar que funciona, haremos pings desde y hacia cada segmento de red disponible. Para esto, anexo una captura de pantalla con las pruebas realizadas que muestran que existe conectividad de extremo a extremo:

![Resultados de pruebas de la red][results-img]

El archivo `practica-10.pkt` es un archivo de Cisco Packet Tracer v7.2, el cual puede abrirse y ejecutarse para corroborar los resultados.

> Es importante saber que a mayor complejidad en nuestra red, tanto a nivel topológico como de configuración, hará que el programa se alente. Por ello, si se presenta algún problema durante las pruebas. Cambiar de modo "En tiempo real" a "Simulación" nos permite evitar la simulación total de la red en todo momento.

## Posibles Mejoras

RIP y OSPF son protocolos conocidos por sus problemas en redes de topologías extensas en dónde las rutas pueden llegar a confundirse dada la conectividad de extremo a extremo. Una mejor configuración sería tener únicamente un solo protocolo operando lo cual disminuye el riesgo de rutas duplicadas o erróneas.

## Conclusiones

Redistribuir rutas en OSPF y RIP es una de las labores que, como Ingenieros en Sistemas, debemos ser capaces de realizar para enlazar dos redes que cuenten con dichos protocolos ya implementados. Es interesante ver los tiempos que toma redistribuir las rutas y en los errores que se pueden presentar.

## Fuentes

- Material visto en clase.

[topology-img]: https://imgur.com/c5C4XxE.png
[results-img]: https://imgur.com/UqhRdrZ.png
