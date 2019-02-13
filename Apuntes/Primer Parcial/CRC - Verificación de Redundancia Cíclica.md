# CRC - Verificación de Redundancia Cíclica

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
