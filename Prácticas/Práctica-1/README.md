# Práctica 1

**Nombre:** Humberto Alejandro Ortega Alcocer

**Número de Boleta:** 20166304495

**Fecha:** 28/08/2019

## Tabla de Contenidos

- [Práctica 1](#pr%c3%a1ctica-1)
  - [Tabla de Contenidos](#tabla-de-contenidos)
  - [Introducción](#introducci%c3%b3n)
  - [Desarrollo](#desarrollo)
    - [Requerimiento: Homebrew](#requerimiento-homebrew)
    - [Instalar `libpcap`](#instalar-libpcap)
    - [Compilación de programas](#compilaci%c3%b3n-de-programas)
  - [Prueba](#prueba)
  - [Posibles Mejoras](#posibles-mejoras)
  - [Conclusiones](#conclusiones)
  - [Fuentes](#fuentes)

## Introducción

En esta primer práctica nos enfocamos en la instalación de todo el software y librerías necesarias para el desarrollo de programas que interactúen con paquetes de red en nuestras computadoras. Para ello, instalamos la librería `pcap` en las versiones necesarias para cada plataforma, así como los *wrappers* de las librerías requeridos por el lenguaje que vayamos a emplear para el desarrollo de las prácticas.

En mi caso en particular, realicé la instalación para mi configuración:

- MacOS (10.14)
- C++ (g++ 9.2)

## Desarrollo

En el caso de MacOS (y de algunos sistemas basados en GNU/Linux), la librería a emplear es `libpcap` dado que no se requieren de modificaciones especiales al SO ya que se cuenta de antemano con todo lo necesario para acceder a los datos en las distintas capas de red.

### Requerimiento: Homebrew

Para instalar la librería, primeramente corroboraremos que tenemos instalado `homebrew` (el cual nos permite instalar software de terceros en nuestra computadora) con el siguiente comando:

`$ brew --version`

En caso de **no** contar con Homebrew, podemos realizar su instalación siguiendo [los pasos en su web oficial](https://brew.sh/index_es), o bien, con el siguiente comando:

`$ /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"`

### Instalar `libpcap`

Para realizar la instalación de la librería, introducimos el comando:

`$ brew install libpcap`

Con lo cual Homebrew realizará la instalación de la librería y sus dependencias.

### Compilación de programas

Para compilar un programa en C++, basta con ejecutar:

`$ g++ miprograma.cpp -o miejecutable.out`

Lo cual generará el binario `miejecutable.out` el cual podemos ejecutar con el siguiente comando:

`./miejecutable.out`

Para realizar el proceso de *linking* de la librería `libpcap`, debemos especificarle al compilador la ubicación de los archivos objeto de la librería. Por suerte para nosotros, al instalar la librería se añaden nuevos "shortcuts" que exportan los directorios en el formato correcto para ser ingresados directamente en el momento de compilación. En nuestro caso: `-lpcap` que se encarga de introducir los parámetros adecuados para que nuestro compilador encuentre la librería y la compile con nuestro programa.

El comando de compilación final quedaría:

`$ g++ miprograma.cpp -lpcap -o miejecutable.out`

Con lo cual podremos usar nuestras librerías recién instaladas.

## Prueba

Para realizar la prueba, usaremos un código de ejemplo muy simple que únicamente lee las interfaces de red disponibles e imprime la primera. Esto es únicamente para corroborar que la instalación fue correcta. El archivo lo llamaremos `prueba.c` y éste será su contenido:

```c
#include <stdio.h>
#include <pcap.h>

int main(int argc,char *argv[])
{
    char *dev, errbuf[PCAP_ERRBUF_SIZE];

    dev = pcap_lookupdev(errbuf);
    if(dev == NULL)
    {
        fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
        return(2);
    }

    printf("Device %s\n", dev);
    return(0);
}
```

Lo compilaremos con el comando:

`$ gcc prueba.c -lpcap -o prueba.out`*

Y lo ejecutaremos con:

`./prueba.out`

Obteniendo como resultado:

`Device en0`

Lo cual demuestra que la librería está correctamente instalada y puede ser incluída en nuestro código sin problema alguno.

**Nota: El código está escrito en `C` puro, la diferencia entre usar `C` y `C++` es objeto de discusión, pero como buena práctica, para compilar programas en `C` usaremos `gcc` y para compilar programas en `C++` usaremos `g++` aunque, en la realidad, ambos compiladores son intercambiables.*

## Posibles Mejoras

Si quisiéramos realizar una instalación pura, podríamos referirnos a [la web oficial de libpcap](https://www.tcpdump.org/#latest-releases) y descargar la última versión de la librería. Compilarla y colocarla en algún directorio común y proporcionar la ubicación al compilador para que compilemos usando esa versión de la librería, sin embargo, la versión con la que cuenta Homebrew es más que suficiente para el contenido del curso.

## Conclusiones

Instalar una librería es dependiente a la plataforma dónde se esté realizando el desarrollo, así como del lenguaje y la configuración que tengamos en nuestro entorno de desarrollo. Para MacOS, Homebrew ha simplificado este proceso y es muy fácil incluir la librería y comenzar a usarla en 10 minutos.

## Fuentes

Las fuentes de información empleadas para la realización de esta práctica son:

- [Homebrew](brew.sh)
- [Página oficial de TCPDump](https://www.tcpdump.org)
- [Fórmula de `libpcap`en Homebrew](https://formulae.brew.sh/formula/libpcap)
