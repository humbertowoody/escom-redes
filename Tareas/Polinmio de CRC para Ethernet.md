# Polinmio de CRC para Ethernet

## CRC

El **Chequeo de Redundancia Cíclica** (CRC por sus siglas en inglés), es uno de los algoritmos para control de error más antiguos y usados en protocolos de comunicación así como aplicaciones que requieran identificar errores así como encontrar la posición donde se dió dicho error y, en caso de ser posible, realizar la corrección del daño ahorrando así, de entrada, una retransmisión del paquete.

Para funcionar, CRC hace uso de un **polinomio generador** que permite, dependiendo de la *complejidad* del mismo, añadir *n* bits a un mensaje para después verificarlo utilizando el polinomio como divisor del mensaje y verificando de forma cíclica cada parte de la división para encontrar el error.

A mayor complejidad de dicho polinomio, mayor cantidad de bits que pueden ser codificados así como la complejidad de la comprobación lo que vuelve difícil modificar información sin alterar el resultado del mensaje.

## CRC-32 para Ethernet

En el caso específico del protocolo **Ethernet**, se incluye al final del paquete un campo de `CRC` dónde los equipos en la capa de enlace pueden verificar la integridad del paquete y, de ser posible, corregir algún error. Esto permite que las redes de computadoras puedan actuar en función de la integridad de la información y garantizar que únicamente la información que se quiso transmitir es, en verdad, la que fue transmitida.

El polinomio que se emplea en Ethernet es:


$x^{{32}}+x^{{26}}+x^{{23}}+x^{{22}}+x^{{16}}+x^{{12}}+x^{{11}}+x^{{10}}+x^{8}+x^{7}+x^{5}+x^{4}+x^{2}+x+1$

Este polinimio, es capaz de trabajar en grupos de 32 bits, haciéndolo ideal para las cargas de trabajo en Ethernet. A su vez, éste polinomio fue estudiado y seleccionado finalmente para ser dentro de los más usados, alrededor 1975, cuando CRC se empezó a popularizar siendo eficiente para múltiples usos.


## Conclusión

CRC es uno de los algoritmos de detección de error más antiguos y más usados. Una de las partes más cruciales es la selección del polinomio generador puesto que éste determina los alcances del chequeo a realizar así como la fiabilidad del resultado arrojado. Además, dependiendo del polinomio seleccionado, éste puede ser implementado 100% a nivel hardware, con lo que se pueden lograr chequeos eficientes y seguros.
