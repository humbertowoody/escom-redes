/**
 * Redes de Computadoras.
 * Sniffer.
 * Humberto Alcocer, 2019.
 */
#include <iostream>
#include <iomanip>
#include <pcap.h>
#include <string>
#include <chrono>

#define MAX_CAPTURE_NUMBER 1000 // El número máximo de paquetes a capturar.
#define MAX_PACKET_SIZE 65536   // El valor máximo de tamaño de paquete.
#define MIN_PACKET_SIZE 100     // El valor mínimo para el tamaño de los paquetes.
#define MAX_TIMEOUT 10000       // El valor máximo de timeout para la captura de paquetes.
#define MIN_TIMEOUT 10          // El valor mínimo de timeout para la captura de paquetes.

/**
 * cap_stats
 * Estructura con todos los datos de las estadísticas de la sesión de sniffing.
 */
typedef struct
{
  int total_packets;                                    // Número de paquetes capturados.
  int ip_packets;                                       // Número de paquetes IP procesados.
  int non_ip_packets;                                   // Número de paquetes que no son IP.
  int iee8023_packets;                                  // Número de tramas 802.3 procesadas.
  int ethernet_packets;                                 // Número de paquetes Ethernet procesados.
  int tcp_packets;                                      // Número de paquetes TCP procesados.
  int udp_packets;                                      // Número de paquetes UDP procesados.
  int icmp_packets;                                     // Número de paquetes ICMP procesados.
  std::chrono::high_resolution_clock::time_point start; // Inicio de Captura.
  std::chrono::high_resolution_clock::time_point end;   // Fin de Captura.
} cap_stats;

// Variable global con las estadísticas.
cap_stats capture_statistics;

/**
 * configuration
 * Estructura con la configuración para el Sniffer.
 */
typedef struct
{
  bool save_to_file;        // Guardar los paquetes a un archivo.
  std::string out_filename; // Ruta al archivo para guardar los paquetes.
  pcap_dumper_t *dumper;    // El dumper para ir vaciando los paquetes al archivo.
} configuration;

// Variable global de configuración.
configuration global_configuration;

/**
 * Prototipo de función que imprime las estadísticas de la sesión de captura.
 */
void print_stats();

/**
 * Prototipo de función para analizar paquetes.
 */
void packet_handler(unsigned char *param, const struct pcap_pkthdr *header, const unsigned char *pkt_data);

/**
 * Prototipo de función para imprimir números hexadecimales adecuadamente.
 */
void print_hex(unsigned char byte);

/**
 * Prototipo de función para calcular checksum del encabezado IP.
 */
unsigned int calculateChecksum(const unsigned char *buf, int length);

/**
 * Función principal.
 */
