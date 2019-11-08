# Práctica 5

**Nombre:** Humberto Alejandro Ortega Alcocer

**Número de Boleta:** 20166304495

**Fecha:** 24/09/2019

## Tabla de Contenidos

- [Práctica 5](#pr%c3%a1ctica-5)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Introducción](#introducci%c3%b3n)
  - [Desarrollo](#desarrollo)
  - [Prueba](#prueba)
  - [Posibles Mejoras](#posibles-mejoras)
  - [Conclusiones](#conclusiones)
  - [Fuentes](#fuentes)

## Introducción

El protocolo IP permite tener una capa de direccionamiento de red con lo que podemos referirnos a un equipo en particular independientemente de como haya cambiado su configuración física. El protocolo IP funciona gracias al encapsulamiento de los paquetes de la capa inferior añadiendo el siguiente encabezado:

![Ecabezado de IP][ip-header-img]

En esta práctica, escribimos un programa que capture paquetes, determine si son de tipo IP y después nos permita visualizar información referente a los campos del encabezado de forma rápida.

## Desarrollo

Para el desarrollo del programa se realizará la programación de varias rutinas, incluídas:

- Seleccionar tarjeta de red a utilizar durante la captura.
- Seleccionar el número de paquetes a capturar.
- Mostrar información de cada paquete capturado.

## Prueba

El código fuente se proporciona junto con este documento. Una correcta ejecución debe arrojar el siguiente resultado:

```txt
Práctica 5
Analizador de IP
Seleccione una interfaz de red de la siguiente lista:
1) en0
2) p2p0
3) awdl0
4) llw0
5) bridge0
6) utun0
7) en1
8) utun1
9) utun2
10) en5
11) lo0
12) gif0
13) stf0
Ingresa el número de la interfaz de red (1-13): 1
¿Cuántos paquetes deseas capturar? (1-100): 10
Iniciando captura...
Leyendo 10 desde en0

------- Paquete Capturado --------
· MAC Origen: 0C:54:15:A9:79:B9
· MAC Destino: FF:FF:FF:FF:FF:FF
· El paquete es IPv4.
  - La versión es: 4
  - IHL: 5 x 4 = 20 bytes.
  - Tipo de servicio: 00
  - Tamaño Total: 78
  - Tiempo de Vida (TTL): 128
  - Protocolo: 11 (UDP)
  - Checksum: 7505
  - IP Origen: 10.100.78.224
  - IP Destino: 10.100.95.255
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: E8:11:32:E3:1E:1B
· MAC Destino: 33:33:FF:06:93:19
· El paquete NO es IP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: E8:11:32:E3:1E:1B
· MAC Destino: 33:33:00:00:00:02
· El paquete NO es IP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 44:03:2C:46:6D:BF
· MAC Destino: 01:00:5E:00:00:FB
· El paquete es IPv4.
  - La versión es: 4
  - IHL: 5 x 4 = 20 bytes.
  - Tipo de servicio: 00
  - Tamaño Total: 220
  - Tiempo de Vida (TTL): 255
  - Protocolo: 11 (UDP)
  - Checksum: FC2A
  - IP Origen: 10.100.68.238
  - IP Destino: 224.0.0.251
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 28:C6:3F:5D:97:1A
· MAC Destino: FF:FF:FF:FF:FF:FF
· El paquete es IPv4.
  - La versión es: 4
  - IHL: 5 x 4 = 20 bytes.
  - Tipo de servicio: 00
  - Tamaño Total: 48
  - Tiempo de Vida (TTL): 128
  - Protocolo: 11 (UDP)
  - Checksum: 2811
  - IP Origen: 10.100.66.147
  - IP Destino: 10.100.95.255
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 28:C6:3F:5D:97:1A
· MAC Destino: FF:FF:FF:FF:FF:FF
· El paquete es IPv4.
  - La versión es: 4
  - IHL: 5 x 4 = 20 bytes.
  - Tipo de servicio: 00
  - Tamaño Total: 48
  - Tiempo de Vida (TTL): 128
  - Protocolo: 11 (UDP)
  - Checksum: 2810
  - IP Origen: 10.100.66.147
  - IP Destino: 10.100.95.255
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 44:2A:60:DC:DE:DA
· MAC Destino: FF:FF:FF:FF:FF:FF
· El paquete es IPv4.
  - La versión es: 4
  - IHL: 5 x 4 = 20 bytes.
  - Tipo de servicio: 00
  - Tamaño Total: 78
  - Tiempo de Vida (TTL): 64
  - Protocolo: 11 (UDP)
  - Checksum: 8168
  - IP Origen: 10.100.75.14
  - IP Destino: 10.100.95.255
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 28:C6:3F:5D:97:1A
· MAC Destino: FF:FF:FF:FF:FF:FF
· El paquete es IPv4.
  - La versión es: 4
  - IHL: 5 x 4 = 20 bytes.
  - Tipo de servicio: 00
  - Tamaño Total: 48
  - Tiempo de Vida (TTL): 128
  - Protocolo: 11 (UDP)
  - Checksum: 280F
  - IP Origen: 10.100.66.147
  - IP Destino: 10.100.95.255
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 28:C6:3F:5D:97:1A
· MAC Destino: FF:FF:FF:FF:FF:FF
· El paquete es IPv4.
  - La versión es: 4
  - IHL: 5 x 4 = 20 bytes.
  - Tipo de servicio: 00
  - Tamaño Total: 48
  - Tiempo de Vida (TTL): 128
  - Protocolo: 11 (UDP)
  - Checksum: 280E
  - IP Origen: 10.100.66.147
  - IP Destino: 10.100.95.255
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 00:22:FA:13:FD:56
· MAC Destino: FF:FF:FF:FF:FF:FF
· El paquete es IPv4.
  - La versión es: 4
  - IHL: 5 x 4 = 20 bytes.
  - Tipo de servicio: 00
  - Tamaño Total: 78
  - Tiempo de Vida (TTL): 128
  - Protocolo: 11 (UDP)
  - Checksum: 6457
  - IP Origen: 10.100.66.229
  - IP Destino: 10.100.95.255
-------  Fin de Análisis  --------
Fin de programa
 - Humberto Alcocer, 2019
ESCOM. Redes de Computadoras. Práctica 5
```

## Posibles Mejoras

Como posible mejora, podríamos colocar un filtro para que únicamente recibamos paquetes de tipo IP, esto nos facilitaría visualizar la información que queremos sobre algún programa en ejecución que tengamos interés en particular y no únicamente de *todos* los paquetes capturados por la interfaz de red.

## Conclusiones

El protocolo IP es el que ha permitido un despegue en la era de la computación personal, es la base fundamental de como funciona nuestro servicio actual de internet y, a la fecha, sigue siendo empleado en la mayoría de las aplicaciones modernas incluso sin considerarlo directamente. Es interesante, desde la perspectiva de un desarrollador, ver cómo cada pequeña parte hace que funcione algo tan complejo como lo es hoy en día nuestra sociedad de forma digital. Entender IP y sus distintos aspectos de configuración nos permite entender las capas superiores de abstracción (que es dónde generalmente trabajaremos) como TCP y UDP, e incluso más abstractas como lo puede ser HTTP, SMTP, FTP etc. Esta práctica nos ayuda a comprender lo que está pasando y, más importante aún, por qué está pasando.

## Fuentes

- Material visto en clase.

[ip-header-img]: https://telescript.denayer.wenk.be/~hcr/cn/idoceo/images/ip_header.gif