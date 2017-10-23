#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(){
  int clientSocket, portNum, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /* membuat konfigurasi UDP Socket*/
  clientSocket = socket(PF_INET, SOCK_DGRAM, 0); 
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891); /* sesuaikan dengan server_udp.c */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); /* ubah sesuai dengan alamat ip server_udp.c */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); 
  /* selesai konfigurasi UDP Socket*/ 

  addr_size = sizeof serverAddr;

  while(1){
    printf("Ketikan kalimat yang akan dikirim ke server:\n");
    fgets(buffer,1024,stdin);
    printf("Anda mengirim: %s",buffer);

    nBytes = strlen(buffer) + 1;
    
    /*mengirim data ke lokasi sesuai konfigurasi UDP Socket*/
    sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);

    /* menunggu dan menerima data */
	nBytes = recvfrom(clientSocket,buffer,1024,0,NULL, NULL);

    printf("Data yang diterima dari server: %s\n",buffer);

  }

  return 0;
}
