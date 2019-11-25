# Práctica 14

**Nombre:** Humberto Alejandro Ortega Alcocer

**Número de Boleta:** 20166304495

**Fecha:** 21/11/2019

## Tabla de Contenidos

- [Práctica 14](#pr%c3%a1ctica-14)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Introducción](#introducci%c3%b3n)
  - [Desarrollo](#desarrollo)
  - [Prueba](#prueba)
  - [Posibles Mejoras](#posibles-mejoras)
  - [Conclusiones](#conclusiones)
  - [Fuentes](#fuentes)

## Introducción

Este protocolo de capa de transporte brinda las siguientes funciones:

- Entrega en orden, sin duplicados, sin errores. **Control de error de extremo a extremo**.
- Control de flujo.
- Direccionamiento en punto de servicio.
- Tiene su especificación en [RFC 793][rfc-793-link].

## Desarrollo

Para el desarrollo de este programa, tendremos que codificar las siguientes rutinas:

1. Imprimir lista de interfaces de captura.
2. El usuario selecciona una interfaz de captura.
3. El usuario ingresa el número de paquetes a capturar.
4. Compilamos el filtro de captura (`tcp`) para únicamente recibir paquetes de **TCP**.
5. Para cada paquete capturado imprimimos su información.

## Prueba

El código fuente se proporciona junto con este documento. Una correcta ejecución debe arrojar el siguiente resultado:

```txt
Práctica 14
Analizador de TCP
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
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 60:9C:9F:1F:99:80
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 6
· Longitud de paquete IP (hlen): 20
· Análisis de TCP:
  ~ Puerto de Origen: 42691
  ~ Puerto de Destino: 47873
  ~ Número de secuencia: 2948652681
  ~ Número de ack: 3512369687
  ~ Longitud: P
  ~ Banderas:
    + CWR: Apagado
    + ECE: Apagado
    + URG: Apagado
    + ACK: Encendido
    + PSH: Encendido
    + RST: Apagado
    + SYN: Apagado
    + FIN: Apagado
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 60:9C:9F:1F:99:80
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 6
· Longitud de paquete IP (hlen): 20
· Análisis de TCP:
  ~ Puerto de Origen: 42947
  ~ Puerto de Destino: 47873
  ~ Número de secuencia: 2441841548
  ~ Número de ack: 573051476
  ~ Longitud: P
  ~ Banderas:
    + CWR: Apagado
    + ECE: Apagado
    + URG: Apagado
    + ACK: Encendido
    + PSH: Encendido
    + RST: Apagado
    + SYN: Apagado
    + FIN: Apagado
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 60:9C:9F:1F:99:80
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 6
· Longitud de paquete IP (hlen): 20
· Análisis de TCP:
  ~ Puerto de Origen: 42691
  ~ Puerto de Destino: 47873
  ~ Número de secuencia: 3351305865
  ~ Número de ack: 3512369687
  ~ Longitud: P
  ~ Banderas:
    + CWR: Encendido
    + ECE: Apagado
    + URG: Apagado
    + ACK: Apagado
    + PSH: Encendido
    + RST: Apagado
    + SYN: Apagado
    + FIN: Apagado
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 60:9C:9F:1F:99:80
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 6
· Longitud de paquete IP (hlen): 20
· Análisis de TCP:
  ~ Puerto de Origen: 42947
  ~ Puerto de Destino: 47873
  ~ Número de secuencia: 2844494732
  ~ Número de ack: 573051476
  ~ Longitud: P
  ~ Banderas:
    + CWR: Encendido
    + ECE: Apagado
    + URG: Apagado
    + ACK: Apagado
    + PSH: Encendido
    + RST: Apagado
    + SYN: Apagado
    + FIN: Apagado
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 60:9C:9F:1F:99:80
· MAC Destino: D4:61:9D:2D:E1:58
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 6
· Longitud de paquete IP (hlen): 20
· Análisis de TCP:
  ~ Puerto de Origen: 47873
  ~ Puerto de Destino: 42691
  ~ Número de secuencia: 3512369687
  ~ Número de ack: 3351305865
  ~ Longitud: P
  ~ Banderas:
    + CWR: Encendido
    + ECE: Apagado
    + URG: Apagado
    + ACK: Apagado
    + PSH: Encendido
    + RST: Apagado
    + SYN: Apagado
    + FIN: Apagado
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 60:9C:9F:1F:99:80
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 6
· Longitud de paquete IP (hlen): 20
· Análisis de TCP:
  ~ Puerto de Origen: 42691
  ~ Puerto de Destino: 47873
  ~ Número de secuencia: 3351305865
  ~ Número de ack: 3529146903
  ~ Longitud: P
  ~ Banderas:
    + CWR: Encendido
    + ECE: Apagado
    + URG: Apagado
    + ACK: Apagado
    + PSH: Encendido
    + RST: Apagado
    + SYN: Apagado
    + FIN: Apagado
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 60:9C:9F:1F:99:80
· MAC Destino: D4:61:9D:2D:E1:58
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 6
· Longitud de paquete IP (hlen): 20
· Análisis de TCP:
  ~ Puerto de Origen: 47873
  ~ Puerto de Destino: 42947
  ~ Número de secuencia: 573051476
  ~ Número de ack: 2844494732
  ~ Longitud: P
  ~ Banderas:
    + CWR: Encendido
    + ECE: Apagado
    + URG: Apagado
    + ACK: Apagado
    + PSH: Encendido
    + RST: Apagado
    + SYN: Apagado
    + FIN: Apagado
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 60:9C:9F:1F:99:80
· MAC Destino: D4:61:9D:2D:E1:58
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 6
· Longitud de paquete IP (hlen): 20
· Análisis de TCP:
  ~ Puerto de Origen: 47873
  ~ Puerto de Destino: 42947
  ~ Número de secuencia: 589828692
  ~ Número de ack: 2861271948
  ~ Longitud: P
  ~ Banderas:
    + CWR: Apagado
    + ECE: Apagado
    + URG: Apagado
    + ACK: Apagado
    + PSH: Encendido
    + RST: Apagado
    + SYN: Apagado
    + FIN: Apagado
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 60:9C:9F:1F:99:80
· MAC Destino: D4:61:9D:2D:E1:58
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 6
· Longitud de paquete IP (hlen): 20
· Análisis de TCP:
  ~ Puerto de Origen: 47873
  ~ Puerto de Destino: 42691
  ~ Número de secuencia: 3529146903
  ~ Número de ack: 3368083081
  ~ Longitud: P
  ~ Banderas:
    + CWR: Apagado
    + ECE: Apagado
    + URG: Apagado
    + ACK: Apagado
    + PSH: Encendido
    + RST: Apagado
    + SYN: Apagado
    + FIN: Apagado
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D4:61:9D:2D:E1:58
· MAC Destino: 60:9C:9F:1F:99:80
· Ether Type: 2048
· El paquete es IP.
· Protocolo: 6
· Longitud de paquete IP (hlen): 20
· Análisis de TCP:
  ~ Puerto de Origen: 42947
  ~ Puerto de Destino: 47873
  ~ Número de secuencia: 2844494732
  ~ Número de ack: 589828692
  ~ Longitud: P
  ~ Banderas:
    + CWR: Encendido
    + ECE: Apagado
    + URG: Apagado
    + ACK: Apagado
    + PSH: Encendido
    + RST: Apagado
    + SYN: Apagado
    + FIN: Apagado
-------  Fin de Análisis  --------
Fin de programa
 - Humberto Alcocer, 2019
ESCOM. Redes de Computadoras. Práctica 14
```

## Posibles Mejoras

Podríamos almacenar todos los paquetes TCP para realizar un análisis del comportamiento de la red y poder detectar congestionamientos en el funcionamiento de la red.

## Conclusiones

TCP es uno de los protocolos más antiguos y usados de Internet. Gracias a él existe Internet como lo conocemos hoy en día, aplicaciones de correo, mensajería instantánea, transmisión de archivos y muchísimas otras aplicaciones están basadas en TCP. Al realizar esta práctica analizamos TCP con lo que podemos visualizar el comportamiento del tráfico dentro de nuestro propio equipo.

## Fuentes

- Material visto en clase.

[rfc-793-link]: https://tools.ietf.org/html/rfc793
