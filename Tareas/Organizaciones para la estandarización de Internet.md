# Organizaciones para la estandarización de Internet

El internet cuenta con múltiples organizaciones y organismos que regulan y establecen el cómo y el por qué de los procesos internos de desarrollo de protocolos de internet así como los mecanismos para el control de sus distintos recursos y servicios.

## ICANN

ICANN es la **Internet Corporation for Assigned Names and Numbers**, una organización sin fines de lucro, formada en 1998 con el fin de mantener el Internet seguro, operable e interoperable.

Básicamente es la coordinación general de direcciones IP y de los dominios de alto nivel (*TLD* por sus siglas en inglés) los cuales se administran en su gran mayoría opr ICANN*. Son los responsables de mantener la infraestructura de DNS funcionando y actualizada para que todos tengamos acceso a sitios de forma rápida y sencilla.

*Algunos TLDs son administrados por los países propios de ellos, por ejemplo: `.de` que es administrado por Alemania o `.uk` que es administrado por el Reino Unido.

## IANA

La **Internet Assigned Numbers Authority**, mejor conocida como *IANA*, es en la actualidad un departamento operado por la **ICANN**, y es la entidad (o subdependencia) que se encarga de supervisar la asignación de direcciones IP, sistemas autónomos, servidores raíz de nombres de dominio DNS y otros recursos relativos a los protocolos de Internet.

En sus inicios, IANA fue administrada principalmente por Jon Postel en el Instituto de Ciencias de la Información (ISI) de la Universidad del Sur de California (USC), en virtud de un contrato de USC/ISI con el Departamento de Defensa de Estados Unidos, hasta que se creó la ICANN para asumir la responsabilidad bajo un contrato del Departamento de Comercio. 

## Registros Regionales de Internet

Los registros regionales de internet son los encargados de la gestión de direcciones IP en ciertas zonas geográficas específicas. De esta forma se permite que cada *región* (o continente) cuente con números asignados para su operación (Direcciones IP y de Sistemas Autónomos). Actualmente existen 5 RIRs (por sus siglas en inglés) y son:

- AFRINIC: Para África.
- ARIN: Para América del Norte.
- APNIC: Para Asia del Este, Oceanía, Sur de Asia y Sureste de Asia.
- LACNIC: Para la mayoría del Caribe y Latinoamérica (México se encuentra bajo este RIR).
- RIPE NCC: Para Europa, Asia Central, Rusia y Oeste de Asia.

## ISP

Un *Proveedor de Servicios de Internet* o un ISP (por sus siglas en inglés), es una organización que provee los servicios requeridos para acceder, usar o participar en Internet. Los proveedores de servicios de internet se dividen en varias categorías como: comerciales, propiedad de la comunidad, sin fines de lucro o privados.

Los servicios típicamente provistos por los ISPs incluyen acceso a Internet, tránsito en Internet, DNS, web hosting, servicio de Usenet y colocación.

### Clasificaciones

Aunque existen múltiples formas de catalogar a los ISPs, las más comunes se enlistan a continuación.

#### Proveedores de Acceso

Los ISPs que son proveedores de acceso, son, como su nombre lo indica, proveedores de acceso a Internet empleando una gran variedad de tecnologías para conectar a los usuarios a su red. Las tecnologías disponibles han variado desde módems de computadora con copladores acústicos a líneas telefónicas, a televisión por cable (CATV), Wi-Fi y Fibra Óptica.

Para los usuarios y pequeñas empresas, las opciones tradicionales incluyen cables de cobre para proveer conectividad del tipo *dial-up*, DSL, túpicamente línea de subscripción digital asimétrica (ADSL), módem para cable o una Red de Servicios Digitales Integrados (ISDN) (típicamente una interfaz básica). Usando fibra óptica para llegar a los usuarios *usualmente* se le conoce como Fibra Al Hogar o de formas similares.

Para clientes con requisitos más demandantes (como empresas grandes o medianas, u otros ISPs) pueden usar DSL de alta velocidad (así como un par trenzado de alta velocidad digital de línea de subscripción), Ethernet, Ethernet metropolitano, Ethernet de gigabit, Frame Relay, ISDN de Tasa de Interfaz Primaria, ATM (Modo de Transferencia Asíncrona) y Redes Ópticas Síncronas (SONET).

El acceso inalámbrico es otra opción, incluyendo celular y acceso a Internet vía satelital.

#### Proveedores de Correo

