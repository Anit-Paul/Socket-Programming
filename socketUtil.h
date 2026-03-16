#ifndef SOCKET_UTIL_H
#define SOCKET_UTIL_H

int make_ipv4_tcp_socket();
struct sockaddr_in * get_addr(char *ip,int port);
#endif

