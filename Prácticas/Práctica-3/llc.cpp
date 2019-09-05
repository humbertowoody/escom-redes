/**
 * Práctica 3
 * Analizar el encabezado de 802.3 (HDLC,LLC)
 * Humberto Alcocer, 2019
 */
#include <iostream>
#include <iomanip>
#include <pcap.h>

#define DEFAULT_FILE "./paquetes.pcap"

int packets = 0; // Contador de Paquetes leídos.

/**
 * Función para mostrar el uso del programa.
 */
void usage(char *progname)
{
  std::cout << "Uso: " << progname << " <nombre de archivo>" << std::endl;
  std::cout << "(Si no se especifica un nombre de archivo se utilizará ./paquetes.pcap)" << std::endl;
}

void print_hex(unsigned char byte)
{
  std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex
            << static_cast<int>(byte)
            << std::setw(1) << std::dec;
}

/**
 * Imprime datos referentes a LLC, HDLC u 802.3
 */
void print_llc(u_char *user, const struct pcap_pkthdr *hdr, const u_char *data)
{
  int longitud; // Variable para almacenar el campo `longitud`.

  // Inicio de Análisis.
  std::cout << "------ Análisis -------" << std::endl;

  // Imprimir el número de paquete capturado.
  std::cout << "·Número de Paquete: " << packets << std::endl;

  // MAC Destino.
  std::cout << "·MAC Destino: ";
  for (int i = 0; i < 6; i++)
  {
    print_hex(data[i]);
    if (i < 5)
      std::cout << ":";
    else
      std::cout << std::endl;
  }

  // MAC Origen.
  std::cout << "·MAC Origen: ";
  for (int i = 6; i < 12; i++)
  {
    print_hex(data[i]);
    if (i < 11)
      std::cout << ":";
    else
      std::cout << std::endl;
  }

  // Longitud.
  longitud = (data[12] * 256) + data[13];
  std::cout << "·Longitud: ";
  print_hex(data[12]);
  print_hex(data[13]);
  std::cout << " (" << longitud << ")." << std::endl;

  if (longitud < 1500)
  {
    // Informar que es trama 802.3
    std::cout << "· La trama es IEEE 802.3" << std::endl;

    // DSAP.
    std::cout << "·DSAP: ";
    print_hex(data[14]);
    std::cout << std::endl;

    // SSAP.
    std::cout << "·SSAP: ";
    print_hex(data[15]);
    std::cout << std::endl;

    // Análisis en modo extendido o modo simple.
    if (longitud > 3)
    {
      // Modo extendido.
      std::cout << "·Tipo de Modo: Extendido." << std::endl;

      // Campo de Control
      std::cout << "·Campo de Control: ";
      print_hex(data[16]);
      print_hex(data[17]);
      std::cout << std::endl;
      std::string control = std::bitset<8>(data[16]).to_string() + std::bitset<8>(data[17]).to_string();
      std::cout << "  ~ Binario: " << control << std::endl;

      // Análisis de tipo de trama.
      std::cout << "·Análisis de trama:" << std::endl;
      if (control.at(0) == '0')
      {
        std::cout << "  ~ Trama tipo: I" << std::endl;
        std::cout << "  ~ N(S) = " << control.substr(1, 7) << std::endl;
        std::cout << "  ~ Bit P/F: " << control.at(8) << std::endl;
        std::cout << "  ~ N(R) = " << control.substr(9, 7) << std::endl;
      }
      else
      {
        if (control.at(1) == '0')
        {
          // Imprimir tipo de trama.
          std::cout << "  ~ Trama tipo: S" << std::endl;
          // Extraer código e imprimir datos.
          std::string codigoS = control.substr(2, 2);
          std::cout << "  ~ Código: " << codigoS << " (";
          if (codigoS.compare("00"))
            std::cout << "RR) [Listo para recibir]" << std::endl;
          else if (codigoS.compare("01"))
            std::cout << "REJ) [Rechazo]" << std::endl;
          else if (codigoS.compare("10"))
            std::cout << "RNR) [No listo para recibir]" << std::endl;
          else if (codigoS.compare("11"))
            std::cout << "SREJ) [Rechazo selectivo]" << std::endl;
          else
            std::cout << "Desconocido)" << std::endl;
          // Bit P/F
          std::cout << "  ~ Bit P/F: " << control.at(8) << std::endl;
          // N(R)
          std::cout << "  ~ N(R) = " << control.substr(9, 7) << std::endl;
        }
        else
        {
          // Trama tipo U.
          std::cout << "  ~ Trama tipo: U" << std::endl;
          // Bit P/F
          std::cout << "  ~ Bit P/F" << control.at(4) << std::endl;
          // Extraer código de trama U e imprimir.
          std::string codigo = control.substr(2, 2) + control.substr(5, 3);
          std::cout << "  ~ Código: " << codigo << " (";
          if (codigo.compare("00001"))
            std::cout << "SNRM)" << std::endl;
          else if (codigo.compare("11011"))
            std::cout << "SNRME)" << std::endl;
          else if (codigo.compare("11000"))
            std::cout << "SARM)" << std::endl;
          else if (codigo.compare("11010"))
            std::cout << "SARME)" << std::endl;
          else if (codigo.compare("11100"))
            std::cout << "SABM)" << std::endl;
          else if (codigo.compare("11110"))
            std::cout << "SABME)" << std::endl;
          else if (codigo.compare("00000"))
            std::cout << "UI)" << std::endl;
          else if (codigo.compare("00110"))
            std::cout << "Acuse sin Numerar)" << std::endl;
          else if (codigo.compare("00010"))
            std::cout << "DISC)" << std::endl;
          else if (codigo.compare("11001"))
            std::cout << "RSET)" << std::endl;
          else if (codigo.compare("10001"))
            std::cout << "Rechazo de Tramas)" << std::endl;
          else if (codigo.compare("00100"))
            std::cout << "UP)" << std::endl;
          else
            std::cout << "Desconocido)" << std::endl;
        }
      }
    }
    else
    {
      // Modo normal.
      std::cout << "·Tipo de Modo: Normal." << std::endl;

      // Campo de Control.
      std::cout << "·Campo de Control: ";
      print_hex(data[16]);
      std::cout << std::endl;
      std::string control = std::bitset<8>(data[16]).to_string();
      std::cout << "  ~ Binario: " << control << std::endl;

      // Análisis.
      std::cout << "·Análisis de tipo de trama:" << std::endl;
      if (control.at(0) == '0')
      {
        // Trama tipo I.
        std::cout << "  ~ Trama tipo: I" << std::endl;
        // N(S)
        std::cout << "  ~ N(S) = " << control.substr(1, 3) << std::endl;
        // Bit P/F
        std::cout << "  ~ Bit P/F: " << control.at(4) << std::endl;
        // N(R)
        std::cout << "  ~ N(R) = " << control.substr(5, 3) << std::endl;
      }
      else
      {
        if (control.at(1) == '0')
        {
          // Trama S.
          std::cout << "  ~ Trama tipo: S" << std::endl;
          // Extraer código de trama S.
          std::string codigoS = control.substr(2, 2);
          std::cout << "  ~ Código: " << codigoS << " (";
          if (codigoS.compare("00"))
            std::cout << "RR) [Listo para recibir]" << std::endl;
          else if (codigoS.compare("01"))
            std::cout << "REJ) [Rechazo]" << std::endl;
          else if (codigoS.compare("10"))
            std::cout << "RNR) [No listo para recibir]" << std::endl;
          else if (codigoS.compare("11"))
            std::cout << "SREJ) [Rechazo selectivo]" << std::endl;
          else
            std::cout << "Desconocido)" << std::endl;
          // Imprimir bit P/F.
          std::cout << "  ~ Bit P/F: " << control.at(4) << std::endl;
          // Imprimir N(R).
          std::cout << "  ~ N(R) = " << control.substr(5, 3) << std::endl;
        }
        else
        {
          // Trama tipo U.
          std::cout << "  ~ Trama tipo: U" << std::endl;
          // Bit P/F
          std::cout << "  ~ Bit P/F" << control.at(4) << std::endl;
          // Extraer código de trama U e imprimir.
          std::string codigo = control.substr(2, 2) + control.substr(5, 3);
          std::cout << "  ~ Código: " << codigo << " (";
          if (codigo.compare("00001"))
            std::cout << "SNRM)" << std::endl;
          else if (codigo.compare("11011"))
            std::cout << "SNRME)" << std::endl;
          else if (codigo.compare("11000"))
            std::cout << "SARM)" << std::endl;
          else if (codigo.compare("11010"))
            std::cout << "SARME)" << std::endl;
          else if (codigo.compare("11100"))
            std::cout << "SABM)" << std::endl;
          else if (codigo.compare("11110"))
            std::cout << "SABME)" << std::endl;
          else if (codigo.compare("00000"))
            std::cout << "UI)" << std::endl;
          else if (codigo.compare("00110"))
            std::cout << "Acuse sin Numerar)" << std::endl;
          else if (codigo.compare("00010"))
            std::cout << "DISC)" << std::endl;
          else if (codigo.compare("11001"))
            std::cout << "RSET)" << std::endl;
          else if (codigo.compare("10001"))
            std::cout << "Rechazo de Tramas)" << std::endl;
          else if (codigo.compare("00100"))
            std::cout << "UP)" << std::endl;
          else
            std::cout << "Desconocido)" << std::endl;
        }
      }
    }
  }
  else
  {
    // No es trama 802.3
    std::cout << "· Esta trama NO es IEEE 802.3." << std::endl;
  }

  // Imprimir fin de Análisis.
  std::cout << "--- Fin de Análisis ---" << std::endl;

  // Aumentar contador.
  packets++;
}

