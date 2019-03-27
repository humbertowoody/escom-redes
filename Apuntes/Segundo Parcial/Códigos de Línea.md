# Códigos de Línea

> Es la manera como se codifican los bits en el medio de transmisión.

Algunos códigos de línea:

![Códigos de Línea 1][codigos-linea-1]

![Códigos de Línea 2][codigos-linea-2]

**B8ZS** es como AMI pero incluye 2 violaciones de código cuando se detectan 8 ceros consecutivos:

- Si se detectan 8 ceros y el último pulso fue positivo (+), se sustituyen los 0's por 000+-0-+.
- Si se detectan 8 ceros y el último pulso fue negativo (-), se sustituye los 0's por 000-+0+-.

[codigos-linea-1]: https://i.imgur.com/fSmoGST.jpg
[codigos-linea-2]: https://i.imgur.com/ucA94HN.jpg
