# Protocolo de Mensajes de Control de Internet (ICMP)    

Este protocolo es utilizado para 2 propósitos:

1. Informar condiciones de error durante el enrutamiento de un paquete.
2. Brindar información de control.

Tiene su especificación en el [RFC 792][rfc-792] y su funcionamiento se da en la capa de Internet (TCP/IP) encapsulado dentro de IP (protocolo = 1).

## Formato de Cabecera

El formato de los mensajes ICMP puede variar, pero siempre conserva los siguientes 3 campos:

![Cabecera de ICMP][icmp-header-image]

## Tipos y Códigos

A continuación, una tabla de referencia de los distintos tipos de códigos y tipos que pueden presentarse en ICMP:

|Tipo|Código|Descripción|
|:---:|:---:|:---:|
|0|0|echo reply|
|3|0|network unreachable|
|3|1|host unreachable|
|3|2|protocol unreachable|
|3|3|port unreachable|
|3|4|fragmentation needed but DF bit set|
|3|5|source route failed|
|3|6|destination network unknown|
|3|7|destination host unknown|
|3|9|destination host administratively prohibited|
|4|0|source quench|
|5|0|redirect for network|
|5|1|redirect for host|
|5|2|redirect for TOS and network|
|8|0|echo request|
|11|0|TTL=0 durint transit|
|12|0|IP header bad|
|13|0|timestamp request|
|14|0|timestamp response|

[icmp-header-image]: https://encrypted-tbn0.gstatic.com/images?q=tbn%3AANd9GcREl9EnTAx1FtOX5OaVNUd5Obyi9FjGIYAu1Y7-zcXvf643e8JV
[rfc-792]: https://tools.ietf.org/html/rfc792
