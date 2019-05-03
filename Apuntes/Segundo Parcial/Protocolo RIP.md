# Protocolo RIP

> Routing Information Protcol

- Creado en 1988 por la empresa *XEROX*, es un ISP.
- Su funcionamiento está basado en el algoritmo *Bellman - Ford*.
- No puede ser implementado en redes extensas (Diámetro Máximo de 15 saltos) pues no se reconocen rutas circulares.
- Transmite a **broadcast** en el puerto 520 UDP las tablas de enrutamiento por lo que es muy suceptible a un ataque.
- Tiene problemas dado que puede darse el caso que un enrutador vecino publique su tabla de enrutamiento antes de que uno publique que tuvo una desconexión, por lo que actualizará su tabla de enrutamiento y posteriormente la publicará. Eventualmente se soluciona, pero toma tiempo y es por eso por lo que no se usa en redes grandes.
