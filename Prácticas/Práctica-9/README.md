# Práctica 9

**Nombre:** Humberto Alejandro Ortega Alcocer

**Número de Boleta:** 20166304495

**Fecha:** 10/10/2019

## Tabla de Contenidos

- [Práctica 9](#pr%c3%a1ctica-9)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Introducción](#introducci%c3%b3n)
  - [Desarrollo](#desarrollo)
  - [Prueba](#prueba)
  - [Posibles Mejoras](#posibles-mejoras)
  - [Conclusiones](#conclusiones)
  - [Fuentes](#fuentes)

## Introducción

Esta práctica conciste en implementar el protocolo de ruteo OSPF, el cual utiliza en el fondo el algoritmo de Dijkstra para operar y buscar la ruta más corta de un punto a otro dentro de la topología de red.

OSPF es un protocolo que tiene ventajas contra RIP en tanto a velocidad y fiabilidad, además que se resuelve el problema de la redistribución cíclica de rutas que tiene RIP.

## Desarrollo

Para el desarrollo de esta práctica, tendremos que replicar la siguiente topología física:

![Topología][topology-img]

## Prueba

Para probar que funciona, haremos pings desde y hacia cada segmento de red disponible. Para esto, anexo una captura de pantalla con las pruebas realizadas que muestran que existe conectividad de extremo a extremo:

![Resultados de pruebas de la red][results-img]

El archivo `practica-9.pkt` es un archivo de Cisco Packet Tracer v7.2, el cual puede abrirse y ejecutarse para corroborar los resultados.

> Es importante saber que a mayor complejidad en nuestra red, tanto a nivel topológico como de configuración, hará que el programa se alente. Por ello, si se presenta algún problema durante las pruebas. Cambiar de modo "En tiempo real" a "Simulación" nos permite evitar la simulación total de la red en todo momento.

## Posibles Mejoras

OSPF es un protocolo muy bueno, sin embargo cuenta con problemas en cuanto a redistribución de rutas en topologías grandes dónde puede darse el caso de desconexión y OSPF tardaría mucho en propagar dicho cambio.

## Conclusiones

OSPF es otro de los protocolos más usados y mayormente implementados en topologías grandes y chicas. Su eficiencia lo vuelve una gran alternativa a RIP y, al buscar el camino más corto, es prueba de que se puede lograr un funcionamiento eficiente y rápido dentro de una red de computadoras.

## Fuentes

- Material visto en clase.

[topology-img]: https://imgur.com/GW1g4Oh.png
[results-img]: https://imgur.com/rCWYxBp.png
