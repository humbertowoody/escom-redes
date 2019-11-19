# CRC - Verificación de Redundancia Cíclica

> A cyclic redundancy check (CRC) is an error-detecting code commonly used in digital networks and storage devices to detect accidental changes to raw data. Blocks of data entering these systems get a short check value attached, based on the remainder of a polynomial division of their contents. On retrieval, the calculation is repeated and, in the event the check values do not match, corrective action can be taken against data corruption. CRCs can be used for error correction (see bitfilters).
>
> CRCs are so called because the check (data verification) value is a redundancy (it expands the message without adding information) and the algorithm is based on cyclic codes. CRCs are popular because they are simple to implement in binary hardware, easy to analyze mathematically, and particularly good at detecting common errors caused by noise in transmission channels. Because the check value has a fixed length, the function that generates it is occasionally used as a hash function.
>
> The CRC was invented by W. Wesley Peterson in 1961; the 32-bit CRC function, used in Ethernet and many other standards, is the work of several researchers and was published in 1975.
>
> – [Wikipedia - CRC](https://en.wikipedia.org/wiki/Cyclic_redundancy_check)

## Algoritmo

- Dado M = un mensaje de tamaño 'n' bits a ser transmitido, se agregan a el 'n' bits de paridad para formar la trama 'T' a ser transmitida, T se obtiene de:
  - T = 2^n M + FCS
  - FCS = Secuencia de comprobación de la trama. Es el resíduo de (2^n M)/p dónde *p* es el polinomio generado.
  - La comprobación de la trama se realiza dividiendo T/P y obteniendo el residuo *r*.
    - Si *r* = 0: La trama contiene errores.
    - Si *r* != 0: La trama **no** contiene errores.
  - n = Al orden del polinomio del mensaje. Para eso, se toma cada bit, de derecha a izquierda como x^0, x^1, ..., x^n, por ejemplo:
    - <table>
        <tbody>
            <tr>
                <th>Mensaje</th>
                <td>1</td>
                <td>1</td>
                <td>0</td>
                <td>1</td>
                <td>0</td>
                <td>1</td>
            </tr>
            <tr>
                <th>Poliniomio Base</th>
                <td>x^5</td>
                <td>x^4</td>
                <td>x^3</td>
                <td>x^2</td>
                <td>x^1</td>
                <td>x^0</td>
            </tr>
            <tr>
                <th>Polinomio Real</th>
                <td>✅</td>
                <td>✅</td>
                <td>❌</td>
                <td>✅</td>
                <td>❌</td>
                <td>✅</td>
            </tr>
            <tr>
                <th>Polinomio Resultante</th>
                <td colspan=6, style='text-align:center;vertical-align:middle'>x^5 + x^4 + x^2 + 1</td>
            </tr>
        </tbody>
      </table>

    - Por lo que el orden es de **5**, dado que el exponente más grande es 5.

## El polinomio generador

El polinomio empleado para generar el cálculo de CRC, en implementaciones oficiales [como Ethernet](https://en.wikipedia.org/wiki/Cyclic_redundancy_check) cuentan con su propio polinomio generador definido en un _estándar_. Es importante notar que el polinomio es un número primo del orden de n^32 y se busca que sea un número primo en específico porque un número no primo es suceptible a errores debido a que nos puede dar 0 el resultado porque podríamos caer en algún múltiplo del polinomio. En el caso específico de _Ethernet_, se usa el polinomio `CRC-32`.
