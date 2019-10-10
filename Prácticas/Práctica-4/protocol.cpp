#include <iostream>
#include <thread>
#include <random>
#include <algorithm>
#include <mutex>
#include <fstream>
#include <pcap.h>

// ID_LENGTH
#ifndef ID_LENGTH
#define ID_LENGTH 8
#endif

/**
 * Estas funciones generan un modo de impresión segura para
 * arquitecturas multi-hilo.
 */

std::ostream &
print_one(std::ostream &os)
{
  return os;
}

template <class A0, class... Args>
std::ostream &
print_one(std::ostream &os, const A0 &a0, const Args &... args)
{
  os << a0;
  return print_one(os, args...);
}

template <class... Args>
std::ostream &
print(std::ostream &os, const Args &... args)
{
  return print_one(os, args...);
}

std::mutex &
get_cout_mutex()
{
  static std::mutex m;
  return m;
}

template <class... Args>
std::ostream &
print(const Args &... args)
{
  std::lock_guard<std::mutex> _(get_cout_mutex());
  return print(std::cout, args...);
}

// Prototipo de función para imprimir de forma segura (multi-hilo)
void safe_print(std::string);

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
  pcap_t *fp;                    // El handle del dispositivo a usar para operaciones de captura y escucha.
  pcap_if_t *d;                  // El dispositivo a usar.
  pcap_if_t *alldevs;            // Todos los dispositivos de captura detectados.
  u_char packet[100];            // El paquete a enviar.
  char errbuf[PCAP_ERRBUF_SIZE]; // Buffer para mensajes de error.
  int i;                         // Variable para operaciones de ciclos.
  int inum;                      // Variable con el número de la interfaz a usar.
  std::string filename;          // El nombre del archivo a enviar.
  std::ifstream file;            // El archivo a leer.

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
  for (d = alldevs, i = 0; d; d = d->next)
  {
    std::cout << ++i << ") " << d->name;
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

  // Abrir dispositivo de red.
  if ((fp = (pcap_t *)pcap_open_live(d->name, // Nombre del dispositivo.
                                     1000,    // Porción del paquete a capturar (solo los primeros 100 bytes)
                                     1,       // Modo promiscuo.
                                     1000,    // Timeout de lectura.
                                     errbuf   // Buffer para almacenar errores.
                                     )) == NULL)
  {
    std::cerr << "Ha sido imposible abrir el adaptador de red, error: " << errbuf << std::endl;
    return -1;
  }

  /**
   * Hasta este punto, usamos std::cout porque no habíamos iniciado otra operación
   * multi-hilo. A partir de aquí, usamos la función print() que es segura en este
   * contexto de operaciones multi-hilo.
   */

  // Iniciar hilo de escucha.
  std::thread(listen_data, std::ref(fp), id).detach();

  // Informar al usuario.
  print("Escuchando paquetes enviados a este dispositivo con el ID: ", id, " .\n");
  print("A partir de este momento, cualquier paquete recibido será procesado y almacenado\n");
  print("en caso de ser dirigido a este dispositivo.\n");
  print("(Se informará sobre segmentos recibidos)\n");

  // Preguntar al usuario por el nombre del archivo a enviar.
  print("Escriba el nombre del archivo a enviar: ");
  std::cin >> filename;

  // Confirmar el nombre del archivo con el usuario.
  print("Se leerá el archivo: ", filename, "\n");

  // Leer archivo.
  file.open(filename, std::ios::in | std::ios::binary | std::ios::ate);
  if (!file.is_open())
  {
    print("Ha ocurrido un error abriendo el archivo. Verifique la información e inténtalo más tarde.\n");
    return -1;
  }

  // Obtenemos el tamaño del archivo.
  file.seekg(0, std::ios::end);

  print("El archivo mide: ", file.tellg(), " bytes.\n");

  // Iniciamos en el primer elemento del archivo.
  file.seekg(0, std::ios::beg);

  // Dividir el archivo en pedazos.

  // Enviar cada pedazo y esperar confirmación.

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
 * El conjunto de caracteres a usar para la generación del ID.
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
 * Función que genera un string aleatorio.
 */
std::string random_string(size_t length, std::function<char(void)> rand_char)
{
  std::string str(length, 0);
  std::generate_n(str.begin(), length, rand_char);
  return str;
}

/**
 * Función que escucha en el dispositivo especificado para captura y realiza
 * el guardado de los segmentos del archivo enviado.
 */
void listen_data(pcap_if_t *d, std::string id)
{
  print("ID: ", id, '\n');
  print("Nombre: ", d->name, '\n');

  // Compilar filtro

  // setear filtro

  // abrir captura infinita
}