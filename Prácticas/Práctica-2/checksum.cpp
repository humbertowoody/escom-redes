#include <iostream>
#include <iomanip>
#include <pcap.h>

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
uint16_t ip_checksum(const void *, size_t);

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
 * Función para imprimir números decimales adecuadamente.
 */
void print_hex(unsigned char byte)
{
  std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex
            << static_cast<int>(byte)
            << std::dec << std::setw(1);
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

  // Ether Type
  std::cout << "· Ether Type: ";
  print_hex(pkt_data[12]);
  print_hex(pkt_data[13]);
  std::cout << std::endl;

  // Tipo de paquete en capa de Red.
  unsigned short tipo = (pkt_data[12] * 256) + pkt_data[13];

  // Imprimir resultados.
  std::cout << "· Tipo de Paquete: " << tipo << std::endl;

  // Informar si es un paquete IP.
  std::cout << "· ¿Es un paquete IP? " << (tipo == 2048 ? "Sí" : "No")
            << "." << std::endl;

  // Fin de análisis de Trama Ethernet.
  std::cout << "--- Fin Trama Ethernet ---" << std::endl;

  // Analizar IP.
  if (tipo == 2048)
  {
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
    case 6:
      std::cout << "TCP";
      break;

    case 17:
      std::cout << "UDP";
      break;

    default:
      std::cout << "No es TCP ni UDP";
      break;
    }
    std::cout << ")" << std::endl;

    // Checksum 24 y 25
    std::cout << "· Checksum: ";
    print_hex(pkt_data[24]);
    print_hex(pkt_data[25]);
    std::cout << std::endl;

    // Análisis de Checksum para IP.
    uint16_t ip_checksum_result = ip_checksum(&pkt_data[14], ((pkt_data[14] & 0X0F) * 4));

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
      std::cout << "· Checksum Corregido: " << ip_checksum((const void *)new_header, ((pkt_data[14] & 0X0F) * 4));
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
    pseudo_ip[10] = ipDataSize & 0XFF;
    pseudo_ip[11] = ipDataSize >> 8;

    // Análisis de Protocolos
    if (protocolo == 6) // TCP
    {
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
      memcpy(pseudo_tcp + 12, &pkt_data[34], ipDataSize);

      // Validación de Checksum.
      uint16_t tcp_checksum_result = ip_checksum(pseudo_tcp, ipDataSize + 12);

      std::cout << "· ¿Checksum TCP correcto? " << (tcp_checksum_result == 0 ? "Sí" : "No") << "." << std::endl;

      // En caso de ser erróneo, corregirlo.
      if (tcp_checksum_result != 0)
      {
        // Nuevo encabezado con Checksum en 0 (puesto que lo vamos a generar).
        unsigned char new_pseudo_header[ipDataSize + 12];
        unsigned char tcp_packet[ipDataSize];

        // Copiar el paquete TCP para limpiar el Checksum.
        memcpy(tcp_packet, &pkt_data[34], ipDataSize);
        // Colocar en 0's el Checksum.
        tcp_packet[16] = tcp_packet[17] = 0;

        // Generar nuevo pseudo encabezado.
        memcpy(new_pseudo_header, pseudo_ip, 12);
        memcpy(new_pseudo_header + 12, tcp_packet, ipDataSize);

        // Imprimir el resultado.
        std::cout << "· Checksum TCP Corregido: " << ip_checksum((const void *)new_pseudo_header, ipDataSize + 12) << std::endl;
      }

      std::cout << "--- Fin de Análisis TCP ---" << std::endl;
    }
    else if (protocolo == 17) // UDP
    {
      std::cout << "--- Análisis UDP ---" << std::endl;

      // Puerto origen.
      std::cout << "· Puerto Origen: " << ((pkt_data[34] * 256) + pkt_data[35]) << std::endl;

      // Puerto destino.
      std::cout << "· Puerto Destino: " << ((pkt_data[36] * 256) + pkt_data[37]) << std::endl;

      // Longitud.
      std::cout << "· Longitud: " << ((pkt_data[37] * 256) + pkt_data[38]) << std::endl;

      // Checksum.
      std::cout << "· Checksum: ";
      print_hex(pkt_data[39]);
      print_hex(pkt_data[40]);
      std::cout << std::endl;

      std::cout << "--- Fin de Análisis UDP ---" << std::endl;
    }
    else // Otro
    {
      std::cout << "· El protocolo no es TCP ni UDP" << std::endl;
    }
  }
  // Imprimir fin del Paquete capturado.
  std::cout << "****************** FIN DE PAQUETE *******************" << std::endl
            << std::endl;
}

/**
 * Calcular el Checksum del encabezado IP.
 */
uint16_t ip_checksum(const void *buf, size_t hdr_len)
{
  unsigned long sum = 0;
  const uint16_t *ip1;

  ip1 = (const uint16_t *)buf;

  while (hdr_len > 1)
  {
    sum += *ip1++;
    if (sum & 0x80000000)
      sum = (sum & 0xFFFF) + (sum >> 16);
    hdr_len -= 2;
  }

  while (sum >> 16)
    sum = (sum & 0xFFFF) + (sum >> 16);

  return (~sum);
}