int main(int argc, char const *argv[])
{
  // Variables.
  pcap_if_t *alldevs;            // Todas las tarjetas de red.
  pcap_if_t *d;                  // La tarjeta de red a usar.
  pcap_t *adhandle;              // Handler de la tarjeta a usar.
  int inum, i, packet_number,    // Contadores.
      temp;                      // Variable miscelánea.
  char option;                   // Temporal.
  std::string filtro;            // Filtro de búsqueda.
  struct bpf_program fp;         // Filtro compilado.
  int packet_size,               // Tamaño del paquete a capturar.
      timeout;                   // Timeout de los paquetes.
  bool promisc,                  // Modo promiscuo de la tarjeta de red.
      use_file;                  // Leer paquetes de un archivo o 'al vuelo'.
  char errbuf[PCAP_ERRBUF_SIZE]; // Buffer para errores.
  std::string in_filename;       // Lectura de paquetes desde archivo.

  // Inicio de Programa
  std::cout << "Sniffer de Paquetes" << std::endl
            << std::endl;

  do
  {
    std::cout << "Selecciona el tipo de captura:" << std::endl
              << std::endl;
    std::cout << "  1) Captura de paquetes 'al vuelo'." << std::endl;
    std::cout << "  2) Usar un archivo." << std::endl;
    std::cout << std::endl;
    std::cout << "Tu opción: ";
    std::cin >> temp;
  } while (temp < 1 || temp > 2);

  // Tipo de captura.
  use_file = (temp == 2);

  if (use_file)
  {
    // Capturar el nombre del archivo.
    std::cout << "Nombre del archivo: ";
    std::cin >> in_filename;
    std::cout << "Se realizará la lectura desde: " << in_filename << std::endl;

    // Abrir archivo on los paquetes a procesar.
    if (!(adhandle = pcap_open_offline(in_filename.c_str(), errbuf)))
    {
      std::cerr << "Error abriendo archivo, " << in_filename << ", para letura: " << errbuf << std::endl;
      return 2;
    }
  }
  else
  {
    // Obtener la lista de dispositivos.
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
      std::cerr << "Error encontrando dispositivos: " << errbuf << std::endl;
      return -1; // Error.
    }

    // Informar al usuario del siguiente proceso.
    std::cout << "Selecciona una interfaz de red: " << std::endl
              << std::endl;

    // Imprimir la lista de interfaces.
    for (d = alldevs, i = 0; d; d = d->next, ++i)
    {
      std::cout << (i + 1) << ") " << d->name;
      std::cout << " (" << (d->description ? d->description : "Sin descripción")
                << ")" << std::endl;
    }
    std::cout << std::endl; // Salto de línea.

    // Verificar que se haya detectado al menos una tarjeta de red.
    if (i == 0)
    {
      std::cout << "¡No se ha podido detectar alguna interfaz!" << std::endl;
      std::cout << "Asegúrate de que los drivers y las librerías se encuentren bien instaladas." << std::endl;
      return -1; // Error.
    }

    // Ciclo para que el usuario seleccione una interfaz válida.
    do
    {
      std::cout << "Ingresa el número de la interfaz (1-" << i << "): ";
      std::cin >> inum;
    } while (inum < 1 || inum > i);

    // Saltar a la interfaz seleccionada.
    for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++)
      ;

    // Obtener el tamaño de paquete a usar.
    do
    {
      std::cout << "¿Cuál es el tamaño de paquete a usar?" << std::endl;
      std::cout << "(" << MIN_PACKET_SIZE << " - " << MAX_PACKET_SIZE << "): ";
      std::cin >> packet_size;
    } while (packet_size > MAX_PACKET_SIZE || packet_size < MIN_PACKET_SIZE);

    // Preguntar por el modo promiscuo.
    do
    {
      std::cout << "¿Desea abrir la interfaz en modo promiscuo? S/N: ";
      std::cin >> option;
    } while (option != 's' && option != 'S' && option != 'n' && option != 'N');

    // Configurar variable.
    promisc = (option == 's' || option == 'S');

    // Obtener el valor de timeout para la captura.
    do
    {
      std::cout << "¿Cuál es el tiempo de timeout que deseas usar (en ms)?" << std::endl;
      std::cout << "El valor recomendado es de 1000." << std::endl;
      std::cout << "(10 - 10000): ";
      std::cin >> timeout;
    } while (timeout < MIN_TIMEOUT || timeout > MAX_TIMEOUT);

    // Abrir el dispositivo y el adaptador.
    if ((adhandle = pcap_open_live(d->name,     // Nombre del dispositivo.
                                   packet_size, // Porción del paquete (65536 es el máximo tamaño).
                                   promisc,     // Modo promiscuo.
                                   1000,        // Timeout de lectura.
                                   errbuf       // Buffer de error.
                                   )) == NULL)
    {
      std::cerr << "No fue posible abrir el adaptador." << std::endl;
      std::cerr << "Probablemente haya un error con: " << d->name << std::endl;
      pcap_freealldevs(alldevs); // Liberar la memoria de los dispositivos.
      return -1;                 // Error.
    }

    // Preguntar para guardar los paquetes capturados.
    do
    {
      std::cout << "¿Deses guardar los paquetes capturados? S/N: ";
      std::cin >> option;
    } while (option != 's' && option != 'S' && option != 'n' && option != 'N');

    global_configuration.save_to_file = (option == 'S' || option == 's');

    if (global_configuration.save_to_file)
    {
      // Archivo para guardar paquetes.
      std::cout << "Nombre del archivo para guardar: ";
      std::cin.ignore();
      std::getline(std::cin, global_configuration.out_filename);

      std::cout << "Los paquetes se guardarán en " << global_configuration.out_filename << std::endl;

      // Inicializar dumper.
      global_configuration.dumper = pcap_dump_open(adhandle, global_configuration.out_filename.c_str());
    }
  }

  // Preguntar al usuario el número de paquetes a capturar.
  do
  {
    std::cout << "¿Cuántos paquetes deseas capturar? (1-" << MAX_CAPTURE_NUMBER << "): ";
    std::cin >> packet_number;

  } while (packet_number < 0 || packet_number > MAX_CAPTURE_NUMBER);

  // Preguntar por el filtro de búsqueda.
  do
  {
    std::cout << "¿Desea usar un filtro de captura? S/N: ";
    std::cin >> option;

  } while (option != 'S' && option != 's' && option != 'N' && option != 'n');

  // Si seleccionó que si, obtener el filtro.
  if (option == 'S' || option == 's')
  {
    do
    {
      std::cout << "Introduce tu filtro: ";
      std::cin.ignore();
      std::getline(std::cin, filtro);
      std::cout << "¿El filtro \"" << filtro << "\" es correcto? S/N: ";
      std::cin >> option;
    } while (option != 'S' && option != 's');

    // Compilar el filtro.
    if (pcap_compile(adhandle, &fp, filtro.c_str(), 0, PCAP_NETMASK_UNKNOWN) == -1)
    {
      std::cerr << "El filtro: \"" << filtro << "\" NO es válido." << std::endl;
      return 2;
    }
    // Aplicar el filtro.
    if (pcap_setfilter(adhandle, &fp) == -1)
    {
      std::cerr << "No se ha podido instalar el filtro en la tarjeta." << std::endl;
      return 2;
    }
  }

  // Inicializar estadísticas en 0.
  capture_statistics.ethernet_packets = 0;
  capture_statistics.icmp_packets = 0;
  capture_statistics.iee8023_packets = 0;
  capture_statistics.ip_packets = 0;
  capture_statistics.non_ip_packets = 0;
  capture_statistics.tcp_packets = 0;
  capture_statistics.udp_packets = 0;
  capture_statistics.total_packets = 0;
  capture_statistics.start = std::chrono::high_resolution_clock::now();

  if (!use_file)
  {
    // Informar al usuario que se inicia la captura.
    std::cout << "Escuchando en: " << (d->description ? d->description : d->name) << std::endl;

    // En este punto, no se requiere más de la lista de dispositivos, liberarla.
    pcap_freealldevs(alldevs);

    // Comenzar la captura.
    pcap_loop(adhandle, packet_number, &packet_handler, NULL);
  }
  else
  {
    // Informar al usuario que se inicia el procesamiento de paquetes.
    std::cout << "Leyendo paquetes desde " << in_filename << std::endl;

    // Realizar el procesamiento de paquetes.
    if (pcap_dispatch(adhandle, 0, &packet_handler, (unsigned char *)0) < 0)
    {
      std::cerr << "Error leyendo paquetes desde el archivo: " << in_filename << std::endl;
      return 4;
    }
  }

  // Finalizar la captura.
  pcap_close(adhandle);

  // Configurar la hora de finalización de la captura.
  capture_statistics.end = std::chrono::high_resolution_clock::now();

  // En caso de haber guardado paquetes, cerrar el archivo.
  if (global_configuration.save_to_file)
  {
    pcap_dump_close(global_configuration.dumper);
  }

  // Imprimir las estadísticas.
  print_stats();

  // Mensaje de despedida.
  std::cout << "La captura ha terminado." << std::endl
            << std::endl;
  std::cout << "ESCOM. Redes de Computadoras - 2019" << std::endl;
  return 0;
}

