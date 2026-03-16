#include "socketUtil.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // making a socket
  int sockfd = make_ipv4_tcp_socket();
  // for connection
  struct sockaddr_in *addr = get_addr("127.0.0.1", 2000);
  int result = connect(sockfd, (struct sockaddr *)addr, sizeof(*addr));
  if (result < 0) {
    printf("connection failed");
    exit(1);
  }
  free(addr);
  addr = NULL;
  printf("connection successful\n");
  // communication
  while (1) {
    char *message = (char *)malloc(500 * sizeof(char));
    printf("Client: ");
    fgets(message, 499, stdin);
    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n')
      message[len - 1] = '\0';
    write(sockfd, message, strlen(message));

    char buffer[1024];
    int bytes_read = read(sockfd, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0)
      break;
    buffer[bytes_read] = '\0';
    printf("Server: %s\n", buffer);
    free(message);
  }

  close(sockfd);
  return 0;
}