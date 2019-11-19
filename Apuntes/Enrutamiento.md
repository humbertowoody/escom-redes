# Enrutamiento

> Es el proceso de reenviar paquetes entre redes, siempre buscando la mejor ruta. Para encontrar la mejor ruta se toma en cuenta la tabla de enrutamiento, distancia administrativa, ancho de banda, MTU etc.

- Enrutamiento interior: Se da dentro de un Sistema Autónomo.
- Enrutamiento exterior: Se da entre Sistemas Autónomos.

## Sistemas Autónomos

### Sistema Autónomo (AS)

Se define como un conjunto de redes IP que poseen una política de rutas propia e independiente. Se identifican a través de *Números de Sistemas Autónomos*.

### Número de Sistema Autónomo (ASN)

Hasta el 2007 eran números de 16 bits, ahora son de 32 bits e identifican de manera única un Sistema Autónomo.


## Tipos de Enrutamiento

### Estático

Se construye a mano la tabla de enrutamiento, agregando los segmentos de red a los que el enrutador no está conectado.

#### Sintáxis

`ip route <Dst> <Máscara> <Siguiente salto/Interfaz> [<Distancia Administrativa>]`

Por ejemplo:

`ip route 40.0.0.0 255.0.0.0 20.255.255.253`

### Dinámico

Se utiliza un protocolo de enrutamiento capaz de detectar cambios en la topología de la red y así recalcular la tabla de enrutamiento y propagar los cambios a sus vecinos. La mayoría de los protocolos de enrutamiento se basan en los siguientes algoritmos:

- Dijkstra: Algoritmo estado-enlace (costo)
- Bellman-Ford: Algoritmo vector-distancia (basado en saltos)