/**
 * Función para imprimir números decimales adecuadamente.
 */
void print_hex(unsigned char byte)
{
  std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex
            << static_cast<int>(byte)
            << std::dec << std::setw(1);
}

void print_stats()
{
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(capture_statistics.end - capture_statistics.start).count();
  std::cout << std::endl;
  std::cout << "Estadísticas de Captura:" << std::endl
            << std::endl;
  std::cout << "- Paquetes Ethernet:   " << capture_statistics.ethernet_packets << std::endl;
  std::cout << "- Paquetes IEEE 802.3: " << capture_statistics.iee8023_packets << std::endl;
  std::cout << "  · Paquetes IP:       " << capture_statistics.ip_packets << std::endl;
  std::cout << "  · Paquetes no IP:    " << capture_statistics.non_ip_packets << std::endl;
  std::cout << "    ~ Paquetes ICMP:   " << capture_statistics.icmp_packets << std::endl;
  std::cout << "    ~ Paquetes TCP:    " << capture_statistics.tcp_packets << std::endl;
  std::cout << "    ~ Paquetes UDP:    " << capture_statistics.udp_packets << std::endl;
  std::cout << "---------------------------------" << std::endl;
  std::cout << "- Total de Paquetes: " << capture_statistics.total_packets << std::endl;
  std::cout << "- Duración de la sesión de captura: " << duration << "ms" << std::endl;
  std::cout << std::endl;
}

