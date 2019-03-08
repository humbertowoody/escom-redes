# Servicios de Transmisión

Antes se llamaba *Type of Service*, pero actualmente el campo se llama *Servicios  Diferenciados*, y se ubica en:

![Encabezado de IP](http://telescript.denayer.wenk.be/~hcr/cn/idoceo/images/ip_header.gif)

## Bits *Type of Service*

Así era como estaba conformado el campo *Type of Service* en las versiones antiguas del protocolo **IP**:

- 0-2: Precedencia.
  - 0: Normal
  - 1: Mínimo 
- 3: Desempeño.
  - 0: Normal
  - 1: Máximo
- 4: Confiabilidad.
  - 0: Normal
  - 1: Máximo
- 6-7: Sin uso.

## Bits Servicios Diferenciados

Actualmente el campo se llama *Servicios Diferenciados*. El esquema a nivel de bits es el siguiente:

|x|x|x|0|0|0|ECN 1| ECN 2
|---|---|---|---|---|---|---|---|


Significado de los bits de control:

|xxx|Significado|Uso
|---|---|---|
|111|Control de Red|Tráfico de Control
|110|Control de Internet|(ej. enrutamiento)
|101|Critic/Eco|Voz
|100|Flash Override|Streaming
|000|Rutina|Default
|001|Prioridad|Libre para clasificar tráfico de datos

## Notificación de Congestionamiento Explícita (ECN)

Este campo nos permite informar a la red del estado del enrutador para permitir un mejor flujo de paquetes dentro de la red.

|ECN|Significado
|:---:|:---:|
|00|Sin capacidad ECN
|01|Capacidad ECN (1)
|10|Capacidad ECN (0)
|11|Congestión Encontrada
