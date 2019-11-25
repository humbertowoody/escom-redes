# Protocolo de Datagrama de Usuario (UDP)

Este protocolo de capa de transporte brinda las siguientes funciones:

- Entrega de datos bajo la política del mejor esfuerzo (no garantiza que los datos lleguen en orden, o sin duplicados), pero es rápido.
- Direccionamiento en punto de servicio.
- Tiene su especificación en el [RFC 768][rfc-768-url]

## Encabezado

Esta es la descripción del encabezado de UDP:

![Encabezado de UDP][udp-header-img]

[rfc-768-url]: https://tools.ietf.org/html/rfc768
[udp-header-img]: https://notes.shichao.io/tcpv1/figure_10-2_600.png
