# Programas de Captura de Paquetes en Java y C

Realmente ambos códigos realizan *exactamente* lo mismo. Sin embargo, las diferencias recaen en los específicos de cada lenguaje como la sintaxis y la funcionalidad orientada, o no, a objetos de las librerías.

## Java

Aquí la verdad no puse mucha atención porque odio Java.

## C

Aquí es interesante ver cómo siempre se requiere liberar la memoria usada por la lista ligada con los dispositivos de captura.

El encabezado es:

<table>
    <tbody>
        <tr>
            <td>MAC Destino</td>
            <td>MAC Origen</td>
            <td>Tipo</td>
            <td>Datos</td>
            <td>CRC</td>
        </tr>
        <tr>
            <td>6 bytes</td>
            <td>6 bytes</td>
            <td>2 bytes</td>
            <td>46 - 1500 bytes</td>
        </tr>
    </tbody>
</table>

Todo esto en la capa 2.