#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(){
  int udpSocket, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  int i;

  /* membuat konfigurasi UDP Socket*/
  udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891); /* sesuaikan dengan client__udp.c */
  serverAddr.sin_addr.s_addr = INADDR_ANY; /* tidak perlu diubah */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  /* selesai konfigurasi UDP Socket*/  

  /*melakukan Binding socket tersebut*/
  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  addr_size = sizeof serverStorage;

  while(1){
   
	/* menunggu dan menerima data yang dikirim ke alamat sesuai konfigurasi diatas */
    nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
	
	printf("Menerima data : %s", buffer);
	
    /* mengirim kembali data ke pengirim */
    sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
  }

  return 0;
}
