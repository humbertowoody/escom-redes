# Control de Flujo

Es la función que permite a un receptor lento o con pocos recursos frenar a un transmisor para evitar ser saturado con datos qeu aún no puede procesar. Existen dos estrategias:

- Parar y esperar: El transmisor solo puede tener una trama en tránsito (antes de enviar la siguiente trama debe recibir el acuse de la trama transmitida)
- Ventana deslizante: El transmisor puede enviar hasta `k` tramas (`k`= tamaño máximo de ventana) sin haber recibido un acuse.


## Parar y Esperar

### Control de Error en Parar y Esperar

El ruido, la interferencia, distorisión y demás fenómenos, pueden afectar la señal de datos, causando que la información no sea entregada.

Ej. Una trama se pierde:

![Imágen de Proceso](https://i.imgur.com/3T1MYf1.jpg)

- Tiempo de Trama (`ttrama`): Tiempo que le toma al transmisor sacar toda la trama al medio de transmisión.
- Tiempo de Propagación (`tprop`): Tiempo que le toma a la onda electromagnética viajar desde el transmisor hasta el receptor.
- Tiempo de Procesamiento (`tproc`): Es el tiempo entre la recepción de una trama y el inicio de la transmisión de una respuesta.
- Tiempo de Acuse (`tack`): Tiempo de Trama para una trama de acuse.

Es importante considerar la velocidad de propagación, que es la velocidad con la que el _medio_ puede transmitir los datos. Esto va a depender del tipo de medio:

Velocidad de Propagación (`Vprop`):

- Medio Guiado: 2x10^8 m/s
- Medio No Guiado: 3x10^18 m/s

Si una trama se pierde, existe un temporizador que es 2 veces la velocidad de propagación del medio el cual es el tiempo que esperamos un acuse de recibo, si no llega tal acuse, se reenvía la trama.

Cuando un acuse de recibo se pierde, lo que se hace es numerar las tramas a nivel de bits, esto quiere decir que se envía la trama 0, y se espera el acuse (`ACK`) 1, de esa forma podemos mandar el acuse de la trama duplicada (porque el emisor la envía dos veces dado qeu no recibió acuse) y frenar la retransmisión.

### Utilización de Canal en Parar y Esperar

`u` = (`tutil`/`t total`) * 100

![Imgur](https://i.imgur.com/q7b1OFV.jpg) 

Por lo que:

`u` = `ttrama`/(`ttrama` + 2`tprop` + 2`tproc` + 2`tack`)

Si consideramos que la tecnología evluciona rápidamente reduciendo el tiempo de procesamiento `tproc` → 0 y si además consideramos que `tack` << `ttrama` por lo tanto `tack` se puede despreciar, entonces:

`u` = `ttrama`/(`ttrama` + 2`tprop` + ~~2`tproc`~~ ~~+ 2 `tack`~~)

`u` = `ttrama`/(`ttrama` + 2`tprop`)

Dividiendo el numerador y el denominador entre `ttrama`:

`u` = (~~`ttrama`/`ttrama`~~)/((~~`ttrama`/`ttrama`~~) + (2`tprop`/`ttrama`))

Si `a` = `tprop`/`ttrama`

Sustituyendo:

|`u` = [1 / ( 1 + 2`a`)] x 100|
|:---:|
