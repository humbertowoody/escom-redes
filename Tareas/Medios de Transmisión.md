# Medios de Transmisión

Existen múltiples medios de transmisión, cada uno con distintas características y cualidades. La definición de medio de transmisión es:

> El medio de transmisión constituye el soporte físico a través del cual emisor y receptor pueden comunicarse en un sistema de transmisión de datos.
> 
> -- <cite>[NEO Research Group, Universidad de Málaga, España][1]</cite>

Esto nos deja ante la pregunta ¿De qué soporte físico hablan? Es muy común que, al pensar sobre la información que enviamos día con día a través de internet (y de las redes intermedias), dejamos de lado la importancia del *medio físico* por el cual viajan, finalmente, nuestros datos. A este proceso se le conoce como *serialización de datos*, y constituye en construir, a partir de una serie de datos digitales, una señal analógica capaz de ser enviada a través de un medio físico como lo puede ser un cable de cobre, una fibra de vidrio o algo como una señal dentro del espectro electromagnético.

Este soporte físico, o medio, es el pilar de la comunicación, y grandes investigaciones se han llevado a cabo con el fin de contestar a la antiquísima y, muy probablemente, pregunta sin fin: ¿Cuál es el mejor medio para transmitir información?

Esa pregunta, tan simple como se alcanza a vislumbrar y tan compleja como sus más ávidos contendientes han observado, ha sido la base para que se realicen múltiples desarrollos fundamentados en el conocimiento físico sobre el medio para intentar llevar las velocidades de transmisión al máximo posible. Esto, a su vez, ha desembocado en que existan un sinfin de medios de transmisión, desde los más austeros hsata los indescriptiblemente más complejos. Podría comenzarse por hablar acerca del *par trenzado*, que consiste en 2 o más cables de cobre entrelazados entre sí por los cuales discurren una serie de pulsos eléctricos de +5v, de forma salteada pero constante, y que a su vez representan la información en su forma "cruda", como algunos autores señalan, es decir, en binario. Un emisor envía una **ráfaga de bits** a través de los cables, y un receptor los recibe y los pone a disposición del equipo cliente. 

Relizar esta tarea es sumamente complejo, y la mayoría de las veces inútil. Esto debido a que no todo el mundo puede tener a su disposición un cable *UDP* con el cual enchufar todos sus dispositivos. Es por ello, que científicos e ingenieros diseñaron medios de transmisión que no requieren un cable, sino que operan sobre el espectro radioeléctrico empleando ondas del campo electromagnético para enviar pulsos que igual representan ráfagas de bits, con la única diferencia de que, al no requerir un cable, los datos viajan por el aire y son enviados, o recibidos según sea el caso, sin necesidad de requerir una conexión fija.

Es por eso, que los medios de transmisión se dividen en 2 subtipos: los **medios guiados** y los **medios no guiados**. Cada uno con sus distintas peculiaridades y consideraciones hacen posible que, bajo una serie de protocolos y mucho trabajo por parte de organismos de estandarización, podamos contar con conectividad en los más finos hoteles así como en las más alejadas regiones.

## Medios Guiados

Los medios guiados conducen (guían) las ondas a través de un camino físico, ejemplos de estos medios son el cable coaxial, la fibra óptica y el par trenzado. Dentro de los más destacados se encuentran:


|Medio|Distancia Máxima de Segmento|Ancho de Banda|Velocidad de Transmisión|
|:--:|:--:|:--:|:--:|
|Par Trenzado|100m|Dependiendo de la categoría, puede ir desde 16MHz en Categoría 3, hasta 100MHz en Categorías 5 y 5e. La categoría 6 tiene 250MHz y la categoría 6A 500 MHz.| 100Mbps en categoría 5e|
|Cable Coaxial|1km a 10km|350MHz|10Mbps|
|Fibra Óptica|100km|2GHz|2Gbps|

## Medios no Guiados

Los medios no guiados proporcionan un soporte para que las ondas se transmitan, pero no las dirigen; como ejemplo de ellos tenemos el aire y el vacío. Entre los más destacados se encuentran:

|Medio|Distancia Máxima de Segmento|Ancho de Banda|Velocidad de Transmisión|
|:--:|:--:|:--:|:--:|
|Microondas Terrestres|5 km|3.5 - 28 Ghz|2048 Kbps
|Satélites|100 km| 500 MHz divididos generalmente entre 12 transmisores/receptores dejando 36 MHz cada uno|128 Kbps - 4 Mbps|
|Ondas de Radio|10 km|300 MHz - 300 GHz|1 - 100 Mbps|
|WiFi|50m - 100m|2.4Ghz / 5Ghz|11Mbps / 300 Mbps

[1]: http://neo.lcc.uma.es/evirtual/cdd/tutorial/fisico/Mtransm.html
