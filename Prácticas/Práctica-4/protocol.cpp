#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <thread>
#include <random>
#include <algorithm>
#include <pcap.h>
#include <mutex>

// ID_LENGTH
#ifndef ID_LENGTH
#define ID_LENGTH 8
#endif

// Mutexes

// Typedef de char_array.
typedef std::vector<char> char_array;

// Prototipo de función que regresa un set de caracteres.
char_array charset();

// Prototipo de función para generación de strings aleatorios.
std::string random_string(size_t, std::function<char(void)>);

// Prototipo de función para escuchar archivos entrantes.
void listen_data(pcap_if_t *, std::string);

// Función principal.
int main(int argc, char **argv)
{
  // Variables locales.
  pcap_t *fp;
  pcap_t *adhandle;
  pcap_if_t *d;
  pcap_if_t *alldevs;
  u_char packet[100];
  char errbuf[PCAP_ERRBUF_SIZE];
  int i;
  int inum;

  // Set de caracteres a usar para el ID.
  const auto ch_set = charset();

  // Crear un generador de números aleatorios no-determinístico.
  std::default_random_engine rng(std::random_device{}());

  // Crear un "modelador" de números aleatorios que nos dará
  // indices uniformemente distribuidos en el set de caracteres.
  std::uniform_int_distribution<> dist(0, ch_set.size() - 1);

  // Crear una función que los une, para obtener una distribución uniforme
  // no-determinística del set de caracteres de elección.
  auto randchar = [ch_set, &dist, &rng]() { return ch_set[dist(rng)]; };

  // Generar el ID de longitud pre-establecida.
  std::string id = random_string(ID_LENGTH, randchar);

  // Print the ID.
  std::cout << "*******************************" << std::endl;
  std::cout << "| ID de este equipo: " << id << " |" << std::endl;
  std::cout << "*******************************" << std::endl;

  // Obtener la lista de dispositivos.
  if (pcap_findalldevs(&alldevs, errbuf) == -1)
  {
    std::cerr << "Error in pcap_findalldevs: " << errbuf << std::endl;
    return -1;
  }

  // Imprimir la lista.
  std::cout << "Lista de dispositivos disponibles:" << std::endl;
  for (d = alldevs, i = 0; d; d = d->next, ++i)
  {
    std::cout << i << ") " << d->name;
    if (d->description)
    {

      std::cout << " (" << d->description << ")" << std::endl;
    }
    else
    {

      std::cout << " (Sin descripción)." << std::endl;
    }
  }

  if (i == 0)
  {
    std::cerr << "¡No se encontraron interfaces! Asegúrese de tener todo instalado e intente de nuevo más tarde." << std::endl;
    return -1;
  }

  do
  {
    std::cout << "Ingrese el número de la interfaz a usar (1-" << i << "): ";
    std::cin >> inum;
  } while (inum < 1 || inum > i);

  // Saltar al adaptador que buscamos.
  for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++)
    ;

  // Iniciar hilo de escucha.
  std::thread(listen_data, d, id).detach();

  /* Open the output device */
  if ((fp = (pcap_t *)pcap_open_live(d->name, // name of the device  //argv[1]
                                     100,     // portion of the packet to capture (only the first 100 bytes)
                                     1,       //PCAP_OPENFLAG_PROMISCUOUS,  // promiscuous mode
                                     1000,    // read timeout
                                     errbuf   // error buffer
                                     )) == NULL)
  {
    fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", argv[1]);
    return -1;
  }

  /* Supposing to be on ethernet, set mac destination to 1:1:1:1:1:1 */
  packet[0] = 1;
  packet[1] = 1;
  packet[2] = 1;
  packet[3] = 1;
  packet[4] = 1;
  packet[5] = 1;

  /* set mac source to 2:2:2:2:2:2 */
  packet[6] = 2;
  packet[7] = 2;
  packet[8] = 2;
  packet[9] = 2;
  packet[10] = 2;
  packet[11] = 2;

  /* Fill the rest of the packet */
  for (i = 12; i < 100; i++)
  {
    packet[i] = i % 256;
  }

  packet[12] = 0x16;
  packet[13] = 0x01;

  /* Send down the packet */
  if (pcap_sendpacket(fp, packet, 100) != 0)
  {
    fprintf(stderr, "\nError sending the packet: %s\n", pcap_geterr(fp));
    return -1;
  }

  return 0;
}

/**
 * The Charset to be used for ID generation.
 */
char_array charset()
{
  return char_array(
      {'0', '1', '2', '3', '4',
       '5', '6', '7', '8', '9',
       'A', 'B', 'C', 'D', 'E', 'F',
       'G', 'H', 'I', 'J', 'K',
       'L', 'M', 'N', 'O', 'P',
       'Q', 'R', 'S', 'T', 'U',
       'V', 'W', 'X', 'Y', 'Z',
       'a', 'b', 'c', 'd', 'e', 'f',
       'g', 'h', 'i', 'j', 'k',
       'l', 'm', 'n', 'o', 'p',
       'q', 'r', 's', 't', 'u',
       'v', 'w', 'x', 'y', 'z'});
};

/**
 * Function to generate a random string of fixed length.
 */
std::string random_string(size_t length, std::function<char(void)> rand_char)
{
  std::string str(length, 0);
  std::generate_n(str.begin(), length, rand_char);
  return str;
}

// Listener thread function prototype.
void listen_data(pcap_if_t *d, std::string id)
{
  std::cout << "ID: " << id << std::endl;
  std::cout << "Nombre: " << d->name << std::endl;
}