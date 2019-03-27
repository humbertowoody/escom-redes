# Direccionamiento

El direccionamiento es el proceso por el cual se envían los paquetes. Cuando se creó la arquitectura TCP/IP, en 1983, ya existía el protocolo IPv4.

En arquitecturas x86, se podría representar una IP como un número entero pero no se puede hacer agregación ni otras cosas.

Número de direcciones IP (versión 4): 2^32.

## Clases

| Clase |            Rango            |                               Descripción                                |
| :---: | :-------------------------: | :----------------------------------------------------------------------: |
|   A   |  0.0.0.0 - 127.255.255.255  |          (2^7)-2 redes, y cada red puede tener (2^24)-2 hosts.           |
|   B   | 128.0.0.0 - 191.255.255.255 | Puede haber hasta (2^14)-2 redes; y cada una puede tener (2^16)-2 hosts. |
|   C   | 192.0.0.0 - 223.255.255.255 |      Puede haber (2^21)-2 redes; cada una con hasta (2^8)-2 hosts.       |
|   D   | 224.0.0.0 - 239.255.255.255 |                 Puede haber hasta 2^28 grupos multicast                  |
|   E   | 240.0.0.0 - 255.255.255.255 |                                 Sin uso.                                 |

Hay dos tipos de direcciones:

- Unidifusión (Unicast): A, B y C.
- Multidifusión (Multicast): D y E.

## VLSM

## CIDR