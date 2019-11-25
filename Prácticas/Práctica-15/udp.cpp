/**
 * Práctica 15
 * Analizar UDP.
 * Humberto Alcocer, 2019
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <pcap.h>

#ifndef MAX_PACKETS
#define MAX_PACKETS 100
#endif // MAX_PACKETS

// Estructura de una dirección IP.
typedef struct ip_addr
{
  unsigned char byte1;
  unsigned char byte2;
  unsigned char byte3;
  unsigned char byte4;
} ip_addr;

// Estructura de encabezado IP.
typedef struct iph
{
  unsigned char ver_ihl;
  unsigned char sdif;
  unsigned short tlen;
  unsigned short id;
  unsigned short t_off;
  unsigned char ttl;
  unsigned char proto;
  unsigned short checksum;
  ip_addr s_ip;
  ip_addr d_ip;
  unsigned int op_pad;
} iph;

// Estructura de encabezado UDP.
typedef struct udph
{
  unsigned short sport;
  unsigned short dport;
  unsigned short len;
  unsigned short checksum;
} udph;

// Prototipo de función para análisis de paquetes IP.
void udp_packet_handler(unsigned char *, const struct pcap_pkthdr *, const unsigned char *);

// Prototipo de función para imprimir valores en hexadecimal.
void print_hex(unsigned char);

// Prototipo de función para imprimir una dirección IP.
void print_ip_addr(ip_addr);

// Función principal.
int main(int argc, char *argv[])
{
  pcap_if_t *alldevs;            // Todas las tarjetas de red.
  pcap_if_t *dev;                // Tarjeta de red a usar.
  pcap_t *ad_handle;             // Handler de la tarjeta a usar.
  char errbuf[PCAP_ERRBUF_SIZE]; // Buffer para mensajes de error.
  int number_of_packets;         // Número de paquetes a capturar.
  struct bpf_program fp;         // Filtro de captura compilado.
  bpf_u_int32 pMask;             // Máscara de Subred
  bpf_u_int32 pNet;              // Dirección IP.

  // Inicio de programa.
  std::cout << "Práctica 15" << std::endl;
  std::cout << "Analizador de UDP" << std::endl;

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

  // Obtener la dirección IP y máscara de subred.
  pcap_lookupnet(dev->name, &pNet, &pMask, errbuf);

  // Compilar filtro de captura.
  if (pcap_compile(ad_handle, &fp, "udp", 0, pNet) == -1)
  {
    std::cerr << "Error compilando filtro de captura." << std::endl;
    return -1;
  }

  // Colocar filtro de captura.
  if (pcap_setfilter(ad_handle, &fp) == -1)
  {
    std::cerr << "Error al asignar filtro de captura." << std::endl;
    exit(1);
  }

  // Para este punto, no requerimos más la lista completa de dispositivos. Liberarla.
  pcap_freealldevs(alldevs);

  // Realizar la captura.
  pcap_loop(ad_handle, number_of_packets, &udp_packet_handler, NULL);

  // Informar sobre fin de programa.
  std::cout << "Fin de programa" << std::endl;
  std::cout << " - Humberto Alcocer, 2019" << std::endl;
  std::cout << "ESCOM. Redes de Computadoras. Práctica 15" << std::endl;

  // Fin de programa.
  return 0;
}

// Implementación de función de análisis de paquetes IP.
void udp_packet_handler(unsigned char *param, const struct pcap_pkthdr *header, const unsigned char *pkt_data)
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
  unsigned int type = (pkt_data[12] * 256) + pkt_data[13];

  std::cout << "· Ether Type: " << type << std::endl;

  // Validar que sea paquete IP:
  if (type == 2048)
  {
    // Imprimir información.
    std::cout << "· El paquete es IP." << std::endl;

    // Castear a la estructura.
    iph *ip = (iph *)(pkt_data + 14);

    std::cout << "· Protocolo: " << static_cast<unsigned>(ip->proto) << std::endl;

    if (ip->proto == 17)
    {
      // Extraer longitud de hlen.
      unsigned char hlen = ((ip->ver_ihl) & 0x0f) * 4;

      std::cout << "· Longitud de paquete IP (hlen): " << static_cast<unsigned>(hlen) << std::endl;

      // Informar de análisis.
      std::cout << "· Análisis de UDP:" << std::endl;

      // Analizar UDP.
      udph *udp = (udph *)(pkt_data + 14 + hlen);

      // Puerto de Origen.
      std::cout << "  ~ Puerto de Origen: " << udp->sport << std::endl;

      // Puerto de Destino.
      std::cout << "  ~ Puerto de Destino: " << udp->dport << std::endl;

      // Longitud.
      std::cout << "  ~ Longitud: " << udp->len << std::endl;
    }
    else
    {
      std::cout << "· El paquete IP no contiene un paquete UDP." << std::endl;
    }
  }
  else
  {
    std::cout << "· El paquete NO es IP." << std::endl;
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

// Implementación de función para imprimir un ip_addr.
void print_ip_addr(ip_addr ip)
{
  std::cout << static_cast<unsigned>(ip.byte1) << "."
            << static_cast<unsigned>(ip.byte2) << "."
            << static_cast<unsigned>(ip.byte3) << "."
            << static_cast<unsigned>(ip.byte4);
}