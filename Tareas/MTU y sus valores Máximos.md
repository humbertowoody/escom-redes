# MTU y sus valores Máximos

El **MTU** o *Maximum Transfer Unit*, es la **unidad máxima de transmisión** de un protocolo de comunicaciones, es decir, la cantidad máxima de información que puede contener una unidad de información de un protocolo de comunicaciones. 

Como sabemos, cada capa de la tira de protocolos TCP/IP opera con un distinto encabezado el cual envuelve los datos con información de control que permiten al receptor validar el mensaje así como ordenarlo y entregarlo correctamente. Cada protocolo especifica su *MTU* de forma que los desarrolladores puedan dividir su información a transmitir en paquetes de la longitud máxima de MTU específicada.

Es común que en redes grandes se modifiquen los valores de MTU para reducir congestionamiento interno, así como para tener un mejor control sobre el desempeño de la red. Al restringir o aumentar los tamaños del MTU el administrador de la red puede optar por distintas opciones de configuración que permitirán que algunas aplicaciones operen de forma más eficiente que otras.

## Valores máximos de MTU

Los valores para el MTU varían de protocolo a protocolo, a continuación, una tabla con los valores de cada uno:

|Protocolo|Capa|Valor Máximo|
|:---:|:---:|:---:|
|Ethernet|Red|1500 bytes|
|PPPoE|Red|1492 bytes|
|ATM (AAL5)|Red| 9180 bytes|
|FDDI|Red| 4470 bytes|
|PPP|Red| 576 bytes|
|IP*|Transporte| 64 KB|

> **Nota*: Aunque se indica 64KB como la capacidad máxima de IP, la realidad es que dicho valor es únicamente teórico dado que la mayoría de los paquetes se mantienen dentro del rango de *Ethernet* siendo 1500 bytes el estándar, sin embargo, el valor mínimo (y por default) es de 576 byts.

## Conclusión

Distintos protocolos ofrecen distintas capacidades de comunicación de datos, es importante conocer la cantidad máxima de información que puede ser enviada a través de un protocolo para diseñar nuestras apliaciones de forma que puedan trabajar y aprovechar de forma eficaz cada uno de los protocolos disponibles. Para eso está el **MTU**, para indicarnos cuánto es el máximo número de datos que podemos enviar vía un protocolo específico y para que, en caso de tener que administrar o configurar una red de computadoras, podamos ajustar sus valores de **MTU** de operación para poder solucionar dificultades implícitas en la red así como optimizar ciertas aplicaciones con requisitos específicos (como imágenes médicas, videojuegos y demás).
