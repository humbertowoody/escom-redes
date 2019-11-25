# Práctica 15

**Nombre:** Humberto Alejandro Ortega Alcocer

**Número de Boleta:** 20166304495

**Fecha:** 21/11/2019

## Tabla de Contenidos

- [Práctica 15](#pr%c3%a1ctica-15)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Introducción](#introducci%c3%b3n)
  - [Desarrollo](#desarrollo)
  - [Prueba](#prueba)
  - [Posibles Mejoras](#posibles-mejoras)
  - [Conclusiones](#conclusiones)
  - [Fuentes](#fuentes)

## Introducción

Este protocolo de capa de transporte brinda las siguientes funciones:

- Entrega de datos bajo la política del mejor esfuerzo (no garantiza que los datos lleguen en orden, o sin duplicados), pero es rápido.
- Direccionamiento en punto de servicio.
- Tiene su especificación en el [RFC 768][rfc-768-url]

## Desarrollo

Para el desarrollo de este programa, tendremos que codificar las siguientes rutinas:

1. Imprimir lista de interfaces de captura.
2. El usuario selecciona una interfaz de captura.
3. El usuario ingresa el número de paquetes a capturar.
4. Compilamos el filtro de captura (`udp`) para únicamente recibir paquetes de **UDP**.
5. Para cada paquete capturado imprimimos su información.

## Prueba

El código fuente se proporciona junto con este documento. Una correcta ejecución debe arrojar el siguiente resultado:

```txt
Práctica 15
Analizador de UDP
Seleccione una interfaz de red de la siguiente lista:
1) en0
2) bridge0
3) p2p0
4) awdl0
5) llw0
6) utun0
7) en1
8) utun1
9) en5
10) lo0
11) gif0
12) stf0
Ingresa el número de la interfaz de red (1-12): 1
¿Cuántos paquetes deseas capturar? (1-100): 10
Iniciando captura...
Leyendo 10 desde en0

------- Paquete Capturado --------
· MAC Origen: A4:50:46:35:38:D3
· MAC Destino: FF:FF:FF:FF:FF:FF
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 17
· Longitud de paquete IP (hlen): 20
· Análisis de UDP:
  ~ Puerto de Origen: 17408
  ~ Puerto de Destino: 17152
  ~ Longitud: 9729
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 00:24:2C:0B:BD:02
· MAC Destino: FF:FF:FF:FF:FF:FF
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 17
· Longitud de paquete IP (hlen): 20
· Análisis de UDP:
  ~ Puerto de Origen: 35072
  ~ Puerto de Destino: 35072
  ~ Longitud: 14848
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: A4:50:46:35:38:D3
· MAC Destino: FF:FF:FF:FF:FF:FF
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 17
· Longitud de paquete IP (hlen): 20
· Análisis de UDP:
  ~ Puerto de Origen: 17408
  ~ Puerto de Destino: 17152
  ~ Longitud: 12801
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: E0:9D:31:D9:45:95
· MAC Destino: FF:FF:FF:FF:FF:FF
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 17
· Longitud de paquete IP (hlen): 20
· Análisis de UDP:
  ~ Puerto de Origen: 33750
  ~ Puerto de Destino: 33750
  ~ Longitud: 3841
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 40:88:05:F7:6B:D1
· MAC Destino: FF:FF:FF:FF:FF:FF
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 17
· Longitud de paquete IP (hlen): 20
· Análisis de UDP:
  ~ Puerto de Origen: 61355
  ~ Puerto de Destino: 48202
  ~ Longitud: 10496
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D0:04:01:F8:1B:17
· MAC Destino: FF:FF:FF:FF:FF:FF
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 17
· Longitud de paquete IP (hlen): 20
· Análisis de UDP:
  ~ Puerto de Origen: 5601
  ~ Puerto de Destino: 5601
  ~ Longitud: 12288
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 00:E1:8C:9D:8A:14
· MAC Destino: FF:FF:FF:FF:FF:FF
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 17
· Longitud de paquete IP (hlen): 20
· Análisis de UDP:
  ~ Puerto de Origen: 35072
  ~ Puerto de Destino: 35072
  ~ Longitud: 14848
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 00:E1:8C:9D:8A:14
· MAC Destino: FF:FF:FF:FF:FF:FF
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 17
· Longitud de paquete IP (hlen): 20
· Análisis de UDP:
  ~ Puerto de Origen: 35072
  ~ Puerto de Destino: 35072
  ~ Longitud: 14848
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 00:E1:8C:9D:8A:14
· MAC Destino: FF:FF:FF:FF:FF:FF
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 17
· Longitud de paquete IP (hlen): 20
· Análisis de UDP:
  ~ Puerto de Origen: 35072
  ~ Puerto de Destino: 35072
  ~ Longitud: 14848
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 00:E1:8C:9D:8A:14
· MAC Destino: FF:FF:FF:FF:FF:FF
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 17
· Longitud de paquete IP (hlen): 20
· Análisis de UDP:
  ~ Puerto de Origen: 35072
  ~ Puerto de Destino: 35072
  ~ Longitud: 14848
-------  Fin de Análisis  --------
Fin de programa
 - Humberto Alcocer, 2019
ESCOM. Redes de Computadoras. Práctica 15
```

## Posibles Mejoras

Si pudiéramos capturar y almacenar toda la información de análisis de paquetes UDP, podríamos encontrar patrones de conexiones para identificar servicios de video/audio en streaming así como juegos de video y aplicaciones que empleen el protocolo UDP.

## Conclusiones

UDP es el protocolo por el cual la transmisión de información en tiempo real de audio y video. Es uno de los más importantes dentro de los protocolos de capa de transporte y al realizar el análisis es más clara la funcionalidad y el modo de operación del mismo.

## Fuentes

- Material visto en clase.

[rfc-768-url]: https://tools.ietf.org/html/rfc768
