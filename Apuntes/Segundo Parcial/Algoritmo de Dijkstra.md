
# Algoritmo de Dijkstra

El algoritmo de Dijkstra es uno de los más reconocidos y usados algoritmos. Se utiliza en múltiples áreas de la computación y, en redes, es uno de los usados para calcular la *Tabla de Ruteo* para obtener el **camino más corto**. Wikipedia lo define como:

> El algoritmo de Dijkstra, también llamado algoritmo de caminos mínimos, es un algoritmo para la determinación del camino más corto, dado un vértice origen, hacia el resto de los vértices en un grafo que tiene pesos en cada arista. Su nombre alude a Edsger Dijkstra, científico de la computación de los Países Bajos que lo describió por primera vez en 1959.
> 
> [Wikipedia: Algoritmo de Dijkstra][dijkstra-wikipedia]

Lo que se hace es calcular 

## Pseudocódigo

El algoritmo de Dijkstra es un algoritmo de tipo *P*, por lo que se garantiza su finalización en tiempo polinómico.

A continuación el pseudocódigo:

```text
Sea +N = número de nodos en la red
    +S = Nodo origen
    +M = Conjunto de nodos incorporados por el algoritmo
    +dij = Costo asociado al enlace entre los nodos iej, donde:
        dij = { ∞, cuando no hay un enlace directo entre los nodos iej
              { 0, cuando i = j
              { > 0, cuando hay un enlace directo entre los nodos iej
        Dn = Costo encontrado pr el algoritmo, dado
            Dn = min[dn, dw+dnw]
```

## Ejemplo

Teniendo el siguiente grafo:

![Imgur](https://i.imgur.com/Q0H6CB8.jpg)

Para calcular la tabla de ruteo, primero ejecutamos el algoritmo de Dijkstra tomando como nodo origen el #4. El resultado es:

|M|D1|Trayectoria|D2|Trayectoria|D3|Trayectoria|D5|Trayectoria|D6|Trayectoria|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|4|5|4-1|3|4-2|3|4-3|1|4-5|8|4-6|
|4,5|5|4-1|3|4-2|2|4-5-3|||3|4-5-6|
|4,5,3|3|4-5-3-1|3|4-2|||||3|4-5-6|
|4,5,3,1|||3|4-3|||||3|4-5-6|
|4,5,3,1,2|||||||||3|4-5-6|
|4,5,3,1,2,6|

### Tabla de Enrutamiento resultante

El resultado para la tabla de enrutamiento es:

|Nodo|Métrica|Siguiente Salto|
|:---:|:---:|:---:|
|1|4|5
|2|5|5
|3|3|5
|4|3|5
|5|2|5
|6|0|-

[dijkstra-wikipedia]: https://es.wikipedia.org/wiki/Algoritmo_de_Dijkstra
