# Control de Flujo

Es la función que permite a un receptor lento o con pocos recursos frenar a un transmisor para evitar ser saturado con datos qeu aún no puede procesar. Existen dos estrategias:

- Parar y esperar: El transmisor solo puede tener una trama en tránsito (antes de enviar la siguiente trama debe recibir el acuse de la trama transmitida)
- Ventana deslizante: El transmisor puede enviar hasta `k` tramas (`k`= tamaño máximo de ventana) sin haber recibido un acuse.

## Control de Error en Parar y Esperar

El ruido, la interferencia, distorisión y demás fenómenos, pueden afectar la señal de datos, causando que la información no sea entregada.

Ej. Una trama se pierde:

- Tiempo de Trama (`ttrama`): Tiempo que le toma al transmisor sacar toda la trama al medio de transmisión.
- Tiempo de Propagación (`tprop`): Tiempo que le toma a la onda electromagnética viajar desde el transmisor hasta el receptor.
- Tiempo de Procesamiento (`tproc`): Es el tiempo entre la recepción de una trama y el inicio de la transmisión de una respuesta.
- Tiempo de Acuse (`tack`): Tiempo de Trama para una trama de acuse.