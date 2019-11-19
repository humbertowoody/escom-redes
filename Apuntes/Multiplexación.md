# Multiplexación

La multiplexación permite que por una misma tarjeta de red puedan viajar datos de múltiples aplicaciones. Esto es dado que se emplean *puertos*, los cuales nos permiten asignar un identificador único a cada aplicación que haga uso de los recursos de red del host.

Al ser 2 bytes el tamaño del *puerto*, el número máximo de aplicaciones simultáneas disponible es de: **65,535** (2^16).

Cada tipo de servicio, ya sea *orientado a conexión* (**TCP**) o *no orientado a conexión* (**UDP**) cuenta con el número de puertos descrito anteriormente, así que en total, combinado, tenemos:

```txt
  65536 *orientado a conexión*
+ 65546 *no orientado a conexión*
--------
 131072 | Aplicaciones simultáneas.
```


## En TCP


Diagrama de encabezado para multiplexación en TCP:

<table  style="text-align: center; table-layout: fixed;">
    <thead>
        <tr>
            <th>1</th>
            <th>2</th>
            <th>3</th>
            <th>4</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td colspan="2">Puerto Origen</td>
            <td colspan="2">Puerto Destino</td>
        </tr>
        <tr>
            <td colspan="4"># secuencia</td>
        </tr>
        <tr>
            <td colspan="4"># ACK</td>
        </tr>
        <tr>
            <td>IHL</td>
            <td>0's y Bits de Control</td>
            <td colspan="2">Ventana</td>
        </tr>
        <tr>
            <td colspan="2">Checksum</td>
            <td colspan="2">Apuntador Urgente</td>
        </tr>
    </tbody>
</table>


## En UDP

Diagrama de encabezado para multiplexación en UDP:

<table  style="text-align: center; table-layout: fixed;">
    <thead>
        <tr>
            <th>1</th>
            <th>2</th>
            <th>3</th>
            <th>4</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td colspan="2">Puerto Origen</td>
            <td colspan="2">Puerto Destino</td>
        <tr>
            <td colspan="2">Longitud</td>
            <td colspan="2">Checksum</td>
        </tr>
    </tbody>
</table>