
/* ethernet monitor 
 * ethermon.c
 *     t-matsu 10/14, 2008
 */

#include  <stdio.h>
#include  <string.h>           /* strcpy */
#include  <arpa/inet.h>        /* sockaddr_in */
#include  <net/if.h>           /* ifreq */
#include  <net/ethernet.h>     /* ether_header ETH_P_ALL */
#include  <netpacket/packet.h> /* PACKET_MR_PROMISC PACKET_ADD_MEMBERSHIP */

char *mac_ntoa(u_char *d){
  static char str[18];
  sprintf(str,"%02x:%02x:%02x:%02x:%02x:%02x",d[0],d[1],d[2],d[3],d[4],d[5]);
  return str;
}

void print_ether(struct ether_header *eth){
  printf("Det MAC addr   : %17s \n",mac_ntoa(eth->ether_dhost));
  printf("Src MAC addr   : %17s \n",mac_ntoa(eth->ether_shost));
  int type = ntohs(eth->ether_type);
  if(type < 1500){
    printf("Ethernet Type  : %5u\n",ntohs(eth->ether_type));
  }else{
    printf("Ethernet Type  : 0x%04x\n",ntohs(eth->ether_type));
  }
}

int main(int argc, char *argv[]){
  struct ifreq ifr;
  int rsock,rsin_size;
  struct sockaddr_in rsin;
  struct ether_header *eth;
  fd_set fds;
  char p0[1518], *p;

  if ((rsock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0 ){
    perror("socket");
    return(0);
  }
 
  rsin_size = sizeof(rsin);
  FD_ZERO(&fds);
  FD_SET(rsock, &fds);

  while(1){
    if(select(rsock+1, &fds, NULL, NULL, NULL) < 0 ){
      perror("select");
      return(0);
    }
    if (FD_ISSET(rsock, &fds)){
      if(recvfrom(rsock, &p0, sizeof(p0), 0, 
                        (struct sockaddr *)&rsin, &rsin_size) < 0 ) {
        perror("recvfrom");
      }
      p = (char *)p0;
      eth = (struct ether_header *)p;
      print_ether(eth);

    }
  }
}