#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void main() {
  struct sockaddr_in my_addr;

  int sockfd;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("Error while creating the socket</ span> n");
    exit(1);
  }

  bzero(&my_addr, sizeof(my_addr)); // zero structure out

  my_addr.sin_family = AF_INET; // match the socket() call

  my_addr.sin_port = htons(5100); // specify port to listen on

  my_addr.sin_addr.s_addr =
      htonl(INADDR_ANY); // allow the server to accept a client connection on
                         // any interface

  if ((bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr))) < 0) {
    perror("Error in binding\n");
    exit(1);
  }

  if (listen(sockfd, 3) == -1) {
    printf("error in listen\n");
    exit(1);
  }

  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);
  int client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
  if (client_fd < 0) {
    printf("Error in accept\n");
    exit(1);
  }

  // Now you can use client_fd to send/receive data
  printf("Client connected\n");

  char buffer[1024];
  int bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
  if (bytes_read > 0) {
    buffer[bytes_read] = '\0';
    printf("Received: %s\n", buffer);
    write(client_fd, "Hello from server", 17);
  }

  close(client_fd);
  close(sockfd);
}
