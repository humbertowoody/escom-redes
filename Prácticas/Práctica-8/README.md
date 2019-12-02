# Práctica 8

**Nombre:** Humberto Alejandro Ortega Alcocer

**Número de Boleta:** 20166304495

**Fecha:** 10/10/2019

## Tabla de Contenidos

- [Práctica 8](#pr%c3%a1ctica-8)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Introducción](#introducci%c3%b3n)
  - [Desarrollo](#desarrollo)
  - [Prueba](#prueba)
  - [Posibles Mejoras](#posibles-mejoras)
  - [Conclusiones](#conclusiones)
  - [Fuentes](#fuentes)

## Introducción

En esta práctica implementaremos el protocolo de ruteo dinámico RIP en una topología de red estándar. RIP es un protocolo que nos permite, de forma dinámica, rutear los paquetes dentro de una red a manera de que cada ruta se pueda descubrir de forma automática para que la red no dependa de un operador que tenga que definir cada una de las rutas posibles dentro de la red que, además de ser tedioso, puede resultar imposible con topologías grandes que tengan millones de rutas estáticas dentro de si.

## Desarrollo

Para el desarrollo de esta práctica, tendremos que replicar la siguiente topología física:

![Topología][topology-img]

## Prueba

Para probar que funciona, haremos pings desde y hacia cada segmento de red disponible. Para esto, anexo una captura de pantalla con las pruebas realizadas que muestran que existe conectividad de extremo a extremo:

![Resultados de pruebas de la red][results-img]

El archivo `practica-8.pkt` es un archivo de Cisco Packet Tracer v7.2, el cual puede abrirse y ejecutarse para corroborar los resultados.

> Es importante saber que a mayor complejidad en nuestra red, tanto a nivel topológico como de configuración, hará que el programa se alente. Por ello, si se presenta algún problema durante las pruebas. Cambiar de modo "En tiempo real" a "Simulación" nos permite evitar la simulación total de la red en todo momento.

## Posibles Mejoras

RIP es un protocolo que tiene problemas cuando un segmento de red desaparece ya que puede entrar en un bucle infinito de propagación de rutas. Aunado a ese problema, el hecho de que la comunicación se realize vía plana sobre UDP permite a un atacante envenenar la tabla de ruteo y manipular la red a voluntad causando daños en operatividad y/o extrayendo información sensible que pueda circular por la misma.

## Conclusiones

RIP es uno de los protocolos más antiguos para ruteo dinámico dentro de redes de computadoras y será uno de los que más contacto lleguemos a tener si trabajamos con topologías antiguas. Es importante conocer cómo se configura y cuáles son los pasos para que la configuración sea exitosa, así como las pruebas y las limitantes del protocolo.

## Fuentes

- Material visto en clase.

[topology-img]: https://imgur.com/QEzR80G.png
[results-img]: https://imgur.com/5Y6ZBp7.png
