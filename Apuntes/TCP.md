# Protoclo de Control de Transmisión (TCP)

Este protocolo de capa de transporte brinda las siguientes funciones:

- Entrega en orden, sin duplicados, sin errores. **Control de error de extremo a extremo**.
- Control de flujo.
- Direccionamiento en punto de servicio.
- Tiene su especificación en [RFC 793][rfc-793-link].

## Encabezado

A continuación, se muestra el formato del encabezado para el protocolo TCP:

![Encabezado de TCP][tcp-header-img]


[rfc-793-link]: https://tools.ietf.org/html/rfc793
[tcp-header-img]: http://telescript.denayer.wenk.be/~hcr/cn/idoceo/images/tcp_header.gif
