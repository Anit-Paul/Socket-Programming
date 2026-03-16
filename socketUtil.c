#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int make_ipv4_tcp_socket(){
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("Error while creating the socket\n");
    exit(1);
  }
  return sockfd;
}

struct sockaddr_in * get_addr(char *ip,int port){
  struct sockaddr_in *addr=malloc(sizeof(struct sockaddr_in));
  addr->sin_family = AF_INET;
  addr->sin_port = htons(port);
  if(strlen(ip)==0){
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
  }else{
  inet_pton(AF_INET, ip, &addr->sin_addr);
  }
  return addr;
}