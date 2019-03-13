# IEEE 802.3 - LLC

El estándar de la IEEE 802.3 que incluye LLC, hereda del antiguo HDLC, el cual permite establecer el control de flujo de los datos durante un periodo de transmisión. Su origen se remonta a HDLC, y no fue hasta el estándar de la IEEE 802.3, donde se especificó su implementación y sus posteriores mejoras únicamente han sido mediante la adición de campos de control así como delimitación de espacios de operación.

## Estructura de tramas

La estructura del encabezado de LLC es:

|MAC Destino|MAC Origen|DSAP|SSAP|LLC Control|Info|FCS|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|6 bytes|6 bytes|1 byte|1 byte|1 byte*| 43 - 1447 bytes|1 byte|

_*Nota: Puede ser de 1 o de 2 bytes dependiendo de la **longitud** que se indique._

El campo de control puede ser de 8 bits o de 16 bits, dependiendo de las necesidades que se tengan para la transmisión de datos. Dichos datos contienen instrucciones.

El campo de control de LLC es un campo importante, dentro de este se encuentra la definición del tipo de trama que se está analizando. Dentro de los tipos, hay tramas de *Información*, *Supervisión* y *Sin Numerar*. Cada una de esas tramas se nombran por lo general `i`, `s` y `u`.

Para realizar este 


### Código de Tramas `u`

|Código|Orden|Respuesta|Explicación|
|:---:|:---:|:---:|:---:|
|00001|SNRM|-|Activación de modo de respuesta normal
|11011|SNRME|-|Activación de modo de respuesta normal extendido
|11000|SARM|DM|Activación de modo de respuesta asíncrona / Modo de desconexión
|11010|SARME|-|Activación de modo de respuesta asíncrona extendida
|11100|SABM|-|Activación de modo de respuesta asíncrona balanceado
|11110|SABME|-|Activación de modo de respuesta asíncrona balanceado extendido
|00000|UI|UI|Información sin numerar
|00110|-|UA|Acuse sin numerar
|00010|DISC|RD|Desconexión  / Petición de desconexión
|11001|RSET|-|Reinicio
|10001|-|FRMR|Rechazo de tramas
|00100|UP||Sondeo sin numerar

### Códigos de Tramas `s`

|Código|Orden|Explicación|
|:---:|:---:|:---:|
|00|RR|Listo para recibir
|01|REJ|Rechazo
|10|RNR|No listo para recibir
|11|SREJ|Rechazo selectivo