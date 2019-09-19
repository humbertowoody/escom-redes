# Práctica 4-1

|            Título |           Protocolo ARP           |
| ----------------: | :-------------------------------: |
|            Nombre | Humberto Alejandro Ortega Alcocer |
| Número de Control |            2016630495             |
|             Fecha |            17/09/2019             |

## Introducción

El protocolo ARP proporciona la funcionalidad de poder solicitar la _traducción_, por decirlo de una manera, de direcciones físicas (hardware) a direcciones lógicas (software), siendo estas direcciones MAC e IP respectivamente. El objetivo de la presente práctica, es realizar un programa que:

- [x] Capture paquetes ARP
- [x] Muestre sus datos
- [x] Realice un análisis de sus distintos campos

## Desarrollo

Para comenzar con el desarrollo del programa, realizaremos la programación de las distintas operaciones de configuración para la captura, siendo estas:

1. Mostrar una lista con todas las tarjetas de red disponibles.
2. Leer la opción de tarjeta de red a usar que seleccione el usuario.
3. Preguntar al usuario por el número de paquetes a capturar (sean o no ARP).
4. Inicializar la tarjeta en _modo promiscuo_, con una longitud máxima de paquete de _65535_ y con un timeout de _10000ms_, eliminando un poco de configuración por parte del usuario.

Posteriormente, se realizará el análisis de cada paquete de **ARP**, para esto, usaremos el siguiente formato:

![Encabezado de ARP][arp-header-gif]

Con el cual, nuestro programa mostrará información referente a los campos:

- Tipo de Hardware
- Tipo de Protocolo
- Longitud de dirección de hardware
- Longitud de dirección de protocolo
- Operación
- Dirección de hardware (MAC) de origen
- Dirección IP de origen
- Dirección IP de destino
- Dirección de hardware (MAC) de destino

En el desarrollo del programa, usé C++ como lenguaje principal, con patrones de C en manejo de estructuras y algunos _castings_ hechos para interpretar los datos crudos.

> En caso de contar con Visual Studio Code, se podrá compilar con la configuración prestablecida para MacOS y Linux usando el atajo de teclado: `Ctrl + B` (`⌘ + B` en MacOS). Esto generará un binario `arp.out` el cual puede ser ejecutado directamente.

## Prueba

El código de esta práctica se encuentra dentro de la carpeta proporcionada con este material. La salida de una correcta ejecución se muestra a continuación:

```txt
Práctica 4.1
Analizador de ARP
Seleccione una interfaz de red de la siguiente lista:
1) en0
2) p2p0
3) awdl0
4) bridge0
5) utun0
6) en1
7) lo0
8) gif0
9) stf0
10) XHC20
Ingresa el número de la interfaz de red (1-10): 1
¿Cuántos paquetes deseas capturar? (1-100): 10
Iniciando captura...
Leyendo 10 desde en0

------- Paquete Capturado --------
· MAC Origen: 68:07:15:24:2D:18
· MAC Destino: FF:FF:FF:FF:FF:FF
- El paquete NO es de tipo ARP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 74:40:BB:B8:D0:FB
· MAC Destino: FF:FF:FF:FF:FF:FF
- El paquete NO es de tipo ARP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 0C:B3:19:53:7A:41
· MAC Destino: FF:FF:FF:FF:FF:FF
- El paquete es de tipo ARP.
  - Tipo Hardware: (1) Ethernet
  - Tipo Proto: 2048
  - Longitud de Hardware:
  - Longitud de Protocolo:
  - Operación ARP: (1) Solicitud ARP  (No ARP Gratuito)
  - MAC origen (ARP): 0C:B3:19:53:7A:41
  - IP origen: 10.100.68.118
  - MAC destino (ARP): 00:00:00:00:00:00
  - IP destino: 10.100.95.254
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 50:68:0A:54:2C:50
· MAC Destino: FF:FF:FF:FF:FF:FF
- El paquete es de tipo ARP.
  - Tipo Hardware: (1) Ethernet
  - Tipo Proto: 2048
  - Longitud de Hardware:
  - Longitud de Protocolo:
  - Operación ARP: (1) Solicitud ARP  (No ARP Gratuito)
  - MAC origen (ARP): 50:68:0A:54:2C:50
  - IP origen: 10.100.68.83
  - MAC destino (ARP): 00:00:00:00:00:00
  - IP destino: 10.100.95.254
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 74:40:BB:B8:D0:FB
· MAC Destino: FF:FF:FF:FF:FF:FF
- El paquete NO es de tipo ARP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 74:40:BB:B8:D0:FB
· MAC Destino: FF:FF:FF:FF:FF:FF
- El paquete NO es de tipo ARP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 74:E5:43:66:FC:C1
· MAC Destino: FF:FF:FF:FF:FF:FF
- El paquete es de tipo ARP.
  - Tipo Hardware: (1) Ethernet
  - Tipo Proto: 2048
  - Longitud de Hardware:
  - Longitud de Protocolo:
  - Operación ARP: (1) Solicitud ARP  (ARP Gratuito)
  - MAC origen (ARP): 74:E5:43:66:FC:C1
  - IP origen: 10.100.70.243
  - MAC destino (ARP): 00:00:00:00:00:00
  - IP destino: 10.100.70.243
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 20:68:9D:EB:BC:FC
· MAC Destino: FF:FF:FF:FF:FF:FF
- El paquete NO es de tipo ARP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: D0:65:CA:24:D8:72
· MAC Destino: FF:FF:FF:FF:FF:FF
- El paquete NO es de tipo ARP.
-------  Fin de Análisis  --------
------- Paquete Capturado --------
· MAC Origen: 4C:32:75:97:E7:E7
· MAC Destino: FF:FF:FF:FF:FF:FF
- El paquete NO es de tipo ARP.
-------  Fin de Análisis  --------
Fin de programa
 - Humberto Alcocer, 2019
ESCOM. Redes de Computadoras. Práctica 4
```

## Posibles Mejoras

Podría mejorar el análisis de ARP realizando un seguimiento de todas las _solicitudes ARP_ así como las _respuestas_ de la red. De esta forma, podríamos comenzar a _"mapear"_ la topología de la red y, finalmente, obtener más información acerca de la configuración actual de la misma, así como datos y estadísticas interesantes como, pero no limitadas a:

- Número de equipos conectados.
- Direcciones asignadas.
- _Status_ de vida de equipos previamente detectados.

## Conclusiones

El protocolo **ARP** cumple una de las funciones más importantes en las redes de computadoras, su correcto funcionamiento es fundamental para que se pueda tener un correcto flujo de configuración de los equipos.

Es fácil subestimar la cantidad de paquetes ARP que se utilizan en todo momento dentro de una red, es por eso que esta práctica me ha parecido, sobre todo, interesante referente a lo mucho que se emplea dicho protocolo. Ataques de tipo "ARP Poisoning" se basan en una explotación simple del diseño de ARP, y verlo funcionar directamente gracias a un _sniffer_, como este, nos permite visualizar comportamientos interesantes dentro de una red de computadoras.

## Fuentes

- Material visto en clase.

[arp-header-gif]: https://www.ipv6.com/wp-content/uploads/2017/06/arp1.gif
