# IEEE 802.3 - LLC

El estándar de la IEEE

## Estructura de tramas




## Código de Tramas `u`

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

## Códigos de Tramas `s`

|Código|Orden|Explicación|
|:---:|:---:|:---:|
|00|RR|Listo para recibir
|01|REJ|Rechazo
|10|RNR|No listo para recibir
|11|SREJ|Rechazo selectivo