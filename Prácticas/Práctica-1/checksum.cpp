#include <iostream>
#include <string>
#include <pcap.h>

// Prototype of the Packet Handler.
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

int main(int argc, char const *argv[])
{
  // Variables.
  pcap_if_t *allDevs;
  pcap_if_t *d;

  int i,               // Iterator.
      interfaceNumber; // Variable to store the number of the interface to use.

  char errbuf[PCAP_ERRBUF_SIZE]; // Error buffer.

  // Print title.
  std::cout << "IP Header checksum calculator." << std::endl
            << std::endl;

  // Retrieve device list.
  if (pcap_findalldevs(&allDevs, errbuf) == -1)
  {
    std::cerr << "Couldn't find network devices." << std::endl;
    std::cerr << "Error Message: " << errbuf << std::endl;
    return -1;
  }

  // Prompt the user to select a network device.
  do
  {
    // Print all available devices.
    for (d = allDevs, i = 1; d; d = d->next, i++)
    {
      std::cout << i << ") " << d->name << std::endl;
      if (d->description)
        std::cout << "\t-" << d->description << std::endl;
      else
        std::cout << "\t- No description available." << std::endl;
    }
    // Check if no network interfaces.
    if (i == 1)
    {
      std::cerr << "No interfaces found." << std::endl;
      return -1;
    }
    std::cout << std::endl
              << std::endl;
    std::cout << "Which interface would you like to use? (1-" << i << "): ";
    std::cin >> interfaceNumber;
  } while (interfaceNumber < 1 || interfaceNumber > i);

  return 0;
}
