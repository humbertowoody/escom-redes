# Modelo de Referencia OSI

Fue desarrollado por la Organización Internacional por la Estandarización (ISO) y obtuvo el grado de estándar internacional en 1983.

Pretende que los sistemas desarrollados con base en él se comuniquen de manera transparente.

Agrupa la funcionalidad de comunicación en 7 diferentes capas:

1. **Capa Física**: Se encarga de la transmisión de cadenas de bits no estructurados sobre el modelo físico, así como voltajes empleados, definición de cada símbolo, número de terminales en cada concentrador 
2. **Capa de enlace de datos**: Se encarga de la corrección de errores y garantiza que los datos lleguen bien.
3. **Capa de Red**: Brinda las funcionas de direccionamiento lógico y enrutamiento.
4. **Capa de Transporte**: Proporciona direccionamiento en parte de servicio, transferencia transparente de datos, control de error y flujo extremo a extremo.
5. **Capa de Sesión**: Establece, gestiona y cierra las conexiones (sesiones) entre las aplicaciones involucradas.
6. **Capa de Presentación**: Proporciona independencia respecto a las diferencias en la representación de los datos (sintaxis).
7. **Capa de Aplicación**: En esta capa residen las aplicaciones de so general como transferencia de archivos, correo electrónico y terminales remotas.

## Representación Gráfica

Las capas se agrupan una encima de otra, y cada una ofrece servicios a la capa superior y consume los servicios de la capa inferior.

|Modelo OSI|
|:---:|
|Capa de Aplicación|
|Capa de Presentación|
|Capa de Sesión|
|Capa de Transporte|
|Capa de Red|
|Capa de Enlace de Datos|
|Capa Física|

## Funciones que deben desempeñar todas las redes

- *Encapsulamiento*. Quiere decir que cada capa le añade un *header* para que se pueda interpretar en el cliente.
- *Control de error*.
  - CRC (Chequeo de Redundancia Cíclica).
  - Checksum.
  - Manning.
  - Bit de paridad. 
- *Entrega en orden.*
- *Control de flujo*.
- *Segmentación y ensamblado*.
- *Direccionamiento*.
- *Multiplexación*.
- *Servicios de transmisión*.
- *Control de conexión*.

### Algoritmos de Control de Error

#### CRC

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