#include "socketUtil.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {

  int sockfd = make_ipv4_tcp_socket();

  struct sockaddr_in *addr = get_addr("", 2000);

  if (bind(sockfd, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
    perror("bind failed");
    exit(1);
  }

  if (listen(sockfd, 5) == -1) {
    perror("listen failed");
    exit(1);
  }

  struct sockaddr client_addr;
  socklen_t client_len = sizeof(client_addr);
  int clientfd = accept(sockfd, &client_addr, &client_len);
  if (clientfd == -1) {
    perror("accept failed");
    exit(1);
  }

  while (1) {
    char buffer[1024];
    int bytes_read = read(clientfd, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0)
      break;
    buffer[bytes_read] = '\0';
    printf("Client: %s\n", buffer);
    char *s = (char *)malloc(500 * sizeof(char));
    printf("Server: ");
    fgets(s, 499, stdin);
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
      s[len - 1] = '\0';
    write(clientfd, s, strlen(s));
    free(s);
  }

  close(clientfd);
  close(sockfd);
  return 0;
}