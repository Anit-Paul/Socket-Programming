#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int sockfd;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("Error while creating the socket\n");

    exit(1);
  }
  struct sockaddr_in server_addr;
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5100);
  //server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Connect to localhost (For same machine)
  inet_pton(AF_INET, "192.168.29.37", &server_addr.sin_addr); //for different machines

  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    printf("Error in connect\n");
    exit(1);
  }

  printf("Connected to server\n");

  char buffer[1024];
  strcpy(buffer, "Hello from client\n");
  write(sockfd, buffer, strlen(buffer));

  bzero(buffer, sizeof(buffer));
  read(sockfd, buffer, sizeof(buffer) - 1);
  printf("Received from server: %s", buffer);

  close(sockfd);
  printf("Connection closed\n");
}