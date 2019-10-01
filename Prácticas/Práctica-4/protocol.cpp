#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>

int main(int argc, char **argv)
{
  pcap_t *fp;
  //char errbuf[PCAP_ERRBUF_SIZE];
  u_char packet[100];
  int i = 0;

  /*********************************************/
  pcap_if_t *alldevs;
  pcap_if_t *d;
  int inum;
  //int i=0;
  pcap_t *adhandle;
  char errbuf[PCAP_ERRBUF_SIZE];

  /* Retrieve the device list */
  if (pcap_findalldevs(&alldevs, errbuf) == -1)
  {
    fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
    exit(1);
  }

  /* Print the list */
  for (d = alldevs; d; d = d->next)
  {
    printf("%d. %s", ++i, d->name);
    if (d->description)
      printf(" (%s)\n", d->description);
    else
      printf(" (No description available)\n");
  }

  if (i == 0)
  {
    printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
    return -1;
  }

  printf("Enter the interface number (1-%d):", i);
  scanf("%d", &inum);

  if (inum < 1 || inum > i)
  {
    printf("\nInterface number out of range.\n");
    /* Free the device list */
    pcap_freealldevs(alldevs);
    return -1;
  }

  /* Jump to the selected adapter */
  for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++)
    ;

  /*******************************************/

  /* Check the validity of the command line */
  /* if (argc != 2)
    {
        printf("usage: %s interface (e.g. 'rpcap://eth0')", argv[0]);
        return;
    }
    */
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