# Checksum (Suma de comprobación)

Este algoritmo se implementa en la mayoría de los protocolos de comunicación dada la facilidad de la implementación. Es de las que casi siempre vamos a encontrar porque es sencillo de implementar a nivel hardware. Aplica para capa 3+.

Este algoritmo es muy bueno porque permite detectar cuando hay un error pero **no** corrige el error.

Procedimiento:

1. Ordenar los datos en palabras de 16 bits (2 bytes).
2. Poner ceros en la posición del checksum y sumar (considerar acarreos).
3. Sumar fuera de los 16 bits
4. Complemento a 1 (negar) el resultado.

Es importante primero extraer el encabezado *Ethernet* de la trama que nos den, de ahí tenemos que extraer el encabezado IP y con ese encabezado es dónde vamos a hacer la Suma de Comprobación. La trama Ethernet cuenta con su propio algoritmo de control de error, en ese caso siendo CRC.
