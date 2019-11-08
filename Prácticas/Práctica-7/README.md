# Práctica 7

**Nombre:** Humberto Alejandro Ortega Alcocer

**Número de Boleta:** 20166304495

**Fecha:** 10/10/2019

## Tabla de Contenidos

- [Práctica 7](#pr%c3%a1ctica-7)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Introducción](#introducci%c3%b3n)
  - [Desarrollo](#desarrollo)
    - [Configuración Física](#configuraci%c3%b3n-f%c3%adsica)
      - [Colocación de Equipos](#colocaci%c3%b3n-de-equipos)
      - [Configuración de Routers](#configuraci%c3%b3n-de-routers)
    - [Configuracion Lógica](#configuracion-l%c3%b3gica)
      - [Equipo Cliente (PC)](#equipo-cliente-pc)
      - [Switch](#switch)
      - [Router](#router)
        - [Interfaces](#interfaces)
        - [Ruteo Estático](#ruteo-est%c3%a1tico)
  - [Prueba](#prueba)
  - [Posibles Mejoras](#posibles-mejoras)
  - [Conclusiones](#conclusiones)
  - [Fuentes](#fuentes)

## Introducción

Esta práctica tiene como objetivo ser una introducción a Cisco Packet Tracer y todas las herramientas que nos ofrece al ser un entorno integrado de aprendizaje para redes de computadoras. El software es gratuito desde la [página de descarga oficial][pt-link] y puede instalarse de forma nativa en Windows, MacOS y Linux.

Una vez instalado, nos pedirá iniciar sesión con una cuenta de NetAcademy de Cisco, aquí podemos registrarnos y nos creará un perfil en NetAcademy que posteriormente podremos usar para los laboratorios necesarios para certificaciones como el CCNA, aunque también podemos optar por no registrarnos y usar el "Guest Mode" con el cual tendremos un número limitado de dispositivos que podemos tener en nuestra topología.

> En caso de usar MacOS, después de la instalación debemos asegurarnos de que le demos permiso a Cisco Packet Tracer de tener "Acceso total al disco", configuración que podemos establecer en Preferencias de Sistema -> Seguridad y Accesibilidad -> Acceso Total al Disco y añadir Cisco Packet Tracer a la lista de softwares permitidos. De otra forma *Packet Tracer crasheará y alentará de forma infinita*.

## Desarrollo

Inicialmente la topología cuenta con 6 segmentos de red:

- 10.0.0.0/8
- 20.0.0.0/8
- 30.0.0.0/8
- 40.0.0.0/8
- 50.0.0.0/8
- 60.0.0.0/8

Esto nos indica que todos los segmentos de red usarán la misma máscara de subred `255.0.0.0`.

La topología es la siguiente:

![Topología de la Práctica ya implementado en Cisco Packet Tracer][topology-img]

Destacan varios detalles:

- Existe una conexión serial entre `Router0` y `Router1`, por lo que deberemos configurar apropiadamente las interfaces entre ambos routers y, en el caso de `Router1` seleccionar el `clock rate` al que operará la conexión (64000 bps es suficiente para fines de esta práctica).
- En el segmento de `50.0.0.0/8` tenemos 2 routers interconectados por un switch intermediario que a su ves cuenta con 3 equipos conectados al mismo. La forma de hacer el ruteo es configurando `Router1` con la IP `50.0.0.2` y `Router2` con la IP `50.0.0.1` y que `Router1` sea la puerta de enlace predeterminada.
- Los equipos tienen por nombre la IP que fue asignada sólamente para fines ilustrativos.

Ahora para realizar la interconexión de los dispositivos deberemos realizar dos tipos de configuraciones: **configuración física** y **configuración lógica**.

### Configuración Física

La configuración física se refiere a la parte de cablear los equipos que participan dentro de la red y la colocación de los mismos acorde a la topología proporcionada.

#### Colocación de Equipos

Inicialmente, colocaremos los equipos con los que vamos a trabajar para esta práctica. Los equipos son:

- 3 routers 2811.
- 5 switches 2950T.
- 15 computadoras de escritorio (3 por cada switch).

#### Configuración de Routers

Los routers, en su configuración inicial, proporcionan 2 puertos de tipo *FastEthernet*, los cuales, aunque son suficientes en la mayoría de los casos, no satisfacen nuestros requerimientos para la topología planteada. Es por ello que deberemos añadir a `Router0` y `Router1` una tarjeta de comunicación serial a cada uno.

Instalar la tarjeta se realiza mediante los siguientes pasos:

1. Doble click en el router que querramos configurar.
2. Seleccionar "Vista Física".
3. Apagar el Router haciendo click en el interruptor en la esquina inferior derecha del equipo.
4. Arrastrar y soltar la tarjeta de comunicación serial *WIC-2T* desde el panel izquierdo hasta uno de los espacios disponibles en el Router. De preferencia, comenzar con el panel inferior izquierdo y añadir tarjetas en orden contrario a las manecillas del reloj.
5. Finalmente, encender el router de nuevo.

El `Router2` no requiere de esta tarjeta ya que su ubicación dentro de la topología nos indica que será cableado únicamente a 2 cables de par trenzado y, al contar con 2 interfaces *FastEthernet* no es necesario añadir ninguna tarjeta.

### Configuracion Lógica

Para la configuración lógica de los dispositivos, es necesario tomar múltiples pasos que difieren de un dispositivo a otro. A continuación describo los pasos que deben tomarse para cada dispositivo.

#### Equipo Cliente (PC)

Para los equipos clientes deberemos configurar:

- Dirección IP: La colocaremos dependiendo del segmento en el que se encuentre nuestro dispositivo. Por ejemplo, si nuestro equipo se encuentra en el segmento `10.0.0.0/8`, podremos elegir una IP dentro del segmento (10.0.0.1 - 10.255.255.255), pero despreciando la dirección de broadcast (10.255.255.255) y la dirección del router del segmento (10.0.0.1, la dirección que yo elegí), por lo que podríamos, por ejemplo, usar la `10.0.0.2`.
- Máscara de Subred: La máscara de subred es la misma para toda la topología: `/8`, es decir, `255.0.0.0`.
- Puerta de Enlace: Aquí colocaremos la dirección IP del Router que hayamos definido para dicho segmento de red.
- Nombre de equipo (Opcional): Es buena práctica colocar inidicadores de los equipos en Packet Tracer con el fin de que sea más sencillo poder identificar y realizar análsis de los errores que sucedan dentro de la red.

#### Switch

Los swtich, al ser capa 2, no requieren configuración adicional.

> Nota: Algunos switches disponibles en Packet Tracer son de capas superiores y por ende permiten realizar configuraciones de Ruteo Estático. Esas opciones quedan fuera del alcance de la práctica pero los comandos son muy parecidos a los de un Router Cisco.

#### Router

Para los router, es requerido configurar más cosas:

- Asignar IP a cada interfaz.
- Asignar rutas estáticas.

##### Interfaces

Para configurar las interfaces, deberemos seguir los siguientes pasos:

1. Introducir el comando: `enable`.
2. Introducir el comando `configure terminal`.
3. Introducir el comando `interface [interfaz]`. Donde `interfaz` es el indicador de la interfaz de red que queremos configurar, por ejemplo, `interface fa0/1` para configurar la segunda interfaz de red de tipo *FastEthernet*.
4. Introducir el comando `ip address [IP] [Máscara]`, con lo cual colocaremos la IP y la Mácara de Subred para dicha interfaz.
5. Finalmente escribimos `exit`.
6. Si se requiere configurar más tarjetas, podemos volver al paso 2. De otra forma, usaremos `^z` (`Ctrl` + `Z`) y después escribiremos `wr` para que la configuración se persista en la memoria del router.

##### Ruteo Estático

Para configurar el ruteo estático es necesario que visualicemos en la topología los segmentos de red y cómo se están comunicando entre sí. Los segmentos de red conectados directamente al router ya son conocidos en la perspectiva de ese router, pero cualquier otro segmento que salga de sus conexiones, deberemos indicarle cuál es el siguiente salto y cuál debe ser la prioridad de ese salto (en este caso, es estático). Para realizar dicha configuración:

1. Introducir el comando: `enable`.
2. Introducir el comando `configure terminal`.
3. Introducir el comando `ip route [IP] [Máscara] [IP del siguiente salto] 1`. Siendo la `IP` y la `Máscara` la IP y la Máscara de Subred del segmento al que no se tiene acceso directamente y requiere ser enviado a otro router dónde se pueda determinar por dónde encaminar el paquete siendo `IP del siguiente salto` la IP de dicho Router. Por ejemplo, para configurar la ruta desde el segmento `10.0.0.0/8` hasta el segmento `40.0.0.0/8` (desde la perspectiva de `Router0`) deberemos usar: `ip route 40.0.0.0 255.0.0.0 30.0.0.2`, esto porque la IP del siguiente salto (en perspectiva de `Router0`), `Router1`, es la `30.0.0.2` puesto que `Router0` es `30.0.0.1`.
4. Finalmente ejecutaremos `show ip route` para que nos muestre la lista de rutas estáticas definidas para ese router.

## Prueba

Para probar que funciona, haremos pings desde y hacia cada segmento de red disponible. Para esto, anexo una captura de pantalla con las pruebas realizadas que muestran que existe conectividad de extremo a extremo:

![Resultados de pruebas de la red][results-img]

El archivo `practica-7.pkt` es un archivo de Cisco Packet Tracer v7.2, el cual puede abrirse y ejecutarse para corroborar los resultados.

> Es importante saber que a mayor complejidad en nuestra red, tanto a nivel topológico como de configuración, hará que el programa se alente. Por ello, si se presenta algún problema durante las pruebas. Cambiar de modo "En tiempo real" a "Simulación" nos permite evitar la simulación total de la red en todo momento.

## Posibles Mejoras

La conexión serial es eficiente pero podría sustituirse por una de mayor capacidad como un _par trenzado cruzado_.

## Conclusiones

Cisco Packet Tracer es una de las herramientas más avanzadas (y divertidas) para aprender los conceptos fundamentales (y otros no tanto) de redes de computadoras.

## Fuentes

- Material visto en clase.

[pt-link]: https://www.netacad.com/es/courses/packet-tracer
[topology-img]: https://i.imgur.com/dLSURzQ.png
[results-img]: https://i.imgur.com/0WlWTEx.png
