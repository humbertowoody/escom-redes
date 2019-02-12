# WHOIS [www.ipn.mx][webIPN]

Durante la clase, el profesor nos habló acerca de los *dueños* o las personas (físicas o morales) que son realmente los "propietarios" de algún dominio en internet. Para conocer información acerca del *dueño* de algún dominio, podemos consultar su registro de **WHOIS**.

## ¿Qué es WHOIS?

**WHOIS** es un protocolo TCP basado en petición/respuesta que se utiliza para efectuar consultas en una base de datos que permite determinar el propietario de un nombre de dominio o una dirección IP en Internet. Las consultas WHOIS se han realizado tradicionalmente usando una interfaz de línea de comandos, pero actualmente existen multitud de páginas web que permiten realizar estas consultas

### Cómo ejecutarlo

Para ejecutarlo, basta con invocar el comando `whois` (disponible en todas las distribuciones Linux, MacOS y en Sistemas Operativos Windows) y añadir la *URL* del **dominio** que querramos consultar. Por ejemplo:

`$ whois www.google.com`

El cuál nos regresará la información del dominio en cuestión con campos obligatorios y algunos opcionales. Estos campos los llena el *Registrar* de dominios y en muchas ocasiones, a usuarios que así lo deseen, se pueden ofrecer **protecciones de seguridad** con el objetivo de cuidar la privacidad de los dueños del dominio.

## Dominio del IPN

El Instituto Politécnico Nacional se encuentra bajo el dominio de internet [ipn.mx][webIPN], bajo el cual podemos encontrar información, servicios y accesos a múltiples escuelas y unidades que pertenecen al instituto. Es el dominio principal bajo el que se encuentran alineados la mayoría de los demás recursos web pertenecientes al instituto.

### Resultados de WHOIS

Los resultados de ejecutar WhoIs a la página del Instituto Politécnico Nacional son los siguientes:

```txt
% IANA WHOIS server
% for more information on IANA, visit http://www.iana.org
% This query returned 1 object

refer:        whois.mx

domain:       MX

organisation: NIC-Mexico
organisation: ITESM - Campus Monterrey
address:      Av. Eugenio Garza Sada 427 Loc. 4, 5, 6
address:      Monterrey Nuevo Leon 64840
address:      Mexico

contact:      administrative
name:         POC ADM IANA
organisation: NIC-Mexico, ITESM - Campus Monterrey
address:      Av. Eugenio Garza Sada 427 Loc. 4, 5, 6
address:      Monterrey Nuevo Leon 64840
address:      Mexico
phone:        +52 (81) 8864 2600
fax-no:       +52 (81) 8864 2600
e-mail:       adm-iana@nic.mx

contact:      technical
name:         POC TECH IANA
organisation: NIC-Mexico, ITESM - Campus Monterrey
address:      Av. Eugenio Garza Sada 427 Loc. 4, 5, 6
address:      Monterrey Nuevo Leon 64840
address:      Mexico
phone:        +52 (81) 8864 2600
fax-no:       +52 (81) 8864 2600
e-mail:       tech-iana@nic.mx

nserver:      C.MX-NS.MX 192.100.224.1 2001:1258:0:0:0:0:0:1
nserver:      E.MX-NS.MX 189.201.244.1
nserver:      I.MX-NS.MX 207.248.68.1
nserver:      M.MX-NS.MX 200.94.176.1 2001:13c7:7000:0:0:0:0:1
nserver:      O.MX-NS.MX 200.23.1.1
nserver:      X.MX-NS.MX 201.131.252.1
ds-rdata:     39767 8 2 119BEC891BF9CFA5C53D2D95C3340F204CD2F647D624B31CB8D3DF6CFD49281D

whois:        whois.mx

status:       ACTIVE
remarks:      Registration information: http://www.registry.mx/

created:      1989-02-01
changed:      2018-06-27
source:       IANA


Cadena_Invalida/Invalid_String

&PARAMETROS VALIDOS:

 &NombreObjeto    Busca en la base de datos de NIC Mexico el objeto solicitado.
 &=NombreDominio  Verifica la disponibilidad de un nombre de dominio.
 &?               Muestra este mensaje.

&NOTA:
 &Si se busca informacion sobre un dominio este debe pertenecer al ccTLD .mx
```

# Conclusión

El protocolo **WHOIS** nos será muy útil al momento de querer averiguar información referente a algún dominio de internet, lo cual nos brindará *insights* acerca de su uso, su fecha de registro y a quién pertenece.

En el caso del IPN, el *TLD* `.mx` es administrado por el *Instituto Tecnológico de Estudios Superiores de Monterrey* (ITESM), por lo que todos los dominios bajo el *TLD* de `.mx` tendrán en su WHOIS, como *Registrar*, a **NIC - México**. El dominio pertenece al IPN pero es administrado por la organización ya mencionada.

[webIPN]: http://www.ipn.mx