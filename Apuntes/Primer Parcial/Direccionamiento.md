# Direccionamiento

El **direccionamiento**  es la capacidad con la que cuenta una red de enviar paquetes de forma distribuída y eficiente de forma lógica a través de una red de computadoras o una interred como lo es Internet. Para esto, se analizan a continuación los niveles de direccionamiento, el alcance y los modos de direccionamiento.

## Nivel de Direccionamiento

Comparación entre direccionamiento en el *Modelo OSI* y el *TCP/IP* en cuanto a direccionamiento se refiere:

<table style="text-align: center;">
<tr>
    <td></td>
    <th>OSI</td>
    <th>TCP / IP</td>
    <td></td>
</tr>
<tr>
    <td></td>
    <td>7</td>
    <td rowspan="3">4</td>
    <td rowspan="3"></td>
</tr>
<tr>
    <td></td>
    <td>6</td>
</tr>
<tr>
    <td></td>
    <td>5</td>
</tr>
<tr>
    <td>TSAP</td>
    <td>4</td>
    <td>3</td>
    <td># Puerto</td>
</tr>
<tr>
    <td>NSAP</td>
    <td>3</td>
    <td>2</td>
    <td>Direción IP</td>
</tr>
<tr>
    <td></td>
    <td>2</td>
    <td rowspan="2">1</td>
    <td rowspan="2">Dirección MAC</td>
</tr>
<tr>
    <td></td>
    <td>1</td>
</tr>
</table>

## Alcance de Direccionamiento

El alcance de direccionamiento se refiere a la capacidad que tiene una red de direccionar un paquete a través de múltiples subredes, arquitecturas e infraestructuras. Para esto, se cuentan con dos principios:

- **No ambiguedad global**: Se refiere a que nunca deberá existir más de una sola dirección IP asignada al mismo tiempo en la misma subred. En caso de duplicarse, los paquetes entrarían en una colisión ya que el *Router* no podría determinar hacia cuál dirección *MAC* corresponde cuál paquete.
- **Aplicabilidad global**: Se refiere a la capacidad de direccionamiento de funcionar de forma global sin problemas de direccionamiento.

## Modo de Direccionamiento

### Unidifusión (Unicast)

Este tipo de direcciones IP son las que más usamos. Son las típicas en el uso de 
internet porque permite enrutar los paquetes de forma global. Para esto, se utilizan los *Registros Regionales de Internet* y demás herramientas de Internet.

#### Estructura

La estructura de una dirección de Unicast es la siguiente:

|id red|id host|
|---|---|
|2 bytes|2 bytes|


#### Tipos de direcciones `unicast`

|Clase|Bytes de ID de Red|Bytes de ID de Host|Rango|
|:---:|:---:|:---:|:---:|
|A|1|3|1.0.0.0 - 127.255.255.255
|B|2|2|128.0.0.0 - 191.255.255.255
|C|1|3|192.0.0.0 - 223.255.255.255
|D|*Multicast*|*Multicast*|224.0.0.0 - 239.255.255.255
|E|||240.0.0.0 - 255.255.255.255


### Multidifusión (Multicast)

Es un tipo de dirección IP que permite hablar a un grupo de hosts. Cuando queremos transmitir audio o video y queremos que lleguen a varios.

### Difusión (Broadcast)

Las direcciones de difusión se utilizan para preguntar algo en la red, es decir, cuando queremos conocer algo pero no contamos con la información suficiente acerca de la topología o el diseño de la red podemos enviar una pregunta de *ARP* para conocer el equivalente en `MAC` de alguna `IP`.

Existen 2 tipos de direcciones *broadcast*:

- **Broadcast Dirigido**: Es para todas las máquinas en la subred. Le llega a todos.

- **Broadcast Limitado**: Dirigido a una subred en específico. Llega a una subred en específico.
