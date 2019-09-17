/**
 * Práctica 4.1
 * Analizar el encabezado de ARP
 * Humberto Alcocer, 2019
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <pcap.h>

#ifndef MAX_PACKETS
#define MAX_PACKETS 100
#endif // MAX_PACKETS

int number_packets = 0;

// Prototipo de función para análisis de paquetes ARP.
void arp_packet_handler(unsigned char *, const struct pcap_pkthdr *, const unsigned char *);

// Prototipo de función para imprimir valores en hexadecimal.
void print_hex(unsigned char);

// Función principal.
int main(int argc, char *argv[])
{
  pcap_if_t *alldevs;            // Todas las tarjetas de red.
  pcap_if_t *dev;                // Tarjeta de red a usar.
  pcap_t *ad_handle;             // Handler de la tarjeta a usar.
  char errbuf[PCAP_ERRBUF_SIZE]; // Buffer para mensajes de error.
  int number_of_packets;         // Número de paquetes a capturar.

  // Inicio de programa.
  std::cout << "Práctica 4.1" << std::endl;
  std::cout << "Analizador de ARP" << std::endl;

  // Obtener la lista de dispositivos.
  if (pcap_findalldevs(&alldevs, errbuf) == -1)
  {
    std::cerr << "Error encontrando dispositivos: " << errbuf << std::endl;
    return -1;
  }

  // Ciclo para control de entradas erróneas.
  int option = -1,
      i = 0;
  do
  {
    // Informar al usuario acerca del siguiente proceso.
    std::cout << "Seleccione una interfaz de red de la siguiente lista:" << std::endl;

    // Imprimir la lista de interfaces disponibles.
    for (dev = alldevs, i = 0; dev; dev = dev->next, ++i)
    {
      std::cout << (i + 1) << ") " << dev->name << std::endl;
    }

    // Validar que se haya detectado, al menos, una interfaz de red.
    if (i == 0)
    {
      std::cout << "¡No se ha podido detectar ninguna interfaz de red!" << std::endl;
      std::cout << "Asegúrate de que los drivers estén bien instalados" << std::endl;
      return -1;
    }

    // Preguntar a usuario por la interfaz de red seleccionada.
    std::cout << "Ingresa el número de la interfaz de red (1-" << i << "): ";

    // Leer dato.
    std::cin >> option;
  } while (option < 1 || option > i);

  // Saltar a la interfaz seleccionada.
  for (dev = alldevs, i = 1; i < option; dev = dev->next, i++)
    ;

  // Abrir dispositivo de captura.
  if ((ad_handle = pcap_open_live(dev->name, 65535, true, 1000, errbuf)) == NULL)
  {
    std::cerr << "No fue posible abrir el adaptador: " << dev->name << std::endl;
    pcap_freealldevs(alldevs); // Liberar memoria.
    return -1;                 // Regresar error.
  }

  // Preguntar al usuario por el número de paquetes a capturar.
  do
  {
    std::cout << "¿Cuántos paquetes deseas capturar? (1-" << MAX_PACKETS << "): ";
    std::cin >> number_of_packets;
  } while (number_of_packets < 1 || number_of_packets > MAX_PACKETS);

  // Informar al usuario que inicia la captura.
  std::cout << "Iniciando captura..." << std::endl;
  std::cout << "Leyendo " << number_of_packets << " desde " << dev->name << std::endl
            << std::endl;

  // Para este punto, no requerimos más la lista completa de dispositivos. Liberarla.
  pcap_freealldevs(alldevs);

  // Realizar la captura.
  pcap_loop(ad_handle, number_of_packets, &arp_packet_handler, NULL);

  // Informar sobre fin de programa.
  std::cout << "Fin de programa" << std::endl;
  std::cout << " - Humberto Alcocer, 2019" << std::endl;
  std::cout << "ESCOM. Redes de Computadoras, práctica 4" << std::endl;

  // Fin de programa.
  return 0;
}

// Implementación de función de análisis de paquetes ARP.
void arp_packet_handler(unsigned char *param, const struct pcap_pkthdr *header, const unsigned char *pkt_data)
{
  std::cout << "------- Paquete Capturado --------" << std::endl;

  // MAC origen en capa de red.
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
  // MAC destino en capa de red.
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

  // Campo tipo.
  unsigned int tipo = (pkt_data[12] * 256) + pkt_data[13];

  if (tipo != 2054)
  {
    std::cout << "- El paquete NO es de tipo ARP." << std::endl;
  }
  else
  {
    std::cout << "- El paquete es de tipo ARP." << std::endl;

    // Campos de ARP.
    unsigned int hw_type = (pkt_data[14] * 256) + pkt_data[15];
    unsigned int protocol_type = (pkt_data[16] * 256) + pkt_data[17];
    unsigned int operation = (pkt_data[20] * 256) + pkt_data[21];

    // Imprimir información de tipo de Hardware.
    std::cout << "  - Tipo Hardware: (" << hw_type << ") ";
    switch (hw_type)
    {
    case 1:
      std::cout << "Ethernet" << std::endl;
      break;
    case 6:
      std::cout << "IEEE 802.x" << std::endl;
      break;

    case 15:
      std::cout << "Frame Relay" << std::endl;
      break;
    case 16:
      std::cout << "ATM" << std::endl;
      break;
    case 17:
      std::cout << "HDLC" << std::endl;
      break;
    default:
      std::cout << "Desconocido" << std::endl;
      break;
    }

    // Imprimir información sobre tipo de protocolo.
    std::cout << "  - Tipo Proto: " << protocol_type << std::endl;

    // Imprimir información sobre longitud de hardware.
    std::cout << "  - Longitud de Hardware: " << std::endl;

    // Imprimir información sobre longitud de protocolo.
    std::cout << "  - Longitud de Protocolo: " << std::endl;

    // Imprimir operación ARP.
    std::cout << "  - Operación ARP: (" << operation << ") ";
    switch (operation)
    {
    case 1:
      std::cout << "Solicitud ARP" << std::endl;
      break;
    case 2:
      std::cout << "Respuesta de ARP" << std::endl;
      break;
    case 3:
      std::cout << "Solicitud RARP" << std::endl;
      break;
    case 4:
      std::cout << "Respuresta de RARP" << std::endl;
      break;
    default:
      std::cout << "Operación desconocida" << std::endl;
      break;
    }
  }

  std::cout << "-------  Fin de Análisis  --------" << std::endl;
}

// Implementación de función para imprimir hexadecimal.
void print_hex(unsigned char byte)
{
  std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex
            << static_cast<int>(byte)
            << std::dec << std::setw(1);
}