#ifndef NETCONN_SOCKET_H
#define NETCONN_SOCKET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#define SELF_PORT 52000

class NetConnSocket{
    protected:
        NetConnSocket(int port);
        struct sockaddr_in src_addr;
        int sockfd;
        int open_socket();
        int self_port_number;  
    
};

#endif