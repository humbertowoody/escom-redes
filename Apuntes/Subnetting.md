# Subnetting (Subredes)

> Implica tomar bits prestados del espacio de direccionamiento de host para crear un nuevo nivel de direccionamiento lógico.

## Ejemplo

Dada la red 192.168.0.0/24, desarrolle un direccionamiento que cumpla los siguientes requisitos:

- Una subred de 20 hosts para ser asignada a la VLAN de Profesores.
- Una subred de 80 hosts para ser asignada a la VLAN de Estudiantes.
- Una subred de 20 hosts para ser asignada a la VLAN de Invitados.
- 3 subredes con 2 hosts cada una para ser asignadas a los enlaces entre los enrutadores.

|   Subred    | ID con longitud de prefijo |     Máscara     |          Rango Útil           |   Broadcast   |    # Hosts    |
| :---------: | :------------------------: | :-------------: | :---------------------------: | :-----------: | :-----------: |
| Estudiantes |       192.168.0.0/25       | 255.255.255.128 |  192.168.0.1 - 192.168.0.126  | 192.168.0.127 | (2^7)-2 = 126 |
| Profesores  |      192.168.0.128/27      | 255.255.255.224 | 192.168.0.129 - 192.168.0.158 | 192.168.0.159 | (2^5)-2 = 30  |
|  Invitados  |      192.168.0.160/27      | 255.255.255.224 | 192.168.0.161 - 192.168.0.190 | 192.168.0.191 | (2^5)-2 = 30  |
|  Enlace 1   |      192.168.0.192/30      | 255.255.255.252 | 192.168.0.193 - 192.168.0.194 | 192.168.0.195 |  (2^2)-2 = 2  |
|  Enlace 2   |      192.168.0.196/30      | 255.255.255.252 | 192.168.0.197 - 192.168.0.198 | 192.168.0.199 |  (2^2)-2 = 2  |
|  Enlace 3   |      192.168.0.200/30      | 255.255.255.252 | 192.168.0.201 - 192.168.0.202 | 192.168.0.203 |  (2^2)-2 = 2  |

Para realizar el cálculo, lo que tenemos que hacer, a modo receta de cocina, es ir tomando cada subred (_subnet_) y, tomando la red dada, hacemos el cálculo para cada una.

Comenzamos con _Estudiantes_, con lo que el id de red **no deberá ser modificado** (192.168.0), el cual lo hemos definido realizando una suma del número de hosts que vamos a necesitar, en este caso 80, sin embargo, el número más cercano en binario es 128 (dejando espacio libre es mejor a que falte espacio), que es 2^7. De aquí, lo que hacemos es calcular la longitud de prefijo, para ello tomamos la longitud base (32) y le restamos el número de bits que usaremos para el _ID de Host_, es decir, para los 128 equipos que conectaremos en la red, y obtendremos un resultado de **25**, por lo que nuestro ID de Red, con longitud de prefijo, es: 192.168.0.0/25. Para calcular la máscara, colocamos en 1's nuestro _ID de Red_ (192.168.0) y le colocamos en 0's el número de bits que usamos para el _ID de Host_ (7 [que se convierten en 128 hosts]) por lo que obtenemos, en decimal, 255.255.255.128. El _Rango Útil_ lo calculamos quitando la primera dirección (puerta de enlace) y la última (broadcast), por lo que tendremos un Rango Útil para la subred desde 192.168.0.1 hasta 192.168.0.126. El _Broadcast_, como ya mencionamos, será la dirección 192.168.0.127. Finalmente, el número de hosts, será de (2^7)-2, le restamos dos por la puerta de enlace y el broadcast, teniendo como resultado el 126. Aunque nos hayan especificado 80, es mejor dejar espacio de sobra por cualquier cosa. Para esta subred, tendremos el siguiente esquema:

| ID de Red | ID de Subred | ID de Hosts |              Descripción              |
| :-------: | :----------: | :---------: | :-----------------------------------: |
| 192.168.0 |   (1 bit)    |  (7 bits)   |          Disposición de Bits          |
| 192.168.0 |      0       |   0000000   | Dirección más baja (Puerta de Enlace) |
| 192.168.0 |      0       |   1111111   |    Dirección más alta (Broadcast)     |

**Nota**: Configuramos el _ID de Subred_ en 0 y no en 1 para una mejor organización y que las subredes nunca se lleguen a encimar.

Continuando con el análisis, en _Profesores_ se nos piden 20 hosts, por lo que comenzaremos calculando el número más cercano, en binario, a 20, el cual es el 30, es decir, 5 bits. Para calcular la longitud de prefijo restamos `32-5` y tendremos un resultado de 27. Ahora, para definir la dirección inicial, tomaremos **la siguiente dirección inmediata del rango anterior**, es decir, la 192.168.0.128 y realizaremos el análisis correspondiente. Tomando en consideración
