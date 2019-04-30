# Práctica 5 - Ruteo Estático

**Nombre:** Humberto Alejandro Ortega Alcocer

**Número de Boleta:** 20166304495

**Fecha:** 16/04/2019

## Tabla de Contenidos

- [Práctica 5 - Ruteo Estático](#pr%C3%A1ctica-5%-%Ruteo%Est%C3%A1tico)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Introducción](#introducci%C3%B3n)
  - [Desarrollo](#desarrollo)
  - [Prueba](#prueba)
  - [Posibles Mejoras](#posibles-mejoras)
  - [Conclusiones](#conclusiones)
  - [Fuentes](#fuentes)

## Introducción

Para realizar una introducción al software de simulación de redes *Cisco Packet Tracer*, la presente práctica pretende replicar la configuración vista en clase de una red para Estudiantes, Profesores e Invitados con ruteo estático. La arquitectura de la red deberá quedar de la siguiente forma:

|   Subred    | ID con longitud de prefijo |     Máscara     |          Rango Útil           |   Broadcast   |
| :---------: | :------------------------: | :-------------: | :---------------------------: | :-----------: | :-----------: |
| Estudiantes |       192.168.0.0/25       | 255.255.255.128 |  192.168.0.1 - 192.168.0.126  | 192.168.0.127 |
| Profesores  |      192.168.0.128/27      | 255.255.255.224 | 192.168.0.129 - 192.168.0.158 | 192.168.0.159 |
|  Invitados  |      192.168.0.160/27      | 255.255.255.224 | 192.168.0.161 - 192.168.0.190 | 192.168.0.191 |
|  Enlace 1   |      192.168.0.192/30      | 255.255.255.252 | 192.168.0.193 - 192.168.0.194 | 192.168.0.195 |
|  Enlace 2   |      192.168.0.196/30      | 255.255.255.252 | 192.168.0.197 - 192.168.0.198 | 192.168.0.199 |
|  Enlace 3   |      192.168.0.200/30      | 255.255.255.252 | 192.168.0.201 - 192.168.0.202 | 192.168.0.203 |

Y deberá contemplar la interconexión de dispositivos, así como los siguientes objectivos específicos:

- Instalar y configurar **Routers**.
- Instalar y configurar **Switches**.
- Configurar **Tabla de Ruteo**.
- Instalar y configurar **Clientes**.

Teniendo como resultado una topología de red de la siguiente forma:

![Topología de la red](https://i.imgur.com/Py6gA24.jpg)

## Desarrollo

Para comenzar, deberemos tener instalado el software **Cisco Packet Tracer**, en caso de no contar con el mismo, lo podremos descargar de la página oficial de [Cisco Networking Academy][packet-tracer-url] en la cual tendremos que registrarnos y, posteriormente, podremos descargar la última versión tanto para Mac, Windows o Linux.

### Configuración Física

Comenzaremos realizando el cableado requerido y la colocación de los equipos físicos que necesitamos para la topología planteada.


#### Inicio

Comenzaremos cambiando la vista al modo *Lógico*, y de ahí partiremos a añadir nuestros elementos de red. Por motivos de la práctica, añadiremos los siguientes dispositivos:

- 3 routers 2811.
- 3 switches 2950T.
- 2 computadoras de escritorio **para cada** subred, es decir, 6 en total.

#### Configuración de Routers

Para configurar los Routers, primero tomaremos en consideración el hardware proporcionado por default para cada uno de ellos. En general, cuentan con 2 puertos *FastEthernet* los cuales, aunque pudiera asumirse que serán los únicos, **no serán suficientes** considerando que requerimos realmente **3** puertos para interconectar cada Router de forma física:

- El puerto que va del Router A al Router B.
- El puerto que va del Router A al Router C.
- El puerto que va del Router A al Switch de su subred.

Dadas esas consideraciones, lo que haremos será añadir una tarjeta de red de tipo *serial*, la cual nos servirá para interconectar los routers entre sí reservando el puerto *FastEthernet* para la conexión con el switch.

##### Instalación de la tarjeta de comunicación Serial

Para instalar la tarjeta de comunicación Serial, **Cisco Packet Tracer** cuenta con una Interfaz Gráfica de Usuario muy poderosa que nos permite visualizar los equipos e interactuar con ellos de una forma *muy similar* a la que tendríamos trabajando con los equipos de forma física. Por ello, es necesario llevar a cabo pasos y procesos que tendríamos que seguir como si estuviéramos frente a frente con cada uno de los dispositivos que dispongamos en nuestra topología de red.

Incluyendo las mencionadas consideraciones, el proceso, para añdir una tarjeta de comunicación serial a **cada uno de los routers** es de:

1. Apagar el Router en cuestión.
2. Arrastrar y soltar la tarjeta de comunicación serial *WIC-2T* desde el panel izquierdo hasta uno de los espacios disponibles en el Router.
3. Encender el Router de nuevo.

Si nosotros intentáramos añadir la tarjeta **sin** haber apagado el Router, el software nos arrojará un error dado que en un ambiente real no es posible instalar una nueva tarjeta sobre un equipo en funcionamiento.

#### Cableado

Para el cableado, debemos tomar en consideración que contamos con dos tipos de interfaces en nuestra topología de internet, aquellas que funcionan con *Comunicación Serial* para la interconexión de Routers, y aquellas otras que funcionan sobre *Ethernet* para la interconexión con Switches, Hosts y Routers. Es por ello, que deberemos de emplear 2 tipos de cableado: Serial y Par Trenzado.

Para la comunicación Serial, usaremos el tipo de cable *Serial DCE*, dado que nuestra comunicación será temporizada. Y para la comunicación de tipo Ethernet, usamos un cable de red de tipo *Par Trenzado* que nos permitirá enlazar los equipos al ser de diferentes capas de la pila de protocolos TCP/IP.

Finalmente tendremos una topología que deberá l

### Configuración Lógica

Para realizar la configuración lógica, aunque es posible realizarla mediante los distintos *GUI*s que nos proporciona el software, usaremos el CLI (Interfaz de Línea de Comandos por sus siglas en inglés) el cual será el que usaremos en realidad con los equipos físicos.

Para realizar dicha configuración comenzaremos cambiando

## Prueba

Para realizar la prueba de que nuestra topología de red es funcional, probaremos realizando un `ping` desde los equipos hacia otros en distintas subredes y validaremos los resultados.

## Posibles Mejoras

Para mejorar el rendimiento general de la red, se debería implementar un protocolo de ruteo que nos permita adaptarnos a los cambios que sucedan dentro de la red sin requerir una configuración manual, claro que es a propósito el uso de ruteo estático para demostrar el funcionamiento, sin embargo esta sería una de las mejoras más notables que se podrían realizar al proyecto.

## Conclusiones



## Fuentes

- Material visto en clase.
- [SDLC, HDLC and LLC, LAPB - Data Network Resource](http://www.rhyshaden.com/hdlc.htm)
- [High-Level Data Link Control - Wikipedia, la enciclopedia libre](https://es.wikipedia.org/wiki/High-Level_Data_Link_Control)
- [Logical link control - Wikipedia](https://en.wikipedia.org/wiki/Logical_link_control)
- [TEMA 3. La capa de enlace de datos - Universidad Complutense de Madrid](https://www.fdi.ucm.es/profesor/rubensm/Redes/Trasparencias/Tema%203.pdf)

[packet-tracer-url]: https://www.netacad.com/es/courses/packet-tracer
