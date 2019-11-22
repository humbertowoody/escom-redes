# Práctica 13

**Nombre:** Humberto Alejandro Ortega Alcocer

**Número de Boleta:** 20166304495

**Fecha:** 21/11/2019

## Tabla de Contenidos

- [Práctica 13](#pr%c3%a1ctica-13)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Introducción](#introducci%c3%b3n)
  - [Desarrollo](#desarrollo)
  - [Prueba](#prueba)
  - [Posibles Mejoras](#posibles-mejoras)
  - [Conclusiones](#conclusiones)
  - [Fuentes](#fuentes)

## Introducción

El protocolo **IGMP** (*Internet Group Message Protocol*), es un protocolo enfocado en la transmisión a grupos de internet para distribuciones de mensajes en masa. Eso quiere decir, que podemos transmitir paquetes TCP/UDP a una dirección multicast y, vía el protocolo IGMP, podremos unirnos y comenzar a recibir esos paquetes. En esta práctica realizaremos un sniffer capaz de interpretar los paquetes de IGMP.

## Desarrollo

Para el desarrollo de este programa, tendremos que codificar las siguientes rutinas:

1. Imprimir lista de interfaces de captura.
2. El usuario selecciona una interfaz de captura.
3. El usuario ingresa el número de paquetes a capturar.
4. Compilamos el filtro de captura (`igmp`) para únicamente recibir paquetes de **IGMP**.
5. Para cada paquete capturado imprimimos su información.

En esta práctica usaremos los filtros de captura dado que el tráfico de IGMP se ve minimizado contra el resto del tráfico fluyendo por nuestra interfaz de captura, permitiéndonos únicamente capturar mensajes de IGMP.

## Prueba

El código fuente se proporciona junto con este documento. Una correcta ejecución debe arrojar el siguiente resultado:

```txt
Práctica 13
Analizador de IGMP
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
¿Cuántos paquetes deseas capturar? (1-100): 10
Iniciando captura...
Leyendo 10 desde en0

------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 01:00:5E:00:00:16
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 2
· Longitud de paquete IP (hlen): 24
· Análisis de IGMP:
  ~ Tipo: reporte (IGMPv3).
  ~ Tiempo: 0ms
  ~ Grupo: 0.0.0.1
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 01:00:5E:00:00:16
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 2
· Longitud de paquete IP (hlen): 24
· Análisis de IGMP:
  ~ Tipo: reporte (IGMPv3).
  ~ Tiempo: 0ms
  ~ Grupo: 0.0.0.1
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 01:00:5E:00:00:16
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 2
· Longitud de paquete IP (hlen): 24
· Análisis de IGMP:
  ~ Tipo: reporte (IGMPv3).
  ~ Tiempo: 0ms
  ~ Grupo: 0.0.0.1
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 01:00:5E:00:00:16
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 2
· Longitud de paquete IP (hlen): 24
· Análisis de IGMP:
  ~ Tipo: reporte (IGMPv3).
  ~ Tiempo: 0ms
  ~ Grupo: 0.0.0.1
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 01:00:5E:00:00:16
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 2
· Longitud de paquete IP (hlen): 24
· Análisis de IGMP:
  ~ Tipo: reporte (IGMPv3).
  ~ Tiempo: 0ms
  ~ Grupo: 0.0.0.1
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 01:00:5E:00:00:16
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 2
· Longitud de paquete IP (hlen): 24
· Análisis de IGMP:
  ~ Tipo: reporte (IGMPv3).
  ~ Tiempo: 0ms
  ~ Grupo: 0.0.0.1
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 01:00:5E:00:00:16
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 2
· Longitud de paquete IP (hlen): 24
· Análisis de IGMP:
  ~ Tipo: reporte (IGMPv3).
  ~ Tiempo: 0ms
  ~ Grupo: 0.0.0.1
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 01:00:5E:00:00:16
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 2
· Longitud de paquete IP (hlen): 24
· Análisis de IGMP:
  ~ Tipo: reporte (IGMPv3).
  ~ Tiempo: 0ms
  ~ Grupo: 0.0.0.1
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 01:00:5E:00:00:16
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 2
· Longitud de paquete IP (hlen): 24
· Análisis de IGMP:
  ~ Tipo: reporte (IGMPv3).
  ~ Tiempo: 0ms
  ~ Grupo: 0.0.0.1
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 01:00:5E:00:00:16
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 2
· Longitud de paquete IP (hlen): 24
· Análisis de IGMP:
  ~ Tipo: reporte (IGMPv3).
  ~ Tiempo: 0ms
  ~ Grupo: 0.0.0.1
-------  Fin de Análisis  --------
Fin de programa
 - Humberto Alcocer, 2019
ESCOM. Redes de Computadoras. Práctica 12
```

## Posibles Mejoras

Como posible mejora, se podría realizar el análisis de los paquetes capturados para determinar el número de equipos que se han unido a un grupo de IGMP así como los tiempos y tipos de mensajes más comunes en la red.

## Conclusiones

IGMP es un protocolo que nos permite realizar distribución de información en una red de computadoras de forma simple para atacar grandes cantidades de equipos clientes que deseen transmitir y recibir información dentro de un grupo de internet.

## Fuentes

- Material visto en clase.
