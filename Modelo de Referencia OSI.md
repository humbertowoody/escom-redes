# Modelo de Referencia OSI

Fue desarrollado por la Organización Internacional por la Estandarización (ISO) y obtuvo el grado de estándar internacional en 1983.

Pretende que los sistemas desarrollados con base en él se comuniquen de manera transparente.

Agrupa la funcionalidad de comunicación en 7 diferentes capas:

1. **Capa Física**: Se encarga de la transmisión de cadenas de bits no estructurados sobre el modelo físico, así como voltajes empleados, definición de cada símbolo, número de terminales en cada concentrador 
2. **Capa de enlace de datos**: Se encarga de la corrección de errores y garantiza que los datos lleguen bien.
3. **Capa de Red**: Brinda las funcionas de direccionamiento lógico y enrutamiento.
4. **Capa de Transporte**: Proporciona direccionamiento en parte de servicio, transferencia transparente de datos, control de error y flujo extremo a extremo.
5. **Capa de Sesión**: Establece, gestiona y cierra las conexiones (sesiones) entre las aplicaciones involucradas.
6. **Capa de Presentación**: Proporciona independencia respecto a las diferencias en la representación de los datos (sintaxis).
7. **Capa de Aplicación**: En esta capa residen las aplicaciones de so general como transferencia de archivos, correo electrónico y terminales remotas.

## Representación Gráfica

Las capas se agrupan una encima de otra, y cada una ofrece servicios a la capa superior y consume los servicios de la capa inferior.

|Modelo OSI|
|:---:|
|Capa de Aplicación|
|Capa de Presentación|
|Capa de Sesión|
|Capa de Transporte|
|Capa de Red|
|Capa de Enlace de Datos|
|Capa Física|

## Funciones que deben desempeñar todas las redes

- *Encapsulamiento*. Quiere decir que cada capa le añade un *header* para que se pueda interpretar en el cliente.
- *Control de error*.
  - CRC (Chequeo de Redundancia Cíclica).
  - Checksum.
  - Manning.
  - Bit de paridad. 
- *Entrega en orden.*
- *Control de flujo*.
- *Segmentación y ensamblado*.
- *Direccionamiento*.
- *Multiplexación*.
- *Servicios de transmisión*.
- *Control de conexión*.