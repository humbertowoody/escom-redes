# Direccionamiento

El direccionamiento es el proceso por el cual se envían los paquetes. Cuando se creó la arquitectura TCP/IP, en 1983, ya existía el protocolo IPv4.

En arquitecturas x86, se podría representar una IP como un número entero pero no se puede hacer agregación ni otras cosas.

Número de direcciones IP (versión 4): 2^32.

## Clases

| Clase |            Rango            |         Rango Útil          |                               Descripción                                |
| :---: | :-------------------------: | :-------------------------: | :----------------------------------------------------------------------: |
|   A   |  0.0.0.0 - 127.255.255.255  |  1.0.0.1 - 126.255.255.254  |          (2^7)-2 redes, y cada red puede tener (2^24)-2 hosts.           |
|   B   | 128.0.0.0 - 191.255.255.255 | 128.0.0.1 - 191.255.255.254 | Puede haber hasta (2^14)-2 redes; y cada una puede tener (2^16)-2 hosts. |
|   C   | 192.0.0.0 - 223.255.255.255 | 192.0.0.1 - 223.255.255.254 |      Puede haber (2^21)-2 redes; cada una con hasta (2^8)-2 hosts.       |
|   D   | 224.0.0.0 - 239.255.255.255 | 225.0.0.1 - 239.255.255.254 |                 Puede haber hasta 2^28 grupos multicast                  |
|   E   | 240.0.0.0 - 255.255.255.255 | 240.0.0.1 - 255.255.255.254 |                                 Sin uso.                                 |

Hay dos tipos de direcciones:

- Unidifusión (Unicast): A, B y C.
- Multidifusión (Multicast): D y E.

### Direcciones Privadas (RFC 1918)

El _RFC 1918_ establece el rango de direcciones privadas predefinidas para usos específicos. Dependiendo el número de dispositivos que queramos tener en una LAN, seleccionamos alguno de estos rangos.

| Clase |             Rango             |
| :---: | :---------------------------: |
|   A   |   10.0.0.0 - 10.255.255.255   |
|   B   |  172.16.0.0 - 172.31.255.255  |
|   C   | 192.168.0.0 - 192.168.255.255 |

### Direcciones de propósito específico

Algunas direcciones tienen un propósito específico, estas direcciones se emplean para tareas definidas por el IANA (ICANN).

|    Dirección    |                                   Descripción                                    |
| :-------------: | :------------------------------------------------------------------------------: |
|     0.0.0.0     |     Se utiliza para identificar máquinas que no cuentan con una dirección IP     |
|    127.0.0.1    | Es la dirección del propio equipo (`localhost` también conocido como `loopback`) |
|    224.0.0.1    |                     Es la dirección `loopback` de multicast                      |
| 255.255.255.255 |                                    Broadcast                                     |

### NAT

_Network Address Translation_, es un servicio que _traduce_ una dirección pública a una dirección privado. El servicio NAT es el que permite que tengamos un router en nuestras casas con una dirección IP pública y, cuando llega un paquete, NAT revisa su lista de direcciones MAC asociadas a un puerto específico en su dirección IP y lo redirige al cliente en la red privada.

Surge a raíz del agotamiento de direcciones IP públicas IPv4 y la incompatibilidad que hubera generado un cambio a IPv6 en equipos _legacy_.

### DHCP

DHCP es el servicio de asignación de direcciones IP, es decir, se encarga de que, cuando un nuevo dispositivo se conecta a una red, asignarle su configuración de red.

La configuración de red que requiere cualquier dispositivo es:

- **IP**: La dirección IP del dispositivo.
- **Máscara**: La máscara de red (o de subred).
- **Puerta de Enlace**: La puerta de enlace de la red (router).
- **DNS**: El servidor DNS que resolverá los requests DNS de la red.

#### Máscara

La máscara se utiliza para tomar decisiones de _¿a quién pasarle un paquete?_ En el sentido de que podemos pasarle el paquete a un host dentro del mismo segmento de red o no. Las máscaras básicas son:

| Clase | Bits de Red | Bits de Host |    Máscara    |
| :---: | :---------: | :----------: | :-----------: |
|   A   |      8      |      24      |   255.0.0.0   |
|   B   |     16      |      16      |  255.255.0.0  |
|   C   |     24      |      8       | 255.255.255.0 |

Si analizamos la pila de protocolos de TCP/IP, veremos que:

1. La aplicación genera datos y añade su cabecera.
2. Al PDU se le añade la cabecera TCP o UDP.
3. Se le añade la IP origen y la IP destino.
4. Se coloca la MAC origen (nuestra MAC) y en la destino (?)

Para definir si la transmisión va a ser de tarjeta de red a tarjeta de red, o si va a pasar por un router, se requiere saber si están en el mismo segmento de red, para esto se hace una operación AND entre las IPs y la Máscara del host.

- IP origen **AND** Máscara.
- IP destino **AND** Máscara.

Si el resultado coincide, están en el mismo segmento y se usa ARP para saber a quién hablarle, en caso contrario, se pasa al Router y que él se haga bolas.

## VLSM

> Máscara de Subred de Longitud Variable

Fue definido por el **IETF** para resolver el problema de máscaras fijas del direccionamiento por clases.

VLSM permite que podamos ajustar las direcciones disponibles bajo el campo de **longitud de prefijo**. Por ejemplo:

- Dirección: `200.1.1.0/30`
  - La dirección es `200.1.1.0`
  - La _longitud de prefijo_ es de `30`.
- Máscara: `255.255.255.252`

El rango dada la notación especificada es:

|    IP     |   Descripción    |
| :-------: | :--------------: |
| 200.1.1.0 |    ID de Red     |
| 200.1.1.1 |    Rango útil    |
| 200.1.1.2 |    Rango útil    |
| 200.1.1.3 | Broadcast de Red |

Como se puede ver, lo que esto nos permite es generar una longitud variable en nuestra red, de esta forma nos evitamos el problema del _Direccionamiento por Clases_ en dónde tendríamos que emplear, al menos, una máscara de clase C con 254 direcciones IP, que puede ser mucho más de lo que realmente necesitamos; o al menos no poder ser específicos como lo permite el VLSM.

## CIDR
