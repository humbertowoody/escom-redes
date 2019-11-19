# Clasificación de Redes de Computadoras

No todas las redes de computadoras son iguales, existen múltiples características para clasificarlas, y todas son distintas. Por eso es importante que sepamos cómo se clasifican.

## Por su Área de Cobertura

- Redes de Área Personal (PAN).
  - Unos cuantos metros.
  - Kbps -> Mbps.
- Redes de Área Local (LAN).
  - De 100m a 1000m.
  - Mbps -> Gbps.
- Redes de Área de Campus (CAN).
  - Conjuntar muchas redes LAN.
  - 5km^2 .
- Redes de Área Metropolitana (MAN).
  - Microondas.
- Redes de Área Amplia (WAN).
  - Satélite.
  - Fibra Óptica.

## Por su Relación funcional

- Cliente Servidor.
- P2P.

## Por su Topología

Topología física: Cómo están conectados los cables de red.

Topología lógica: Cómo funcionan los protocolos de red.

- Bus.
  - Muy poco fiable porque es suceptible a las colisión de tramas. 
- Anillo.
  - Token Ring.
  - Master/Slave.
  - El maestro envía una trama llamada *Token* y ese token se va transmitiendo de puerto en puerto.
  - Si tiene que transmitir genera una trama con los datos y la envía con el token.
  - Si no tiene nada que transmitir genera una trama vacía y la envía.
  - Si recibe datos, toma los datos del token y genera una trama vacía y la reenvía. 
- Estrella.
  - Switches. Trabajan en la capa de enlace de datos. Interpretan las ráfagas de bits, estructurarlos en tramas y los envían a la MAC Destino. Analiza y guarda en la tabla de enrutamiento las computadoras conectadas a sus puertos puede hacer labores de capa 3. 
  - Se llama *Estrella* porque todas las comunicaciones pasan por el centro.
- Árbol.
  - Es una extensión de la topología de *Estrella*.
  - Muchos switches interconectados. 
- Malla.
  - Redes inalámbricas.
  - *Mesh Network*.
  - Hash table para validar qué mensajes tiene cada participante de la red con checksums.
  - Muy robusto. 