Un proveedor de Correo Electrónico es una organización que provee servicio de alojamiento de dominios de correo electrónico con acceso al almacenamiento en sus bandejas de correos. Provee con la capacidad de enviar, recibir, aceptar y almacenar correos de usuarios u otras organizaciones a servidores de correo electrónico.

Muchos proveedores de servicios de correo electrónico son también proveedores de acceso a Internet, mientras que otros no lo son (p. ej. Gmail, Yahoo! Mail, Outlook etc). La definición dada en el RFC 6650 cubre servicios de alojamiento de correo electrónico, así como los distintos departamentos de compañías, universidades, organizaciones, grupos e individuos que controlan sus propios servidores de correos. La tarea es típicamente lograda al implementar el Protocolo Simple de Transferencia de Correo (SMTP por sus siglas en inglés) y posiblemente proveer de acceso a los mensajes mediante el Protocolo de Acceso a Mensajes de Internet (IMAP), el Protocolo de la Oficina Postal, Webmail o algún protocolo propietario.

#### ISPs de Alojamiento (Hosting)

Los servicios de Alojamiento para Internet proveen de correo electrónico, alojamiento web, o almacenamiento en línea. Otros servicios pueden incluir Servidores Privados Virtuales (VPS), Servicios en la Nube (AWS, GCP, DigitalOcean) u operación física de Servidores.

#### ISPs de Tránsito

Justo como los clientes pagan por su acceso a Internet, los ISP per sé deben pagar a otros ISPs más grandes por acceso a Internet. Un ISP más grande generalmente cuenta con una red más grande que la del ISP contratador o es capaz de proveer al ISP que lo contrata con acceso a partes del Internet que el ISP que lo contrata no puede acceder.

En el caso más simple, una sola conexión es establecida hacia un ISP grande y es usada para transmitir datos desde y hacia áreas del Internet fuera de la red local; este mode de interconexión es, generalmente, aplicado en cascada múltiples veces hasta que se llega a un Carrier (portador) de Nivel 1. En la realidad, la situación es generalmente más compleja: Los ISPs con más de un punto de presencia (PoP por su siglas en inglés) pueden tener coneciones separadas a un ISP más grande en múltiples puntos de presencia, o pueden ser clientes de múltiples ISPs grandes y pueden tener conexiones a cada one de ellos en uno o más puntos de presencia. Los ISPs de Tránsito proveen grandes cantidades de ancho de banda para conectar, a su vez, a otros ISPs más pequeños y acceder a otros ISPs.

#### ISPs Virtuales

Un ISP virtual (VISP por sus siglas en inglés) es una operación que compra servicios de otro ISP a veces llamado ISP de venta al mayoreo en este contexto, el cual le permite a los clientes del VISP acceder a Internet usando servicios e infraestructura que son propiedad y son operados por el ISP de venta al mayoreo. Los VISPs se parecen a los Operadores Móviles Virtuales (OMVs) y a los proveedores de servicios locales.

#### ISPs Gratuitos

Los ISPs gratuitos son servicios de acceso a internet que proveen su servicio libre de cargos. Muchos de estos ISPs gratuitos muestran anuncios mientras el usuario esté conectado; como la televisión comercial, en el sentido de que están vendiendo la atención del usuario al anunciante. Otros ISPs gratuitos, a veces llamados *freenets*, son organizaciones sin fines de lucro con voluntarios dando mantenimiento.

#### ISP Inalámbrico

Un proveedor inalámbrico de servicios de Internet (WISP por sus siglas en inglés) es un proveedor de servidios de Internet con una red basada en tecnología inalámbrica. La tecnología puede incluir el común Wi-Fi de malla, equipo propietario diseñado para operar sobre bandas abiertas como 900 MHz, 2.4 GHz, 4.9, 5.2, 5.4, 5.7 y 5.8 GHz o frecuencias con licencia como 2.5 GHz (EBS/BRS), 3.65 GHz (NN) y la banda de UHF (incluyendo MMDS) y LMDS.

# Conclusión

La razón fundamental de que una tecnología funciona es la interoperabilidad y la compatibilidad con otras tecnologías y versiones de la misma. Es, a mi parecer, una de las razones por las que Internet ha prosperado de la forma en que lo ha hecho. Construir bloques sólidos de ingeniería ha permitido a Internet alcanzar el nivel que tiene actualmente y, sin lugar a dudas, es importante conocer a los comités, organizaciones y consejos que se han encargado de fijar los estándares de funcionamiento y compatibilidad que han permitido el desarrollo  de esta tecnología.