// Función principal.
int main(int argc, char **argv)
{
  pcap_t *p;                     // Descriptor para captura de paquetes.
  char filename[80];             // Nombre del archivo con los paquetes a leer.
  char errbuf[PCAP_ERRBUF_SIZE]; // Buffer para mensajes de error.
  char prestr[80];               // String de prefijos de error de pcap.

  // Si existe un segundo argumento (el nombre del archivo), lo usaremos,
  // en caso de que no exista, usaremos el default.
  if (argc >= 2)
    strcpy(filename, argv[1]);
  else
    strcpy(filename, DEFAULT_FILE);

  // Abrir archivo con los paquetes a procesar.
  if (!(p = pcap_open_offline(filename, errbuf)))
  {
    std::cerr << "Error abriendo archivo, " << filename << ", para lectura: " << errbuf << std::endl;
    return 2;
  }

  // Procesar cada paquete.
  if (pcap_dispatch(p, 0, &print_llc, (unsigned char *)0) < 0)
  {
    // Imprimir el error.
    std::cerr << "Error leyendo paquetes desde el archivo: " << filename << std::endl;
    pcap_perror(p, prestr);
    return 4;
  }

  // Imprimir el número de paquetes analizados.
  std::cout << "Paquetes procesados: " << packets << std::endl;

  // Cerrar el dispositivo de captura de paquetes.
  pcap_close(p);
  return 0;
}