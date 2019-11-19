# Ventana Deslizante

En ventana deslizante se le permite al transmisor enviar hasta `k` tramas (`k` es el **tamaño máximo de ventana**) sin haber recibido un acuse (`ACK`). La finalidad es conseguir una mayor utilización cuando `Tprop >> Ttrama`.

## Implementación

Para implementar *Ventana Deslizante*, se deben contar con 2 *buffers* y 4 *apuntadores*:

- `a1`: Apuntador en el transmisor; indica el inicio de ventana. Se desplaza cerrando la ventan cada que se transmite una trama.
- `a2`: Apuntador en el transmisor; indica el fin de ventana. Se desplaza abriendo la ventana cada que se recibe un acuse en secuencia.
- `b1`: Apuntador en el receptor; indica el inicio de ventana. Se desplaza cerrando la ventana cada que se recibe una trama.
- `b2`: Apuntador en el receptor; indica el fin de ventana. Se desplaza la ventana cada que se envía un acuse.

El objetivo final es que las tramas en el transmisor y el receptor **sean iguales**.

## Control de Error

Para el control del error, se cuentan únicamente con 2 opciones:

1. **Retroceder M**: En este esquema el receptor no tiene permitido recibir tramas fuera de secuencia. Aquí, las tramas que se envíen posterior al `ACK` con el número de secuencia de la trama que **no** se recibió, serán descartadas.
2. **Rechazo Selectivo**: En este esquema el receptor puede recibir tramas fuera de secuencia. Aquí únicamente se requiere la retransmisión de la trama para la que se envía el `ACK` con el número de secuencia de la trama **no recibida**.