## Ancho de Banda (B)

Intervalo de frecuencias positivas donde la respuesta es relativamente plana, por  lo tanto las señales pueden pasar sin distorsión. En este rango de frecuencias se concentra la mayor cantidad de la energía de la señal. Se mide en Hertz (Hz).

## Relación Señal-Ruido (S/N)

Expresa la cantidad en que una señal de información excede el nivel de ruido presente en el medio.

```txt
        Potencia señal (watts)
S/N = --------------------------
        Potencia ruido (watts)
```

Para pasarlo a decibeles:

```txt
                              Potencia señal (watts)
(S/N)dB =  10 log (base 10) --------------------------
                              Potencia ruido (watts)
```

## Teorema de Muestreo

Si la frecuencia más alta contenida en una señal analógica es `Fmax = B`y la señal es muestreada con una `frecuencia = 2B`, entonces la señal podrá ser perfectamente recuperada a partir de las muestras.