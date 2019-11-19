# Código de Hamming

Dada una cadena *M* de *m* bits de longitud, se agregan *n* bits de paridad para formar la trama *T* a ser transmitida con un tramaño *m+n* de bits. Los bits de paridad (bits de Hamming) se colocan en posiciones que son múltiplos de potencias de 2 y se calculan de la siguiente manera:

Dado *M* = `10011101001011101011110`, generar *T*.

- Tenemos que calcular *n* (los bits de paridad), para esto, se debe cumplir que:
  - *2^n >= m + n + 1*
  - Lo podemos hacer intuitivo, probando que se cumpla la desigualdad:
    - *2^5 >= 22 + n + 1*
    - *2^5 >= 22 + 5 + 1*
    - *32 >= 22 + 5 + 1* 
    - *32 >= 28* ✅
- Conociendo los bits de paridad *(n)*, podemos ahora armar la nueva cadena de la siguiente forma:

|Posición de Bits|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|27| 1's|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|*Bits de Hamming*|*H*|*H*|1|*H*|0|0|1|*H*|1|1|0|1|0|0|1|*H*|0|1|1|1|0|1|0|1|1|1|0||
|Primer Bit (1)|**0**||1||0||1||1||0||0||1||0||1||0||0||1||0|*6*|
|Segundo Bit (2)||**0**|1|||0|1|||1|0|||0|1|||1|1|||1|0|||1|0|*8*|
|Tercer Bit (4)||||**1**|0|0|1|||||1|0|0|1|||||1|0|1|0|||||*6*|
|Cuarto Bit (8)||||||||**1**|1|1|0|1|0|0|1|||||||||1|1|1|0|*8*|
|Quinto Bit (16)||||||||||||||||**1**|0|1|1|1|0|1|0|1|1|1|0|*8*|
|***T***|**0**|**0**|1|**1**|0|0|1|**1**|1|1|0|1|0|0|1|**1**|0|1|1|1|0|1|0|1|1|1|0||

- El procedimiento es simple:
  - Colocamos los bits de Hamming (o de paridad) en las posiciones que van de 2^n[*i*].
  - Colocamos la cadena **en el orden que se encuentra** rellenando los huecos entre los bits de paridad.
  - Finalmente analizamos cada bit de paridad.
  - Iniciamos en la posición del bit de paridad, y a partir de ahí bajamos el número del bit **sí** y después **no**. Por emeplo, en la posición del *Primer Bit (1)*, se inicia en el primer bit de paridad, y a partir de ahí, dado que es *1* el valor que se tiene, se baja 1 sí y 1 no. Para el *Segundo Bit (2)*, nos colocamos en la posición del segundo bit y bajamos 2 sí y 2 no.
  - Contamos para cada fila los 1's y, como siempre deben ser pares, seleccionamos el valor del bit de paridad dependiendo de si hace falta o no para complementar a un número par.
  - Finalmente armamos la cadena *T*.
- Colocando los *bits de paridad* de forma ordenada tendríamos:

||H1|H2|H3|H4|H5||
|:---:|:---:|:---:|:---:|:---:|:---:|---:|
|Binario|0|0|1|1|1|
|Decimal|||4|2|1|(4 + 2 + 1) = **7**|

- Con esto sabemos que el **7º** bit de la cadena original *(M)*, es el que tiene el error, por lo que al invertirlo, deberá corregirse el error.

### Referencias Externas

- [Wikipedia: Código de Hamming](https://es.wikipedia.org/wiki/C%C3%B3digo_Hamming)