#include <iostream>
#include <iomanip>
#include <pcap.h>

/* 4 bytes IP address */
typedef struct ip_address
{
  u_char byte1;
  u_char byte2;
  u_char byte3;
  u_char byte4;
} ip_address;

/* IPv4 header */
typedef struct ip_header
{
  u_char ver_ihl;         // Version (4 bits) + Internet header length (4 bits)
  u_char tos;             // Type of service
  u_short tlen;           // Total length
  u_short identification; // Identification
  u_short flags_fo;       // Flags (3 bits) + Fragment offset (13 bits)
  u_char ttl;             // Time to live
  u_char proto;           // Protocol
  u_short crc;            // Header checksum
  ip_address saddr;       // Source address
  ip_address daddr;       // Destination address
  u_int op_pad;           // Option + Padding
} ip_header;

/* UDP header*/
typedef struct udp_header
{
  u_short sport; // Source port
  u_short dport; // Destination port
  u_short len;   // Datagram length
  u_short crc;   // Checksum
} udp_header;

/**
 * Prototipo de función para analizar paquetes.
 */
void packet_handler(unsigned char *param, const struct pcap_pkthdr *header, const unsigned char *pkt_data);

/**
 * Función para imprimir números decimales adecuadamente.
 */
void print_hex(unsigned char byte)
{
  std::cout << std::setw(2) << std::setfill('0') << std::hex
            << static_cast<int>(byte)
            << std::dec << std::setw(1);
}

/**
 * Función principal.
 */
int main(int argc, char const *argv[])
{
  // Variables.
  pcap_if_t *alldevs; // Todas las tarjetas de red.
  pcap_if_t *d;       // La tarjeta de red a usar.
  pcap_t *adhandle;

  int inum, i; // Contadores.

  char errbuf[PCAP_ERRBUF_SIZE]; // Buffer para errores.

  // Título de programa.
  std::cout << "Programa para calcular Checksum" << std::endl
            << std::endl;

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

  // Abrir el dispositivo y el adaptador.
  if ((adhandle = pcap_open_live(d->name, // Nombre del dispositivo.
                                 65536,   // Porción del paquete (65536 es el máximo tamaño).
                                 1,       // Modo promiscuo.
                                 1000,    // Timeout de lectura.
                                 errbuf   // Buffer de error.
                                 )) == NULL)
  {
    std::cerr << "No fue posible abrir el adaptador." << std::endl;
    std::cerr << "Probablemente haya un error con: " << d->name << std::endl;
    pcap_freealldevs(alldevs); // Liberar la memoria de los dispositivos.
    return -1;                 // Error.
  }

  // Informar al usuario que se inicia la captura.
  std::cout << "Escuchando en: " << (d->description ? d->description : d->name) << std::endl;

  // En este punto, no se requiere más de la lista de dispositivos, liberarla.
  pcap_freealldevs(alldevs);

  // Comenzar la captura.
  pcap_loop(adhandle, 15, packet_handler, NULL);

  // Finalizar la captura.
  pcap_close(adhandle);

  // Mensaje de despedida.
  std::cout << "La captura ha terminado." << std::endl
            << std::endl;
  std::cout << "Humberto Alcocer 2019" << std::endl;
  return 0;
}

/**
 * Función de Callback para analizar cada paquete.
 */
void packet_handler(unsigned char *param, const struct pcap_pkthdr *header, const unsigned char *pkt_data)
{
  // Variables.
  struct tm *ltime;
  char timestr[16];
  time_t local_tv_sec;

  // Parámetros sin utilizar.
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
  // Trama Ethernet.
  std::cout << "--- Trama Ethernet ---" << std::endl;

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

  // Fin de análisis de Trama Ethernet.
  std::cout << "--- Fin Trama Ethernet ---" << std::endl;

  // Tipo de paquete en capa de Red.
  unsigned short tipo = (pkt_data[12] * 256) + pkt_data[13];

  // Imprimir resultados.
  std::cout << "Tipo de Paquete: " << tipo << std::endl;

  std::cout << "Byte 12: ";
  print_hex(pkt_data[12]);
  std::cout << std::endl;
  std::cout << "Byte 13: ";
  print_hex(pkt_data[13]);
  std::cout << std::endl;

  // Informar si es un paquete IP.
  std::cout << "¿Es un paquete IP? " << (tipo == 2048 ? "Sí" : "No")
            << "." << std::endl;

  // Analizar IP.
  if (tipo == 2048)
  {
    std::cout << "--- Paquete IP ---" << std::endl;
    ip_header *ih;
    // Obtener la posición del paquete IP.
    ih = (ip_header *)(pkt_data + 14); // Longitud del encabezado de IP.
    // Direcciones IP origen y destino.
    printf("%d.%d.%d.%d -> %d.%d.%d.%d\n",
           ih->saddr.byte1,
           ih->saddr.byte2,
           ih->saddr.byte3,
           ih->saddr.byte4,
           ih->daddr.byte1,
           ih->daddr.byte2,
           ih->daddr.byte3,
           ih->daddr.byte4);
    // Imprimir fin del Paquete IP:
    std::cout << "--- Fin de Paquete IP ---" << std::endl;
  }
  // Imprimir fin del Paquete capturado.
  std::cout << "****************** FIN DE PAQUETE *******************" << std::endl
            << std::endl;
}
