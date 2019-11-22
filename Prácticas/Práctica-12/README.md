# Práctica 12

**Nombre:** Humberto Alejandro Ortega Alcocer

**Número de Boleta:** 20166304495

**Fecha:** 19/11/2019

## Tabla de Contenidos

- [Práctica 12](#pr%c3%a1ctica-12)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Introducción](#introducci%c3%b3n)
    - [Tipos y Códigos ICMP](#tipos-y-c%c3%b3digos-icmp)
  - [Desarrollo](#desarrollo)
  - [Prueba](#prueba)
  - [Posibles Mejoras](#posibles-mejoras)
  - [Conclusiones](#conclusiones)
  - [Fuentes](#fuentes)

## Introducción

En esta práctica analizaremos el protoclo **ICMP**, siglas para el *Internet Control Message Protocol*, con el cual podemos enviar mensajes de error y de información operativa para un mejor diagnóstico de una red de datos. Para analizar ICMP, crearemos un programa que sea capaz de leer paquetes al vuelo, extraiga la trama y pueda descomponerla hasta arrojar información de un paquete ICMP tan explícita como sea posible.

### Tipos y Códigos ICMP

A continuación se anexa una tabla con los distintos códigos y tipos disponibles en ICMP para mostrar en el mensaje:

| Tipo  | Código |                 Descripción                  |
| :---: | :----: | :------------------------------------------: |
|   0   |   0    |                  echo reply                  |
|   3   |   0    |             network unreachable              |
|   3   |   1    |               host unreachable               |
|   3   |   2    |             protocol unreachable             |
|   3   |   3    |               port unreachable               |
|   3   |   4    |     fragmentation needed but DF bit set      |
|   3   |   5    |             source route failed              |
|   3   |   6    |         destination network unknown          |
|   3   |   7    |           destination host unknown           |
|   3   |   9    | destination host administratively prohibited |
|   4   |   0    |                source quench                 |
|   5   |   0    |             redirect for network             |
|   5   |   1    |              redirect for host               |
|   5   |   2    |         redirect for TOS and network         |
|   8   |   0    |                 echo request                 |
|  11   |   0    |             TTL=0 durint transit             |
|  12   |   0    |                IP header bad                 |
|  13   |   0    |              timestamp request               |
|  14   |   0    |              timestamp response              |

## Desarrollo

Para el desarrollo del programa, se realizará la programación de varias rutinas:

1. Seleccionar la tarjeat de red a usar para la captura.
2. Seleccionar el número de paquetesa a capturar.
3. Mostrar la información relevante de cada paquete capturado.

## Prueba

El código fuente se proporciona junto con este documento. Una correcta ejecución debe arrojar el siguiente resultado:

```txt
Práctica 12
Analizador de ICMPP
Seleccione una interfaz de red de la siguiente lista:
1) en0
2) bridge0
3) p2p0
4) awdl0
5) llw0
6) utun0
7) en1
8) utun1
9) lo0
10) gif0
11) stf0
Ingresa el número de la interfaz de red (1-11): 1
¿Cuántos paquetes deseas capturar? (1-100): 20
Iniciando captura...
Leyendo 20 desde en0

------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 94:FE:9D:62:3B:00
· Ether Type: 2048
· El paquete es IP.
· Protocolo:
· Longitud de paquete IP (hlen):
  ~ ICMP tipo:
  ~ ICMP código:
  ~ ICMP checksum:34908
  ~ ICMP descripción: echo request
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 94:FE:9D:62:3B:00
· MAC Destino: D4:61:9D:2D:E1:58
· Ether Type: 2048
· El paquete es IP.
· Protocolo:
· Longitud de paquete IP (hlen):
  ~ ICMP tipo:
  ~ ICMP código:
  ~ ICMP checksum:34916
  ~ ICMP descripción: echo reply
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 94:FE:9D:62:3B:00
· MAC Destino: 33:33:FF:99:B3:05
· Ether Type: 34525
· El paquete NO es IP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 94:FE:9D:62:3B:00
· MAC Destino: 33:33:FF:FE:DE:3A
· Ether Type: 34525
· El paquete NO es IP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 94:FE:9D:62:3B:00
· Ether Type: 2048
· El paquete es IP.
· Protocolo:
· Longitud de paquete IP (hlen):
  ~ ICMP tipo:
  ~ ICMP código:
  ~ ICMP checksum:23511
  ~ ICMP descripción: echo request
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 94:FE:9D:62:3B:00
· MAC Destino: D4:61:9D:2D:E1:58
· Ether Type: 2048
· El paquete es IP.
· Protocolo:
· Longitud de paquete IP (hlen):
  ~ ICMP tipo:
  ~ ICMP código:
  ~ ICMP checksum:23519
  ~ ICMP descripción: echo reply
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 94:FE:9D:62:3B:00
· Ether Type: 2048
· El paquete es IP.
· Protocolo:
· Longitud de paquete IP (hlen):
  ~ ICMP tipo:
  ~ ICMP código:
  ~ ICMP checksum:40278
  ~ ICMP descripción: echo request
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 94:FE:9D:62:3B:00
· MAC Destino: D4:61:9D:2D:E1:58
· Ether Type: 2048
· El paquete es IP.
· Protocolo:
· Longitud de paquete IP (hlen):
  ~ ICMP tipo:
  ~ ICMP código:
  ~ ICMP checksum:40286
  ~ ICMP descripción: echo reply
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 94:FE:9D:62:3B:00
· MAC Destino: D4:61:9D:2D:E1:58
· Ether Type: 34525
· El paquete NO es IP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 94:FE:9D:62:3B:00
· Ether Type: 34525
· El paquete NO es IP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 94:FE:9D:62:3B:00
· MAC Destino: 33:33:FF:FE:DE:3A
· Ether Type: 34525
· El paquete NO es IP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 94:FE:9D:62:3B:00
· MAC Destino: 33:33:FF:92:8F:89
· Ether Type: 34525
· El paquete NO es IP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 94:FE:9D:62:3B:00
· MAC Destino: 33:33:FF:D3:BC:56
· Ether Type: 34525
· El paquete NO es IP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 94:FE:9D:62:3B:00
· MAC Destino: 33:33:FF:1A:FA:49
· Ether Type: 34525
· El paquete NO es IP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 94:FE:9D:62:3B:00
· MAC Destino: 33:33:FF:4C:5F:D6
· Ether Type: 34525
· El paquete NO es IP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 94:FE:9D:62:3B:00
· MAC Destino: 33:33:FF:CE:50:9B
· Ether Type: 34525
· El paquete NO es IP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 94:FE:9D:62:3B:00
· MAC Destino: 33:33:FF:A0:28:7C
· Ether Type: 34525
· El paquete NO es IP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 94:FE:9D:62:3B:00
· MAC Destino: 33:33:FF:5E:DA:AB
· Ether Type: 34525
· El paquete NO es IP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 94:FE:9D:62:3B:00
· Ether Type: 2048
· El paquete es IP.
· Protocolo:
· Longitud de paquete IP (hlen):
  ~ ICMP tipo:
  ~ ICMP código:
  ~ ICMP checksum:52685
  ~ ICMP descripción: echo request
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 94:FE:9D:62:3B:00
· MAC Destino: D4:61:9D:2D:E1:58
· Ether Type: 2048
· El paquete es IP.
· Protocolo:
· Longitud de paquete IP (hlen):
  ~ ICMP tipo:
  ~ ICMP código:
  ~ ICMP checksum:52693
  ~ ICMP descripción: echo reply
-------  Fin de Análisis  --------
Fin de programa
 - Humberto Alcocer, 2019
ESCOM. Redes de Computadoras. Práctica 12
```

## Posibles Mejoras

Como posible mejora, nuestro programa podría mantener un registro de los paquetes tanto en origen como destino, así como su relación con el encabezado IP que lo contiene permitiéndonos visualizar de forma más concreta el comportamiento de la red.

## Conclusiones

ICMP es uno de los protocolos más útiles para el diagnóstico y operación de una red de computadoras. Nos proporciona una serie de herramientas básicas como `ping`, `traceroute` y `dig` que son fundamentales durante la instalación y configuración de una red de computadoras actualmente. Es interesante notar como, para que nuestro programa arroje resultados más evidentes, es necesario tener múltiples líneas de comando ejecutando operaciones como las mencionadas anteriormente (`ping`, `traceroute`, `dig`) sin las cuales el programa simplemente no encontrará mensajes ICMP dado que no son comunes para la operación básica de una red.

## Fuentes

- Material visto en clase.
