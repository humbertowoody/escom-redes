# Proyecto Final

> "There was a time when people felt the internet was another world, but now people realize it's a tool we use in this world".
> - Tim Berners Lee.

Como proyecto final decidí realizar la implementación de un *sniffer* de paquetes en red que permita capturar, analizar y exportar datos de forma rápida y sencilla. El programa está realizado en C/C++ usando la librería [libpcap][libpcap-lib] para las funcionalidades de análisis y exportación de los datos.

## Tabla de Contenidos
- [Proyecto Final](#proyecto-final)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Objetivos](#objetivos)
  - [Implementación](#implementaci%C3%B3n)
  - [Prueba](#prueba)
    - [Paquetes *al vuelo*](#paquetes-al-vuelo)
    - [Paquetes desde un archivo](#paquetes-desde-un-archivo)
    - [Establecer filtros de captura.](#establecer-filtros-de-captura)
    - [Exportar captura a un archivo `.pcap`](#exportar-captura-a-un-archivo-pcap)
  - [Conclusión](#conclusi%C3%B3n)

## Objetivos

Dentro del universo de softwares capturadores (e intérpretes) de paquetes de red, existen múltiples funciones a nuestra disposición, definir las más útiles siempre dependerá del caso de uso que consideremos darle a dicho análisis. Aún así, se cuenta con un cierto nivel de aceptación ante los diferentes _Sniffers_ disponibles para que se cuente con algunas funciones elementales.

El presente proyecto, únicamente busca cubrir esas funcionalidades simples de forma directa y con el afán de proporcionar una especie de guía para desarrollar programas más complejos que requieran de las mismas. Las funcionalidades contempladas son:

- Exhibir las interfaces de captura disponibles.
- Permite elegir y configurar los parámetros de la interfaz de captura.
- Permite especificar filtros de captura.
- Permite elegir el número de paquetes a ser capturados.
- Permite analizar paquetes *al vuelo*, o desde un archivo.
- Muestra información de **cada protocolo de cada paquete capturado**.
- Muestra estadísticas de los paquetes capturados.
- Permite exportar la tasa de captura a un formato estándar de los programas de captura (`.pcap`).

## Implementación

Para desarrollar la implementación del actual programa, comenzamos con el análisis del flujo que tendrá el usuario al interactuar con el mismo; algo simple pero que permita configurar los parámetros de forma rápida y eficiente.

Primeramente, el programa imprime un encabezado de bienvenida y posteriormente sigue el siguiente flujo:

1. Preguntar al usuario si desea capturar los paquetes *al vuelo* o desde un archivo.
2. **Al Vuelo**
   1. Mostrar una lista de las tarjetas de red disponibles.
   2. El usuario selecciona una tarjeta.
   3. Preguntar al usuario por el **tamaño máximo de paquete**, lo recomendado es 65536.
   4. Preguntar al usuario si la interfaz deberá operar en **modo promiscuo**.
   5. Preguntar al usuario por el **tiempo de timeout** para la captura de paquetes, lo recomendado es de 1000 (en ms).
   6. Preguntar al usuario si desea guardar en un archivo los paquetes capturados.
   7. **Si Guardar**
      1. Preguntar por el nombre del archivo.
      2. Abrir el archivo.
3. **Desde un Archivo**
   1. Preguntar al usuario por el nombre del archivo para leer los paquetes.
4. Preguntar al usuario el **número de paquetes** a capturar.
5. Preguntar al usuario si desea emplear un filtro de captura.
6. **Con Filtro**
   1. Preguntar al usuario por el filtro
   2. Compilar el filtro
   3. Aplicar el filtro
7. Análizar los paquetes
   1. Recibir el paquete
   2. Imprimir fecha de captura
   3. Análisis de Ethernet/802.3
   4. Análisis de IP
   5. Análisis de ICMP, TCP o UDP.

El código fuente, refleja fuertemente este flujo y es así como el programa ya compilado opera.

## Prueba

Para realizar la prueba correcta del programa, tendremos que considerar todos los casos de uso válidos para el mismo, para no colocar sientos de pruebas aquí, nos enfocaremos en los casos de uso cruciales para nuestro *Sniffer*:

- Leer paquetes *al vuelo*.
- Leer paquetes desde un archivo.
- Establecer filtros de captura.
- Exportar captura a un archivo `.pcap`.

### Paquetes *al vuelo*

Para realizar la cpatura de paquetes al vuelo, seleccionamos la **primer opción** en el primer menú. Posteriormente llenaremos nuestra configuración y finalmente el programa nos entregará una salida parecida a:

```txt
Sniffer de Paquetes

Selecciona el tipo de captura:

  1) Captura de paquetes 'al vuelo'.
  2) Usar un archivo.

Tu opción: 1
Selecciona una interfaz de red:

1) en0 (Sin descripción)
2) p2p0 (Sin descripción)
3) awdl0 (Sin descripción)
4) bridge0 (Sin descripción)
5) utun0 (Sin descripción)
6) en1 (Sin descripción)
7) lo0 (Sin descripción)
8) gif0 (Sin descripción)
9) stf0 (Sin descripción)
10) XHC20 (Sin descripción)

Ingresa el número de la interfaz (1-10): 1
¿Cuál es el tamaño de paquete a usar?
(100 - 65536): 65536
¿Desea abrir la interfaz en modo promiscuo? S/N: S
¿Cuál es el tiempo de timeout que deseas usar (en ms)?
El valor recomendado es de 1000.
(10 - 10000): 1000
¿Deses guardar los paquetes capturados? S/N: N
¿Cuántos paquetes deseas capturar? (1-1000): 10
¿Desea usar un filtro de captura? S/N: N
Escuchando en: en0
***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:13:59
Número de Paquete: 0
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 94:FE:9D:62:3B:00
· MAC Origen: D4:61:9D:2D:E1:58
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 972
· Tamaño de Datos: 952 bytes
· Tiempo de Vida (TTL): 64
· Protocolo: 06 (TCP)
· Checksum: E20D
· ¿Checksum Correcto? Sí.
· IP Origen: 192.168.1.65
· IP Destino: 104.244.42.65
--- Fin de Paquete IP ---
---Análisis TCP ---
· Puerto Origen: 56073
· Puerto Destino: 443
· Longitud de Encabezado: 128 bits = 16 bytes.
· Banderas TCP:
  ¬ NS: Activa.
  ¬ CWR: Inactiva.
  ¬ ECE: Inactiva.
  ¬ URG: Inactiva.
  ¬ ACK: Activa.
  ¬ PSH: Activa.
  ¬ RST: Inactiva.
  ¬ SYN: Inactiva.
  ¬ FIN: Inactiva.
· Checksum de TCP: F6B2
· Pseudo Encabezado TCP:
  ~ IP Origen: 192.168.1.65
  ~ IP Destino: 104.244.42.65
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 6
  ~ Longitud de PDU: 952
· ¿Checksum TCP correcto? Sí.
· Valor Checksum: 0
--- Fin de Análisis TCP ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:13:59
Número de Paquete: 1
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 280
· Tamaño de Datos: 260 bytes
· Tiempo de Vida (TTL): 51
· Protocolo: 06 (TCP)
· Checksum: 629A
· ¿Checksum Correcto? Sí.
· IP Origen: 104.244.42.65
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis TCP ---
· Puerto Origen: 443
· Puerto Destino: 56073
· Longitud de Encabezado: 128 bits = 16 bytes.
· Banderas TCP:
  ¬ NS: Activa.
  ¬ CWR: Inactiva.
  ¬ ECE: Inactiva.
  ¬ URG: Inactiva.
  ¬ ACK: Activa.
  ¬ PSH: Activa.
  ¬ RST: Inactiva.
  ¬ SYN: Inactiva.
  ¬ FIN: Inactiva.
· Checksum de TCP: E620
· Pseudo Encabezado TCP:
  ~ IP Origen: 104.244.42.65
  ~ IP Destino: 192.168.1.65
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 6
  ~ Longitud de PDU: 260
· ¿Checksum TCP correcto? Sí.
· Valor Checksum: 0
--- Fin de Análisis TCP ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:13:59
Número de Paquete: 2
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 94:FE:9D:62:3B:00
· MAC Origen: D4:61:9D:2D:E1:58
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 52
· Tamaño de Datos: 32 bytes
· Tiempo de Vida (TTL): 64
· Protocolo: 06 (TCP)
· Checksum: E5A5
· ¿Checksum Correcto? Sí.
· IP Origen: 192.168.1.65
· IP Destino: 104.244.42.65
--- Fin de Paquete IP ---
---Análisis TCP ---
· Puerto Origen: 56073
· Puerto Destino: 443
· Longitud de Encabezado: 128 bits = 16 bytes.
· Banderas TCP:
  ¬ NS: Activa.
  ¬ CWR: Inactiva.
  ¬ ECE: Inactiva.
  ¬ URG: Inactiva.
  ¬ ACK: Inactiva.
  ¬ PSH: Activa.
  ¬ RST: Inactiva.
  ¬ SYN: Inactiva.
  ¬ FIN: Inactiva.
· Checksum de TCP: EAEA
· Pseudo Encabezado TCP:
  ~ IP Origen: 192.168.1.65
  ~ IP Destino: 104.244.42.65
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 6
  ~ Longitud de PDU: 32
· ¿Checksum TCP correcto? Sí.
· Valor Checksum: 0
--- Fin de Análisis TCP ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:13:59
Número de Paquete: 3
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 86DD
· Tipo de Paquete: 34525
· El paquete es Ethernet.
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:13:59
Número de Paquete: 4
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 94:FE:9D:62:3B:00
· MAC Origen: D4:61:9D:2D:E1:58
· Ether Type: 86DD
· Tipo de Paquete: 34525
· El paquete es Ethernet.
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:13:59
Número de Paquete: 5
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 86DD
· Tipo de Paquete: 34525
· El paquete es Ethernet.
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:13:59
Número de Paquete: 6
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 94:FE:9D:62:3B:00
· MAC Origen: D4:61:9D:2D:E1:58
· Ether Type: 86DD
· Tipo de Paquete: 34525
· El paquete es Ethernet.
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:14:00
Número de Paquete: 7
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 70
· Tamaño Total: 320
· Tamaño de Datos: 300 bytes
· Tiempo de Vida (TTL): 42
· Protocolo: 06 (TCP)
· Checksum: 459F
· ¿Checksum Correcto? Sí.
· IP Origen: 104.40.147.142
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis TCP ---
· Puerto Origen: 443
· Puerto Destino: 56102
· Longitud de Encabezado: 128 bits = 16 bytes.
· Banderas TCP:
  ¬ NS: Activa.
  ¬ CWR: Inactiva.
  ¬ ECE: Inactiva.
  ¬ URG: Inactiva.
  ¬ ACK: Activa.
  ¬ PSH: Activa.
  ¬ RST: Inactiva.
  ¬ SYN: Inactiva.
  ¬ FIN: Inactiva.
· Checksum de TCP: 5019
· Pseudo Encabezado TCP:
  ~ IP Origen: 104.40.147.142
  ~ IP Destino: 192.168.1.65
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 6
  ~ Longitud de PDU: 300
· ¿Checksum TCP correcto? Sí.
· Valor Checksum: 0
--- Fin de Análisis TCP ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:14:00
Número de Paquete: 8
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 94:FE:9D:62:3B:00
· MAC Origen: D4:61:9D:2D:E1:58
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 52
· Tamaño de Datos: 32 bytes
· Tiempo de Vida (TTL): 64
· Protocolo: 06 (TCP)
· Checksum: 7D24
· ¿Checksum Correcto? Sí.
· IP Origen: 192.168.1.65
· IP Destino: 104.40.147.142
--- Fin de Paquete IP ---
---Análisis TCP ---
· Puerto Origen: 56102
· Puerto Destino: 443
· Longitud de Encabezado: 128 bits = 16 bytes.
· Banderas TCP:
  ¬ NS: Activa.
  ¬ CWR: Inactiva.
  ¬ ECE: Inactiva.
  ¬ URG: Inactiva.
  ¬ ACK: Inactiva.
  ¬ PSH: Activa.
  ¬ RST: Inactiva.
  ¬ SYN: Inactiva.
  ¬ FIN: Inactiva.
· Checksum de TCP: 2201
· Pseudo Encabezado TCP:
  ~ IP Origen: 192.168.1.65
  ~ IP Destino: 104.40.147.142
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 6
  ~ Longitud de PDU: 32
· ¿Checksum TCP correcto? Sí.
· Valor Checksum: 0
--- Fin de Análisis TCP ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:14:00
Número de Paquete: 9
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 70
· Tamaño Total: 309
· Tamaño de Datos: 289 bytes
· Tiempo de Vida (TTL): 42
· Protocolo: 06 (TCP)
· Checksum: 45A9
· ¿Checksum Correcto? Sí.
· IP Origen: 104.40.147.142
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis TCP ---
· Puerto Origen: 443
· Puerto Destino: 56102
· Longitud de Encabezado: 128 bits = 16 bytes.
· Banderas TCP:
  ¬ NS: Activa.
  ¬ CWR: Inactiva.
  ¬ ECE: Inactiva.
  ¬ URG: Inactiva.
  ¬ ACK: Activa.
  ¬ PSH: Activa.
  ¬ RST: Inactiva.
  ¬ SYN: Inactiva.
  ¬ FIN: Inactiva.
· Checksum de TCP: 588B
· Pseudo Encabezado TCP:
  ~ IP Origen: 104.40.147.142
  ~ IP Destino: 192.168.1.65
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 6
  ~ Longitud de PDU: 289
· ¿Checksum TCP correcto? Sí.
· Valor Checksum: 0
--- Fin de Análisis TCP ---
****************** FIN DE PAQUETE *******************


Estadísticas de Captura:

- Paquetes Ethernet:                10
- Paquetes IEEE 802.3:              0
  · Paquetes IP:                    6
  · Paquetes no IP:                 4
    ~ Paquetes ICMP:                0
    ~ Paquetes TCP:                 6
    ~ Paquetes UDP:                 0
    ~ Paquetes desconocidos:        0
-----------------------------------------
- Total de Paquetes:                10
- Duración de la sesión de captura: 1006ms

La captura ha terminado.

ESCOM. Redes de Computadoras - 2019
```

Con lo cual podemos corroborar que la captura se realizó de forma adecuada usando nuestra tarjeta de red especificada.

### Paquetes desde un archivo

Para realizar la prueba de ejecución del programa leyendo los paquetes directamente de un archivo, seleccionaremos la **segunda opción** en el menú principal de la aplicación. Llenaremos el nombre del archivo, nos preguntará por el número de paquetes y si quisiéramos específicar un filtro de captura y posteriormente nos otorgará una salida parecida a:

```txt
Sniffer de Paquetes

Selecciona el tipo de captura:

  1) Captura de paquetes 'al vuelo'.
  2) Usar un archivo.

Tu opción: 2
Nombre del archivo: paquetes.pcap
Se realizará la lectura desde: paquetes.pcap
¿Cuántos paquetes deseas capturar? (1-1000): 33
¿Desea usar un filtro de captura? S/N: N
Leyendo paquetes desde paquetes.pcap
***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 0
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 0003
· Tipo de Paquete: 3
· El paquete es 802.3 + LLC.
·Longitud: 0003 (3).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Normal.
·Campo de Control: 7F
  ~ Binario: 01111111
·Análisis de tipo de trama:
  ~ Trama tipo: I
  ~ N(S) = 111
  ~ Bit P/F: 1
  ~ N(R) = 111
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 1
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:DF:1B
· MAC Origen: 00:02:B3:9C:AE:BA
· Ether Type: 0003
· Tipo de Paquete: 3
· El paquete es 802.3 + LLC.
·Longitud: 0003 (3).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Normal.
·Campo de Control: 73
  ~ Binario: 01110011
·Análisis de tipo de trama:
  ~ Trama tipo: I
  ~ N(S) = 111
  ~ Bit P/F: 0
  ~ N(R) = 011
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 2
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 0004
· Tipo de Paquete: 4
· El paquete es 802.3 + LLC.
·Longitud: 0004 (4).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Extendido.
·Campo de Control: 0101
  ~ Binario: 0000000100000001
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000001
  ~ Bit P/F: 0
  ~ N(R) = 0000001
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 3
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:DF:1B
· MAC Origen: 00:02:B3:9C:AE:BA
· Ether Type: 0004
· Tipo de Paquete: 4
· El paquete es 802.3 + LLC.
·Longitud: 0004 (4).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Extendido.
·Campo de Control: 0101
  ~ Binario: 0000000100000001
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000001
  ~ Bit P/F: 0
  ~ N(R) = 0000001
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 4
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 0012
· Tipo de Paquete: 18
· El paquete es 802.3 + LLC.
·Longitud: 0012 (18).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Extendido.
·Campo de Control: 0001
  ~ Binario: 0000000000000001
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000000
  ~ Bit P/F: 0
  ~ N(R) = 0000001
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 5
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:DF:1B
· MAC Origen: 00:02:B3:9C:AE:BA
· Ether Type: 0012
· Tipo de Paquete: 18
· El paquete es 802.3 + LLC.
·Longitud: 0012 (18).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Extendido.
·Campo de Control: 0003
  ~ Binario: 0000000000000011
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000000
  ~ Bit P/F: 0
  ~ N(R) = 0000011
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 6
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:DF:1B
· MAC Origen: 00:02:B3:9C:AE:BA
· Ether Type: 0004
· Tipo de Paquete: 4
· El paquete es 802.3 + LLC.
·Longitud: 0004 (4).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Extendido.
·Campo de Control: 0103
  ~ Binario: 0000000100000011
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000001
  ~ Bit P/F: 0
  ~ N(R) = 0000011
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 7
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 0004
· Tipo de Paquete: 4
· El paquete es 802.3 + LLC.
·Longitud: 0004 (4).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Extendido.
·Campo de Control: 0103
  ~ Binario: 0000000100000011
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000001
  ~ Bit P/F: 0
  ~ N(R) = 0000011
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 8
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 00AC
· Tipo de Paquete: 172
· El paquete es 802.3 + LLC.
·Longitud: 00AC (172).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Extendido.
·Campo de Control: 0202
  ~ Binario: 0000001000000010
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000010
  ~ Bit P/F: 0
  ~ N(R) = 0000010
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 9
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:DF:1B
· MAC Origen: 00:02:B3:9C:AE:BA
· Ether Type: 0004
· Tipo de Paquete: 4
· El paquete es 802.3 + LLC.
·Longitud: 0004 (4).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Extendido.
·Campo de Control: 0104
  ~ Binario: 0000000100000100
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000001
  ~ Bit P/F: 0
  ~ N(R) = 0000100
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 10
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:DF:1B
· MAC Origen: 00:02:B3:9C:AE:BA
· Ether Type: 005F
· Tipo de Paquete: 95
· El paquete es 802.3 + LLC.
·Longitud: 005F (95).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Extendido.
·Campo de Control: 0204
  ~ Binario: 0000001000000100
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000010
  ~ Bit P/F: 0
  ~ N(R) = 0000100
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 11
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 0004
· Tipo de Paquete: 4
· El paquete es 802.3 + LLC.
·Longitud: 0004 (4).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Extendido.
·Campo de Control: 0104
  ~ Binario: 0000000100000100
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000001
  ~ Bit P/F: 0
  ~ N(R) = 0000100
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 12
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 0091
· Tipo de Paquete: 145
· El paquete es 802.3 + LLC.
·Longitud: 0091 (145).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Extendido.
·Campo de Control: 0404
  ~ Binario: 0000010000000100
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000100
  ~ Bit P/F: 0
  ~ N(R) = 0000100
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 13
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:DF:1B
· MAC Origen: 00:02:B3:9C:AE:BA
· Ether Type: 0004
· Tipo de Paquete: 4
· El paquete es 802.3 + LLC.
·Longitud: 0004 (4).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Extendido.
·Campo de Control: 0106
  ~ Binario: 0000000100000110
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000001
  ~ Bit P/F: 0
  ~ N(R) = 0000110
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 14
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:DF:1B
· MAC Origen: 00:02:B3:9C:AE:BA
· Ether Type: 0046
· Tipo de Paquete: 70
· El paquete es 802.3 + LLC.
·Longitud: 0046 (70).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Extendido.
·Campo de Control: 0406
  ~ Binario: 0000010000000110
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000100
  ~ Bit P/F: 0
  ~ N(R) = 0000110
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 15
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 0004
· Tipo de Paquete: 4
· El paquete es 802.3 + LLC.
·Longitud: 0004 (4).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Extendido.
·Campo de Control: 0106
  ~ Binario: 0000000100000110
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000001
  ~ Bit P/F: 0
  ~ N(R) = 0000110
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 16
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 007E
· Tipo de Paquete: 126
· El paquete es 802.3 + LLC.
·Longitud: 007E (126).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Extendido.
·Campo de Control: 0606
  ~ Binario: 0000011000000110
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000110
  ~ Bit P/F: 0
  ~ N(R) = 0000110
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 17
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:DF:1B
· MAC Origen: 00:02:B3:9C:AE:BA
· Ether Type: 0004
· Tipo de Paquete: 4
· El paquete es 802.3 + LLC.
·Longitud: 0004 (4).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Extendido.
·Campo de Control: 0108
  ~ Binario: 0000000100001000
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000001
  ~ Bit P/F: 0
  ~ N(R) = 0001000
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 18
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 0004
· Tipo de Paquete: 4
· El paquete es 802.3 + LLC.
·Longitud: 0004 (4).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Extendido.
·Campo de Control: 0108
  ~ Binario: 0000000100001000
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000001
  ~ Bit P/F: 0
  ~ N(R) = 0001000
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 19
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 007E
· Tipo de Paquete: 126
· El paquete es 802.3 + LLC.
·Longitud: 007E (126).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Extendido.
·Campo de Control: 0808
  ~ Binario: 0000100000001000
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0001000
  ~ Bit P/F: 0
  ~ N(R) = 0001000
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 20
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:DF:1B
· MAC Origen: 00:02:B3:9C:AE:BA
· Ether Type: 0004
· Tipo de Paquete: 4
· El paquete es 802.3 + LLC.
·Longitud: 0004 (4).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Extendido.
·Campo de Control: 010A
  ~ Binario: 0000000100001010
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000001
  ~ Bit P/F: 0
  ~ N(R) = 0001010
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 21
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 0004
· Tipo de Paquete: 4
· El paquete es 802.3 + LLC.
·Longitud: 0004 (4).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Extendido.
·Campo de Control: 010A
  ~ Binario: 0000000100001010
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000001
  ~ Bit P/F: 0
  ~ N(R) = 0001010
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 22
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 0012
· Tipo de Paquete: 18
· El paquete es 802.3 + LLC.
·Longitud: 0012 (18).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Extendido.
·Campo de Control: 0A0B
  ~ Binario: 0000101000001011
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0001010
  ~ Bit P/F: 0
  ~ N(R) = 0001011
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 23
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:DF:1B
· MAC Origen: 00:02:B3:9C:AE:BA
· Ether Type: 0004
· Tipo de Paquete: 4
· El paquete es 802.3 + LLC.
·Longitud: 0004 (4).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Extendido.
·Campo de Control: 010D
  ~ Binario: 0000000100001101
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000001
  ~ Bit P/F: 0
  ~ N(R) = 0001101
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 24
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 03:00:00:00:00:01
· MAC Origen: 00:04:AC:44:4D:02
· Ether Type: 008B
· Tipo de Paquete: 139
· El paquete es 802.3 + LLC.
·Longitud: 008B (139).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Extendido.
·Campo de Control: 032C
  ~ Binario: 0000001100101100
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000011
  ~ Bit P/F: 0
  ~ N(R) = 0101100
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 25
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 0035
· Tipo de Paquete: 53
· El paquete es 802.3 + LLC.
·Longitud: 0035 (53).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Extendido.
·Campo de Control: 0C0A
  ~ Binario: 0000110000001010
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0001100
  ~ Bit P/F: 0
  ~ N(R) = 0001010
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 26
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:DF:1B
· MAC Origen: 00:02:B3:9C:AE:BA
· Ether Type: 0035
· Tipo de Paquete: 53
· El paquete es 802.3 + LLC.
·Longitud: 0035 (53).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Extendido.
·Campo de Control: 0A0E
  ~ Binario: 0000101000001110
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0001010
  ~ Bit P/F: 0
  ~ N(R) = 0001110
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 27
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 0012
· Tipo de Paquete: 18
· El paquete es 802.3 + LLC.
·Longitud: 0012 (18).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Extendido.
·Campo de Control: 0E0D
  ~ Binario: 0000111000001101
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0001110
  ~ Bit P/F: 0
  ~ N(R) = 0001101
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 28
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:DF:1B
· MAC Origen: 00:02:B3:9C:AE:BA
· Ether Type: 0004
· Tipo de Paquete: 4
· El paquete es 802.3 + LLC.
·Longitud: 0004 (4).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Extendido.
·Campo de Control: 0111
  ~ Binario: 0000000100010001
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000001
  ~ Bit P/F: 0
  ~ N(R) = 0010001
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 29
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 0012
· Tipo de Paquete: 18
· El paquete es 802.3 + LLC.
·Longitud: 0012 (18).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Extendido.
·Campo de Control: 100D
  ~ Binario: 0001000000001101
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0010000
  ~ Bit P/F: 0
  ~ N(R) = 0001101
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 30
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:DF:1B
· MAC Origen: 00:02:B3:9C:AE:BA
· Ether Type: 0004
· Tipo de Paquete: 4
· El paquete es 802.3 + LLC.
·Longitud: 0004 (4).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Extendido.
·Campo de Control: 0113
  ~ Binario: 0000000100010011
·Análisis de trama:
  ~ Trama tipo: I
  ~ N(S) = 0000001
  ~ Bit P/F: 0
  ~ N(R) = 0010011
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 31
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:AE:BA
· MAC Origen: 00:02:B3:9C:DF:1B
· Ether Type: 0003
· Tipo de Paquete: 3
· El paquete es 802.3 + LLC.
·Longitud: 0003 (3).
·DSAP: F0
·SSAP: F0
·Tipo de Modo: Normal.
·Campo de Control: 53
  ~ Binario: 01010011
·Análisis de tipo de trama:
  ~ Trama tipo: I
  ~ N(S) = 101
  ~ Bit P/F: 0
  ~ N(R) = 011
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 12:24:33
Número de Paquete: 32
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 00:02:B3:9C:DF:1B
· MAC Origen: 00:02:B3:9C:AE:BA
· Ether Type: 0003
· Tipo de Paquete: 3
· El paquete es 802.3 + LLC.
·Longitud: 0003 (3).
·DSAP: F0
·SSAP: F1
·Tipo de Modo: Normal.
·Campo de Control: 73
  ~ Binario: 01110011
·Análisis de tipo de trama:
  ~ Trama tipo: I
  ~ N(S) = 111
  ~ Bit P/F: 0
  ~ N(R) = 011
· ¿Es un paquete IP? No.
--- Fin Trama Ethernet (u 802.3) ---
****************** FIN DE PAQUETE *******************


Estadísticas de Captura:

- Paquetes Ethernet:                0
- Paquetes IEEE 802.3:              33
  · Paquetes IP:                    0
  · Paquetes no IP:                 33
    ~ Paquetes ICMP:                0
    ~ Paquetes TCP:                 0
    ~ Paquetes UDP:                 0
    ~ Paquetes desconocidos:        0
-----------------------------------------
- Total de Paquetes:                33
- Duración de la sesión de captura: 8ms

La captura ha terminado.

ESCOM. Redes de Computadoras - 2019
```

Con lo cual podremos corroborar que nuestro programa es capaz de análizar paquetes contenidos en un archivo con formato estándar de captura de paquetes (`.pcap`).

**Nota: Los paquetes que usé para este demo son los contenidos en el archivo `paquetes.pcap`, los cuales son específicos para probar el análisis de paquetes con encabezado Ethernet de tipo 802.3 pero funciona con cualquier tipo de paquetes.*

### Establecer filtros de captura.

Es indispensable que nuestro programa sea capaz de aplicar filtros de captura con el fin de permitirle al usuario explotar nuestro *Sniffer* de mejor manera. Para ello, podremos hacer uso de la captura desde un archivo o *al vuelo* y el filtro deberá contar con la sintáxis específica. Digamos que quisiéramos capturar **únicamente** todo el tráfico DNS, el cual es de tipo *UDP* empleando el puerto **53**, por lo que nuestro programa nos presentaría la siguiente salida:

```txt
Sniffer de Paquetes

Selecciona el tipo de captura:

  1) Captura de paquetes 'al vuelo'.
  2) Usar un archivo.

Tu opción: 1
Selecciona una interfaz de red:

1) en0 (Sin descripción)
2) p2p0 (Sin descripción)
3) awdl0 (Sin descripción)
4) bridge0 (Sin descripción)
5) utun0 (Sin descripción)
6) en1 (Sin descripción)
7) lo0 (Sin descripción)
8) gif0 (Sin descripción)
9) stf0 (Sin descripción)
10) XHC20 (Sin descripción)

Ingresa el número de la interfaz (1-10): 1
¿Cuál es el tamaño de paquete a usar?
(100 - 65536): 65536
¿Desea abrir la interfaz en modo promiscuo? S/N: S
¿Cuál es el tiempo de timeout que deseas usar (en ms)?
El valor recomendado es de 1000.
(10 - 10000): 1000
¿Deses guardar los paquetes capturados? S/N: N
¿Cuántos paquetes deseas capturar? (1-1000): 10
¿Desea usar un filtro de captura? S/N: S
Introduce tu filtro: port 53
¿El filtro "port 53" es correcto? S/N: S
Escuchando en: en0
***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:24:10
Número de Paquete: 0
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 94:FE:9D:62:3B:00
· MAC Origen: D4:61:9D:2D:E1:58
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 60
· Tamaño de Datos: 40 bytes
· Tiempo de Vida (TTL): 64
· Protocolo: 11 (UDP)
· Checksum: 2302
· ¿Checksum Correcto? Sí.
· IP Origen: 192.168.1.65
· IP Destino: 8.8.4.4
--- Fin de Paquete IP ---
--- Análisis UDP ---
· Puerto Origen: 34274
· Puerto Destino: 53
· Longitud: 40
· Checksum: 9EAA
· Pseudo Encabezado UDP:
  ~ IP Origen: 192.168.1.65
  ~ IP Destino: 8.8.4.4
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 17
  ~ Longitud de PDU: 40
· ¿Checksum UDP correcto? Sí.
--- Fin de Análisis UDP ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:24:10
Número de Paquete: 1
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 94:FE:9D:62:3B:00
· MAC Origen: D4:61:9D:2D:E1:58
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 60
· Tamaño de Datos: 40 bytes
· Tiempo de Vida (TTL): 64
· Protocolo: 11 (UDP)
· Checksum: 3414
· ¿Checksum Correcto? Sí.
· IP Origen: 192.168.1.65
· IP Destino: 8.8.4.4
--- Fin de Paquete IP ---
--- Análisis UDP ---
· Puerto Origen: 46624
· Puerto Destino: 53
· Longitud: 40
· Checksum: 3E19
· Pseudo Encabezado UDP:
  ~ IP Origen: 192.168.1.65
  ~ IP Destino: 8.8.4.4
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 17
  ~ Longitud de PDU: 40
· ¿Checksum UDP correcto? Sí.
--- Fin de Análisis UDP ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:24:10
Número de Paquete: 2
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 70
· Tamaño Total: 76
· Tamaño de Datos: 56 bytes
· Tiempo de Vida (TTL): 123
· Protocolo: 11 (UDP)
· Checksum: 8182
· ¿Checksum Correcto? Sí.
· IP Origen: 8.8.4.4
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
--- Análisis UDP ---
· Puerto Origen: 53
· Puerto Destino: 34274
· Longitud: 56
· Checksum: AC01
· Pseudo Encabezado UDP:
  ~ IP Origen: 8.8.4.4
  ~ IP Destino: 192.168.1.65
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 17
  ~ Longitud de PDU: 56
· ¿Checksum UDP correcto? Sí.
--- Fin de Análisis UDP ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:24:10
Número de Paquete: 3
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 70
· Tamaño Total: 88
· Tamaño de Datos: 68 bytes
· Tiempo de Vida (TTL): 123
· Protocolo: 11 (UDP)
· Checksum: B0AE
· ¿Checksum Correcto? Sí.
· IP Origen: 8.8.4.4
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
--- Análisis UDP ---
· Puerto Origen: 53
· Puerto Destino: 46624
· Longitud: 68
· Checksum: 755F
· Pseudo Encabezado UDP:
  ~ IP Origen: 8.8.4.4
  ~ IP Destino: 192.168.1.65
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 17
  ~ Longitud de PDU: 68
· ¿Checksum UDP correcto? Sí.
--- Fin de Análisis UDP ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:24:10
Número de Paquete: 4
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 94:FE:9D:62:3B:00
· MAC Origen: D4:61:9D:2D:E1:58
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 62
· Tamaño de Datos: 42 bytes
· Tiempo de Vida (TTL): 64
· Protocolo: 11 (UDP)
· Checksum: AC29
· ¿Checksum Correcto? Sí.
· IP Origen: 192.168.1.65
· IP Destino: 8.8.4.4
--- Fin de Paquete IP ---
--- Análisis UDP ---
· Puerto Origen: 30200
· Puerto Destino: 53
· Longitud: 42
· Checksum: 4D3E
· Pseudo Encabezado UDP:
  ~ IP Origen: 192.168.1.65
  ~ IP Destino: 8.8.4.4
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 17
  ~ Longitud de PDU: 42
· ¿Checksum UDP correcto? Sí.
--- Fin de Análisis UDP ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:24:10
Número de Paquete: 5
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 94:FE:9D:62:3B:00
· MAC Origen: D4:61:9D:2D:E1:58
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 62
· Tamaño de Datos: 42 bytes
· Tiempo de Vida (TTL): 64
· Protocolo: 11 (UDP)
· Checksum: A464
· ¿Checksum Correcto? Sí.
· IP Origen: 192.168.1.65
· IP Destino: 8.8.4.4
--- Fin de Paquete IP ---
--- Análisis UDP ---
· Puerto Origen: 56939
· Puerto Destino: 53
· Longitud: 42
· Checksum: 9A7E
· Pseudo Encabezado UDP:
  ~ IP Origen: 192.168.1.65
  ~ IP Destino: 8.8.4.4
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 17
  ~ Longitud de PDU: 42
· ¿Checksum UDP correcto? Sí.
--- Fin de Análisis UDP ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:24:10
Número de Paquete: 6
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 70
· Tamaño Total: 107
· Tamaño de Datos: 87 bytes
· Tiempo de Vida (TTL): 123
· Protocolo: 11 (UDP)
· Checksum: CCB2
· ¿Checksum Correcto? Sí.
· IP Origen: 8.8.4.4
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
--- Análisis UDP ---
· Puerto Origen: 53
· Puerto Destino: 30200
· Longitud: 87
· Checksum: DB13
· Pseudo Encabezado UDP:
  ~ IP Origen: 8.8.4.4
  ~ IP Destino: 192.168.1.65
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 17
  ~ Longitud de PDU: 87
· ¿Checksum UDP correcto? Sí.
--- Fin de Análisis UDP ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:24:11
Número de Paquete: 7
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 70
· Tamaño Total: 119
· Tamaño de Datos: 99 bytes
· Tiempo de Vida (TTL): 123
· Protocolo: 11 (UDP)
· Checksum: 720B
· ¿Checksum Correcto? Sí.
· IP Origen: 8.8.4.4
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
--- Análisis UDP ---
· Puerto Origen: 53
· Puerto Destino: 56939
· Longitud: 99
· Checksum: 4941
· Pseudo Encabezado UDP:
  ~ IP Origen: 8.8.4.4
  ~ IP Destino: 192.168.1.65
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 17
  ~ Longitud de PDU: 99
· ¿Checksum UDP correcto? Sí.
--- Fin de Análisis UDP ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:24:11
Número de Paquete: 8
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 94:FE:9D:62:3B:00
· MAC Origen: D4:61:9D:2D:E1:58
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 65
· Tamaño de Datos: 45 bytes
· Tiempo de Vida (TTL): 64
· Protocolo: 11 (UDP)
· Checksum: B322
· ¿Checksum Correcto? Sí.
· IP Origen: 192.168.1.65
· IP Destino: 8.8.4.4
--- Fin de Paquete IP ---
--- Análisis UDP ---
· Puerto Origen: 21761
· Puerto Destino: 53
· Longitud: 45
· Checksum: CB6F
· Pseudo Encabezado UDP:
  ~ IP Origen: 192.168.1.65
  ~ IP Destino: 8.8.4.4
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 17
  ~ Longitud de PDU: 45
· ¿Checksum UDP correcto? Sí.
--- Fin de Análisis UDP ---
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:24:11
Número de Paquete: 9
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 94:FE:9D:62:3B:00
· MAC Origen: D4:61:9D:2D:E1:58
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 65
· Tamaño de Datos: 45 bytes
· Tiempo de Vida (TTL): 64
· Protocolo: 11 (UDP)
· Checksum: EEA1
· ¿Checksum Correcto? Sí.
· IP Origen: 192.168.1.65
· IP Destino: 8.8.4.4
--- Fin de Paquete IP ---
--- Análisis UDP ---
· Puerto Origen: 58419
· Puerto Destino: 53
· Longitud: 45
· Checksum: 2F90
· Pseudo Encabezado UDP:
  ~ IP Origen: 192.168.1.65
  ~ IP Destino: 8.8.4.4
  ~ Reservado: 0
  ~ Protocolo (Encabezado IP): 17
  ~ Longitud de PDU: 45
· ¿Checksum UDP correcto? Sí.
--- Fin de Análisis UDP ---
****************** FIN DE PAQUETE *******************


Estadísticas de Captura:

- Paquetes Ethernet:                10
- Paquetes IEEE 802.3:              0
  · Paquetes IP:                    10
  · Paquetes no IP:                 0
    ~ Paquetes ICMP:                0
    ~ Paquetes TCP:                 0
    ~ Paquetes UDP:                 10
    ~ Paquetes desconocidos:        0
-----------------------------------------
- Total de Paquetes:                10
- Duración de la sesión de captura: 6012ms

La captura ha terminado.

ESCOM. Redes de Computadoras - 2019
```

Comprobando así que se cumplen los requisitos para especificar y aplicar filtros de captura.

### Exportar captura a un archivo `.pcap`

Exportar nuestra captura a un archivo de formato estándar (cómo lo es `.pcap`) nos permite a nosotros, como usuarios, capturar los paquetes y poder llevarlos a un software de análisis especializado como [WireShark][wireshark-url] para poder llevar a cabo un análisis más detallado con herramientas más completas (y complejas).

Para probar esta opción, seleccionaremos captura de paquetes *al vuelo* y, al llegar la opción de exportar a un archivo, seleccionaremos `S`, es decir, sí, y especificaremos el nombre del archivo para almacenar la tasa de captura. Imaginemos que queremos capturar todos los paquetes **ICMP** y exportarlos a un archivo `icmp.pcap` para después analizarlo con **WireShark**; la ejecución del programa con esos pasos en mente nos arroja:

```txt
Sniffer de Paquetes

Selecciona el tipo de captura:

  1) Captura de paquetes 'al vuelo'.
  2) Usar un archivo.

Tu opción: 1
Selecciona una interfaz de red:

1) en0 (Sin descripción)
2) p2p0 (Sin descripción)
3) awdl0 (Sin descripción)
4) bridge0 (Sin descripción)
5) utun0 (Sin descripción)
6) en1 (Sin descripción)
7) lo0 (Sin descripción)
8) gif0 (Sin descripción)
9) stf0 (Sin descripción)
10) XHC20 (Sin descripción)

Ingresa el número de la interfaz (1-10): 1
¿Cuál es el tamaño de paquete a usar?
(100 - 65536): 65536
¿Desea abrir la interfaz en modo promiscuo? S/N: S
¿Cuál es el tiempo de timeout que deseas usar (en ms)?
El valor recomendado es de 1000.
(10 - 10000): 1000
¿Deses guardar los paquetes capturados? S/N: S
Nombre del archivo para guardar: icmp.pcap
Los paquetes se guardarán en icmp.pcap
¿Cuántos paquetes deseas capturar? (1-1000): 20
¿Desea usar un filtro de captura? S/N: S
Introduce tu filtro: icmp
¿El filtro "icmp" es correcto? S/N: S
Escuchando en: en0
***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 0
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: C0
· Tamaño Total: 80
· Tamaño de Datos: 60 bytes
· Tiempo de Vida (TTL): 64
· Protocolo: 01 (ICMP)
· Checksum: 0270
· ¿Checksum Correcto? Sí.
· IP Origen: 192.168.1.254
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5084
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 1
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: C0
· Tamaño Total: 80
· Tamaño de Datos: 60 bytes
· Tiempo de Vida (TTL): 64
· Protocolo: 01 (ICMP)
· Checksum: 026F
· ¿Checksum Correcto? Sí.
· IP Origen: 192.168.1.254
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5084
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 2
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: C0
· Tamaño Total: 80
· Tamaño de Datos: 60 bytes
· Tiempo de Vida (TTL): 64
· Protocolo: 01 (ICMP)
· Checksum: 026E
· ¿Checksum Correcto? Sí.
· IP Origen: 192.168.1.254
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5084
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 3
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 96
· Tamaño de Datos: 76 bytes
· Tiempo de Vida (TTL): 254
· Protocolo: 01 (ICMP)
· Checksum: B5A6
· ¿Checksum Correcto? Sí.
· IP Origen: 200.38.193.226
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5073
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 4
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 96
· Tamaño de Datos: 76 bytes
· Tiempo de Vida (TTL): 254
· Protocolo: 01 (ICMP)
· Checksum: B5A4
· ¿Checksum Correcto? Sí.
· IP Origen: 200.38.193.226
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5073
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 5
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 96
· Tamaño de Datos: 76 bytes
· Tiempo de Vida (TTL): 254
· Protocolo: 01 (ICMP)
· Checksum: B5A3
· ¿Checksum Correcto? Sí.
· IP Origen: 200.38.193.226
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5073
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 6
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 168
· Tamaño de Datos: 148 bytes
· Tiempo de Vida (TTL): 252
· Protocolo: 01 (ICMP)
· Checksum: CFC1
· ¿Checksum Correcto? Sí.
· IP Origen: 189.246.2.214
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5073
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 7
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 168
· Tamaño de Datos: 148 bytes
· Tiempo de Vida (TTL): 252
· Protocolo: 01 (ICMP)
· Checksum: CFC0
· ¿Checksum Correcto? Sí.
· IP Origen: 189.246.2.214
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5073
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 8
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 168
· Tamaño de Datos: 148 bytes
· Tiempo de Vida (TTL): 252
· Protocolo: 01 (ICMP)
· Checksum: CFBF
· ¿Checksum Correcto? Sí.
· IP Origen: 189.246.2.214
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5073
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 9
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 96
· Tamaño de Datos: 76 bytes
· Tiempo de Vida (TTL): 252
· Protocolo: 01 (ICMP)
· Checksum: 29B8
· ¿Checksum Correcto? Sí.
· IP Origen: 201.125.120.45
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: E4CC
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 10
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 96
· Tamaño de Datos: 76 bytes
· Tiempo de Vida (TTL): 252
· Protocolo: 01 (ICMP)
· Checksum: 29B6
· ¿Checksum Correcto? Sí.
· IP Origen: 201.125.120.45
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: E4CD
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 11
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 96
· Tamaño de Datos: 76 bytes
· Tiempo de Vida (TTL): 252
· Protocolo: 01 (ICMP)
· Checksum: 29B5
· ¿Checksum Correcto? Sí.
· IP Origen: 201.125.120.45
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: E4CE
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 12
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 70
· Tamaño Total: 56
· Tamaño de Datos: 36 bytes
· Tiempo de Vida (TTL): 251
· Protocolo: 01 (ICMP)
· Checksum: 434A
· ¿Checksum Correcto? Sí.
· IP Origen: 189.247.252.41
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5084
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 13
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 70
· Tamaño Total: 56
· Tamaño de Datos: 36 bytes
· Tiempo de Vida (TTL): 251
· Protocolo: 01 (ICMP)
· Checksum: 434A
· ¿Checksum Correcto? Sí.
· IP Origen: 189.247.252.41
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5084
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 14
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 70
· Tamaño Total: 56
· Tamaño de Datos: 36 bytes
· Tiempo de Vida (TTL): 251
· Protocolo: 01 (ICMP)
· Checksum: 434A
· ¿Checksum Correcto? Sí.
· IP Origen: 189.247.252.41
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5084
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 15
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 70
· Tamaño Total: 96
· Tamaño de Datos: 76 bytes
· Tiempo de Vida (TTL): 250
· Protocolo: 01 (ICMP)
· Checksum: 05B8
· ¿Checksum Correcto? Sí.
· IP Origen: 108.170.254.1
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5073
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 16
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 70
· Tamaño Total: 80
· Tamaño de Datos: 60 bytes
· Tiempo de Vida (TTL): 59
· Protocolo: 01 (ICMP)
· Checksum: 59FE
· ¿Checksum Correcto? Sí.
· IP Origen: 108.170.254.17
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5084
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 17
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 70
· Tamaño Total: 80
· Tamaño de Datos: 60 bytes
· Tiempo de Vida (TTL): 59
· Protocolo: 01 (ICMP)
· Checksum: 59FB
· ¿Checksum Correcto? Sí.
· IP Origen: 108.170.254.17
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5084
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:04
Número de Paquete: 18
--- Trama Ethernet (u 802.3) ---
· MAC Destino: D4:61:9D:2D:E1:58
· MAC Origen: 94:FE:9D:62:3B:00
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 70
· Tamaño Total: 80
· Tamaño de Datos: 60 bytes
· Tiempo de Vida (TTL): 58
· Protocolo: 01 (ICMP)
· Checksum: A17A
· ¿Checksum Correcto? Sí.
· IP Origen: 108.170.236.43
· IP Destino: 192.168.1.65
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 0B
· Tipo (decimal): 11
· Código: 00
· Código (decimal): 0
· Mensaje de control: TTL expired in transit
· Checksum: 5084
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************

***************** PAQUETE CAPTURADO *****************
Hora de Captura: 21:29:06
Número de Paquete: 19
--- Trama Ethernet (u 802.3) ---
· MAC Destino: 94:FE:9D:62:3B:00
· MAC Origen: D4:61:9D:2D:E1:58
· Ether Type: 0800
· Tipo de Paquete: 2048
· El paquete es Ethernet.
· ¿Es un paquete IP? Sí.
--- Fin Trama Ethernet (u 802.3) ---
--- Paquete IP ---
· Versión de IP: 4
· Longitud de Encabezado: 5 x 4 = 20 bytes.
· Tipo de Servicio: 00
· Tamaño Total: 56
· Tamaño de Datos: 36 bytes
· Tiempo de Vida (TTL): 64
· Protocolo: 01 (ICMP)
· Checksum: 651A
· ¿Checksum Correcto? Sí.
· IP Origen: 192.168.1.65
· IP Destino: 198.54.117.10
--- Fin de Paquete IP ---
---Análisis ICMP---
· Tipo: 03
· Tipo (decimal): 3
· Código: 03
· Código (decimal): 3
· Mensaje de control: Destination port unreachable
· Checksum: 01DB
---Fin de Análisis de ICMP---
· Paquete guardado en: icmp.pcap
****************** FIN DE PAQUETE *******************


Estadísticas de Captura:

- Paquetes Ethernet:                20
- Paquetes IEEE 802.3:              0
  · Paquetes IP:                    20
  · Paquetes no IP:                 0
    ~ Paquetes ICMP:                20
    ~ Paquetes TCP:                 0
    ~ Paquetes UDP:                 0
    ~ Paquetes desconocidos:        0
-----------------------------------------
- Total de Paquetes:                20
- Duración de la sesión de captura: 14022ms

La captura ha terminado.

ESCOM. Redes de Computadoras - 2019
```

Siendo así exitosa la prueba y ahora permitiéndonos realizar un análisis más detallado de los paquetes en crudo en softwares compatibles como **WireShark** etc.

## Conclusión

El desarrollo de una herramienta tan simple conlleva un entendimiento general de los conceptos de redes para poder descomponer los datos capturados en las distintas interpretaciones que puedan ser útiles al usuario. Es importante notar que, aunque múltiples programas de captura de paquetes existen actualmente en el mercado, desarrollar un _Sniffer_ nos permite entender de mejor manera como se comporta nuestra red y los paquetes que discurren a través de ella.

---

> Escuela Superior de Cómputo
>
> Redes de Computadoras

Humberto Alejandro Ortega Alcocer.

Hecho con ❤️ en 2019.