/**
 * Función de Callback para analizar cada paquete.
 */
void packet_handler(unsigned char *param, const struct pcap_pkthdr *header, const unsigned char *pkt_data)
{
  // Variables.
  struct tm *ltime;    // Tiempo "crudo".
  char timestr[16];    // Tiempo "leíble".
  time_t local_tv_sec; // Variable para conversión.

  // Limpiar parámetros.
  (void)(param);
  (void)(pkt_data);

  // Convertir el timestamp a un formato leíble.
  local_tv_sec = header->ts.tv_sec;
  ltime = localtime(&local_tv_sec);
  strftime(timestr, sizeof timestr, "%H:%M:%S", ltime); // Convertir a formato HH:MM:SS

  // Impimir
  std::cout << "***************** PAQUETE CAPTURADO *****************" << std::endl;
  // Hora de Captura.
  std::cout << "Hora de Captura: " << timestr << std::endl;
  std::cout << "Número de Paquete: " << capture_statistics.total_packets << std::endl;
  // Trama Ethernet.
  std::cout << "--- Trama Ethernet (u 802.3) ---" << std::endl;

  // MAC Destino.
  std::cout << "· MAC Destino: ";
  for (int j = 0; j < 6; j++)
  {
    print_hex(pkt_data[j]);
    if (j < 5)
    {
      std::cout << ":";
    }
    else
    {
      std::cout << std::endl;
    }
  }

  // MAC Origen.
  std::cout << "· MAC Origen: ";
  for (int k = 6; k < 12; k++)
  {
    print_hex(pkt_data[k]);
    if (k < 11)
    {
      std::cout << ":";
    }
    else
    {
      std::cout << std::endl;
    }
  }

  // Ether Type
  std::cout << "· Ether Type: ";
  print_hex(pkt_data[12]);
  print_hex(pkt_data[13]);
  std::cout << std::endl;

  // Tipo de paquete en capa de Red.
  auto tipo = (pkt_data[12] * 256) + pkt_data[13];

  // Imprimir resultados.
  std::cout << "· Tipo de Paquete: " << tipo << std::endl;

  // Determinar si es de tipo Ethernet u 802.3
  if (tipo > 1534)
  {
    std::cout << "· El paquete es Ethernet." << std::endl;
    capture_statistics.ethernet_packets++;
  }
  else
  {
    std::cout << "· El paquete es 802.3 + LLC." << std::endl;
    capture_statistics.iee8023_packets++;
  }

  // Informar si es un paquete IP.
  std::cout << "· ¿Es un paquete IP? " << (tipo == 2048 ? "Sí" : "No")
            << "." << std::endl;

  // Fin de análisis de Trama Ethernet.
  std::cout << "--- Fin Trama Ethernet (u 802.3) ---" << std::endl;

  // Analizar IP.
  if (tipo == 2048)
  {
    // Aumentar contador.
    capture_statistics.ip_packets++;

    // Pseudo-Encabezado para TCP/UDP.
    unsigned char pseudo_ip[12];

    // Imprimir inicio de análisis de IP.
    std::cout << "--- Paquete IP ---" << std::endl;

    // Versión de IP.
    std::cout << "· Versión de IP: " << (pkt_data[14] >> 4) << std::endl;

    // IHL.
    std::cout << "· Longitud de Encabezado: " << (pkt_data[14] & 0X0F)
              << " x 4 = " << ((pkt_data[14] & 0X0F) * 4)
              << " bytes." << std::endl;

    // Tipo de Servicio.
    std::cout << "· Tipo de Servicio: ";
    print_hex(pkt_data[15]);
    std::cout << std::endl;

    // Tamaño Total.
    std::cout << "· Tamaño Total: " << ((pkt_data[16] * 256) + pkt_data[17]) << std::endl;

    // Tamaño de Datos.
    unsigned int ipDataSize = (((pkt_data[16] * 256) + pkt_data[17]) - ((pkt_data[14] & 0X0F) * 4));

    std::cout << "· Tamaño de Datos: " << ipDataSize << " bytes" << std::endl;

    // TTL 22
    std::cout << "· Tiempo de Vida (TTL): " << static_cast<int>(pkt_data[22]) << std::endl;

    // Protocolo 23
    int protocolo = static_cast<int>(pkt_data[23]);
    std::cout << "· Protocolo: ";
    print_hex(pkt_data[23]);
    std::cout << " (";
    switch (protocolo)
    {
    case 1:
      std::cout << "ICMP";
      break;
    case 6:
      std::cout << "TCP";
      break;

    case 17:
      std::cout << "UDP";
      break;

    default:
      std::cout << "No es ICMP, TCP ni UDP";
      break;
    }
    std::cout << ")" << std::endl;

    // Checksum 24 y 25
    std::cout << "· Checksum: ";
    print_hex(pkt_data[24]);
    print_hex(pkt_data[25]);
    std::cout << std::endl;

    // Análisis de Checksum para IP.
    uint16_t ip_checksum_result = calculateChecksum(&pkt_data[14], ((pkt_data[14] & 0X0F) * 4));

    std::cout << "· ¿Checksum Correcto? " << (ip_checksum_result == 0 ? "Sí" : "No") << "." << std::endl;

    // En caso de ser erróneo, corregirlo.
    if (ip_checksum_result != 0)
    {
      // Nuevo encabezado con Checksum en 0 (puesto que lo vamos a generar).
      unsigned char *new_header;

      // Copiar el encabezado.
      memcpy(new_header, &pkt_data[14], ((pkt_data[14] & 0X0F) * 4));

      // Colocar en 0's el Checksum.
      new_header[10] = new_header[11] = 0;

      // Imprimir el resultado.
      std::cout << "· Checksum Corregido: " << calculateChecksum(new_header, ((pkt_data[14] & 0X0F) * 4));
    }

    // IP Origen 26, 27, 28 y 29.
    std::cout << "· IP Origen: ";
    for (int i = 26; i < 30; i++)
    {
      std::cout << static_cast<int>(pkt_data[i]);
      if (i < 29)
      {
        std::cout << ".";
      }
      else
      {
        std::cout << std::endl;
      }
    }

    // IP Destino.
    std::cout << "· IP Destino: ";
    for (int i = 30; i < 34; i++)
    {
      std::cout << static_cast<int>(pkt_data[i]);
      if (i < 33)
      {
        std::cout << ".";
      }
      else
      {
        std::cout << std::endl;
      }
    }

    // Imprimir fin del Paquete IP:
    std::cout << "--- Fin de Paquete IP ---" << std::endl;

    // Armado de Pseudo-Encabezado

    // IP Origen.
    pseudo_ip[0] = pkt_data[26];
    pseudo_ip[1] = pkt_data[27];
    pseudo_ip[2] = pkt_data[28];
    pseudo_ip[3] = pkt_data[29];

    // IP Destino.
    pseudo_ip[4] = pkt_data[30];
    pseudo_ip[5] = pkt_data[31];
    pseudo_ip[6] = pkt_data[32];
    pseudo_ip[7] = pkt_data[33];

    // Reservado.
    pseudo_ip[8] = 0;

    // Protocolo.
    pseudo_ip[9] = pkt_data[23];

    // Longitud (Encabezado + Datos).
    pseudo_ip[10] = ipDataSize >> 8;
    pseudo_ip[11] = ipDataSize & 0XFF;

    // Análisis de Protocolos
    if (protocolo == 1) // ICMP
    {
      // Aumentar contador.
      capture_statistics.icmp_packets++;

      std::cout << "---Análisis ICMP---" << std::endl;

      std::cout << "· Tipo: ";
      print_hex(pkt_data[34]);
      std::cout << std::endl;
      int type = static_cast<int>(pkt_data[34]);
      std::cout << "· Tipo (decimal): " << type << std::endl;

      std::cout << "· Código: ";
      print_hex(pkt_data[35]);
      std::cout << std::endl;
      int code = static_cast<int>(pkt_data[35]);
      std::cout << "· Código (decimal): " << code << std::endl;

      // Variable para almacenar el mensaje de control.
      std::string message;

      if (type == 0)
      {
        message = "Echo reply (used to ping).";
      }
      else if (type == 3)
      {
        switch (code)
        {
        case 0:
          message = "Destination network unreachable";
          break;
        case 1:
          message = "Destination host unreachable";
          break;
        case 2:
          message = "Destination protocol unreachable";
          break;
        case 3:
          message = "Destination port unreachable";
          break;
        case 4:
          message = "Fragmentation required, and DF flag set";
          break;
        case 5:
          message = "Source route failed";
          break;
        case 6:
          message = "Destination network unknown";
          break;
        case 7:
          message = "Destination host unknown";
          break;
        case 8:
          message = "Source host isolated";
          break;
        case 9:
          message = "Network administratively prohibited";
          break;
        case 10:
          message = "Host administratively prohibited";
          break;
        case 11:
          message = "Network unreachable for ToS";
          break;
        case 12:
          message = "Host unreachable for ToS";
          break;
        case 13:
          message = "Communication administratively prohibited";
          break;
        case 14:
          message = "Host precedence violation";
          break;
        default:
          message = "Precedence cutoff in effect";
          break;
        }
      }
      else if (type == 4)
      {
        message = "Source quench (congestion control)";
      }
      else if (type == 5)
      {
        switch (code)
        {
        case 0:
          message = "Redirect Datagram for the Network";
          break;
        case 1:
          message = "Redirect Datagram for the Host";
          break;
        case 2:
          message = "Redirect Datagram for the ToS & network";
          break;
        default:
          message = "Redirect Datagram for the ToS & host";
          break;
        }
      }
      else if (type == 6)
      {
        message = "Alternate Host Address";
      }
      else if (type == 8)
      {
        message = "Echo request (used to ping)";
      }
      else if (type == 9)
      {
        message = "Router Advertisement";
      }
      else if (type == 10)
      {
        message = "Router discovery/selection/solicitation";
      }
      else if (type == 11)
      {
        if (code == 0)
        {
          message = "TTL expired in transit";
        }
        else
        {
          message = "Fragment reassembly time exceeded";
        }
      }
      else if (type == 12)
      {
        if (code == 0)
        {
          message = "Pointer indicates the error";
        }
        else if (code == 1)
        {
          message = "Missing a required option";
        }
        else
        {
          message = "Bad length";
        }
      }
      else if (type == 13)
      {
        message = "Timestamp";
      }
      else if (type == 14)
      {
        message = "Timestamp Reply";
      }
      else if (type == 15)
      {
        message = "Information Request";
      }
      else if (type == 16)
      {
        message = "Information Reply";
      }
      else if (type == 17)
      {
        message = "Address Mask Request";
      }
      else if (type == 18)
      {
        message = "Address Mask Reply";
      }
      else if (type == 40)
      {
        message = "Photuris, Security failures";
      }
      else if (type == 42)
      {
        message = "Extended echo request";
      }
      else if (type == 42)
      {
        switch (code)
        {
        case 0:
          message = "No error";
          break;
        case 1:
          message = "Malformed query";
          break;
        case 2:
          message = "No such interface";
          break;
        case 3:
          message = "No such table entry";
          break;
        default:
          message = "Multiple interfaces satisfy query";
          break;
        }
      }
      else
      {
        message = "La combinación de tipo + código no arrojó ningún resultado. Puede que esté deprecada, sea experimental o sin asignar.";
      }

      std::cout << "· Mensaje de control: " << message << std::endl;

      std::cout
          << "· Checksum: ";
      print_hex(pkt_data[36]);
      print_hex(pkt_data[37]);
      std::cout << std::endl;

      std::cout << "---Fin de Análisis de ICMP---" << std::endl;
    }
    else if (protocolo == 6) // TCP
    {
      // Aumentar contador.
      capture_statistics.tcp_packets++;

      std::cout << "---Análisis TCP ---" << std::endl;
      // Puerto de Origen.
      std::cout << "· Puerto Origen: " << ((pkt_data[34] * 256) + pkt_data[35]) << std::endl;

      // Puerto de Destino.
      std::cout << "· Puerto Destino: " << ((pkt_data[36] * 256) + pkt_data[37]) << std::endl;

      // Longitud de encabezado TCP.
      std::cout << "· Longitud de Encabezado: " << static_cast<int>(pkt_data[46] & 0XF0)
                << " bits = " << ((pkt_data[46] & 0XF0) / 8)
                << " bytes." << std::endl;

      // Banderas TCP.
      std::cout << "· Banderas TCP:" << std::endl
                << "  ¬ NS: " << (((pkt_data[46] >> 7) & 1) ? "Activa" : "Inactiva")
                << "." << std::endl
                << "  ¬ CWR: " << ((pkt_data[47] & 1) ? "Activa" : "Inactiva")
                << "." << std::endl
                << "  ¬ ECE: " << (((pkt_data[47] >> 1) & 1) ? "Activa" : "Inactiva")
                << "." << std::endl
                << "  ¬ URG: " << (((pkt_data[47] >> 2) & 1) ? "Activa" : "Inactiva")
                << "." << std::endl
                << "  ¬ ACK: " << (((pkt_data[47] >> 3) & 1) ? "Activa" : "Inactiva")
                << "." << std::endl
                << "  ¬ PSH: " << (((pkt_data[47] >> 4) & 1) ? "Activa" : "Inactiva")
                << "." << std::endl
                << "  ¬ RST: " << (((pkt_data[47] >> 5) & 1) ? "Activa" : "Inactiva")
                << "." << std::endl
                << "  ¬ SYN: " << (((pkt_data[47] >> 6) & 1) ? "Activa" : "Inactiva")
                << "." << std::endl
                << "  ¬ FIN: " << (((pkt_data[47] >> 7) & 1) ? "Activa" : "Inactiva")
                << "." << std::endl;

      // Checksum
      std::cout << "· Checksum de TCP: ";
      print_hex(pkt_data[50]);
      print_hex(pkt_data[51]);
      std::cout << std::endl;

      // Análisis de Checksum de TCP.

      // Armado de pseudo-encabezado de TCP.
      unsigned char pseudo_tcp[ipDataSize + 12];
      memcpy(pseudo_tcp, pseudo_ip, 12);
      memcpy(&pseudo_tcp[12], &pkt_data[34], ipDataSize);

      // Imprimir Pseudo Encabezado TCP.
      std::cout << "· Pseudo Encabezado TCP:" << std::endl;
      // IP Origen 0 - 4.
      std::cout << "  ~ IP Origen: ";
      for (int i = 0; i < 4; i++)
      {
        std::cout << static_cast<int>(pseudo_tcp[i]);
        if (i < 3)
        {
          std::cout << ".";
        }
        else
        {
          std::cout << std::endl;
        }
      }

      // IP Destino.
      std::cout << "  ~ IP Destino: ";
      for (int i = 4; i < 8; i++)
      {
        std::cout << static_cast<int>(pseudo_tcp[i]);
        if (i < 7)
        {
          std::cout << ".";
        }
        else
        {
          std::cout << std::endl;
        }
      }

      // Reservado
      std::cout << "  ~ Reservado: " << static_cast<int>(pseudo_tcp[8]) << std::endl;

      // Protocolo
      std::cout << "  ~ Protocolo (Encabezado IP): " << static_cast<int>(pseudo_tcp[9]) << std::endl;

      // Longitud de PDU
      std::cout << "  ~ Longitud de PDU: " << ((pseudo_tcp[10] * 256) + pseudo_tcp[11]) << std::endl;

      // Validación de Checksum.
      unsigned int tcp_checksum_result = calculateChecksum(pseudo_tcp, ipDataSize + 12);

      std::cout << "· ¿Checksum TCP correcto? " << (tcp_checksum_result == 0 ? "Sí" : "No") << "." << std::endl;
      std::cout << "· Valor Checksum: " << tcp_checksum_result << std::endl;

      // En caso de ser erróneo, corregirlo.
      if (tcp_checksum_result != 0)
      {
        // Colocar Checksum TCP en 0.
        memcpy(&pseudo_tcp[28], "00", 2);
        // Imprimir el resultado.
        std::cout << "· Checksum TCP Corregido: " << calculateChecksum(pseudo_tcp, ipDataSize + 12) << std::endl;
      }

      std::cout << "--- Fin de Análisis TCP ---" << std::endl;
    }
    else if (protocolo == 17) // UDP
    {
      // Aumentar contador.
      capture_statistics.udp_packets++;

      std::cout << "--- Análisis UDP ---" << std::endl;

      // Puerto origen.
      std::cout << "· Puerto Origen: " << ((pkt_data[34] * 256) + pkt_data[35]) << std::endl;

      // Puerto destino.
      std::cout << "· Puerto Destino: " << ((pkt_data[36] * 256) + pkt_data[37]) << std::endl;

      // Longitud.
      std::cout << "· Longitud: " << ((pkt_data[38] * 256) + pkt_data[39]) << std::endl;

      // Checksum.
      std::cout << "· Checksum: ";
      print_hex(pkt_data[40]);
      print_hex(pkt_data[41]);
      std::cout << std::endl;

      // Análisis de Checksum de UDP.

      // Armado de pseudo-encabezado de UDP.
      unsigned char pseudo_udp[ipDataSize + 12];
      memcpy(pseudo_udp, pseudo_ip, 12);
      memcpy(pseudo_udp + 12, &pkt_data[34], ipDataSize);

      // Imprimir Pseudo Encabezado TCP.
      std::cout << "· Pseudo Encabezado UDP:" << std::endl;
      // IP Origen 0 - 4.
      std::cout << "  ~ IP Origen: ";
      for (int i = 0; i < 4; i++)
      {
        std::cout << static_cast<int>(pseudo_udp[i]);
        if (i < 3)
        {
          std::cout << ".";
        }
        else
        {
          std::cout << std::endl;
        }
      }

      // IP Destino.
      std::cout << "  ~ IP Destino: ";
      for (int i = 4; i < 8; i++)
      {
        std::cout << static_cast<int>(pseudo_udp[i]);
        if (i < 7)
        {
          std::cout << ".";
        }
        else
        {
          std::cout << std::endl;
        }
      }

      // Reservado
      std::cout << "  ~ Reservado: " << static_cast<int>(pseudo_udp[8]) << std::endl;

      // Protocolo
      std::cout << "  ~ Protocolo (Encabezado IP): " << static_cast<int>(pseudo_udp[9]) << std::endl;

      // Longitud de PDU
      std::cout << "  ~ Longitud de PDU: " << ((pseudo_udp[10] * 256) + pseudo_udp[11]) << std::endl;

      // Validación de Checksum.
      unsigned int udp_checksum_result = calculateChecksum(pseudo_udp, ipDataSize + 12);

      std::cout << "· ¿Checksum UDP correcto? " << (udp_checksum_result == 0 ? "Sí" : "No") << "." << std::endl;

      // En caso de ser erróneo, corregirlo.
      if (udp_checksum_result != 0)
      {
        // Colocar en 0 el checksum de UDP.
        memcpy(&pseudo_udp[18], "00", 2);
        // Imprimir el resultado.
        std::cout << "· Checksum UDP Corregido: " << calculateChecksum(pseudo_udp, ipDataSize + 12) << std::endl;
      }

      std::cout << "--- Fin de Análisis UDP ---" << std::endl;
    }
    else // Otro
    {
      std::cout << "· El protocolo no es ICMP, TCP ni UDP" << std::endl;
    }
  }
  else
  {
    capture_statistics.non_ip_packets++;
  }

  // Aumentar el contador de paquetes.
  capture_statistics.total_packets++;

  // Si se activó guardar paquetes, hacerlo ahora.
  if (global_configuration.save_to_file)
  {
    // Informar al usuario.
    std::cout << "· Paquete guardado en: " << global_configuration.out_filename << std::endl;

    // Dumpear paquete (escribir, pues).
    pcap_dump((u_char *)global_configuration.dumper, header, pkt_data);
  }

  // Imprimir fin del Paquete capturado.
  std::cout << "****************** FIN DE PAQUETE *******************" << std::endl
            << std::endl;
}

/**
 * Calcular el Checksum.
 */
unsigned int calculateChecksum(const unsigned char *buf, int length)
{
  int i = 0;

  int sum = 0; //long
  int data;    //long

  // Handle all pairs
  while (length > 1)
  {

    data = (((buf[i] << 8) & 0xFF00) | ((buf[i + 1]) & 0xFF));
    sum += data;
    // 1's complement carry bit correction in 16-bits (detecting sign extension)
    if ((sum & 0xFFFF0000) > 0)
    {
      sum = sum & 0xFFFF;
      sum += 1;
    }

    i += 2;
    length -= 2;
  }

  // Handle remaining byte in odd length buffers
  if (length > 0)
  {
    sum += (buf[i] << 8 & 0xFF00);
    if ((sum & 0xFFFF0000) > 0)
    {
      sum = sum & 0xFFFF;
      sum += 1;
    }
  }

  // Final 1's complement value correction to 16-bits
  sum = ~sum;
  sum = sum & 0xFFFF;
  return sum;
}
