#include "NetConnSocket.h"
#include <cstring>
#include <iostream>

NetConnSocket::NetConnSocket(int port_number):self_port_number(port_number){
    this->open_socket();
}

int NetConnSocket::open_socket(){
    int ret;
    memset(&this->src_addr,0,sizeof(src_addr));

    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(0 > sockfd)
    {
        std::cout<<"Socket can't be created"<<std::endl;
        return -1;
    }

    int opt = 1;
    ret = setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));
    if(ret < 0){
        std::cout<<"Setsockopt error"<<std::endl;
        return -1;
    }

    src_addr.sin_family      = AF_INET;
    src_addr.sin_port        = htons(this->self_port_number);
    src_addr.sin_addr.s_addr = INADDR_ANY;

    if(0 > bind(sockfd,(const struct sockaddr *)&src_addr,sizeof(this->src_addr)))
    {
        std::cout<<"Bind error"<<std::endl;
        shutdown(this->sockfd,SHUT_RDWR);
        return -1;
    }

    std::cout<<"Socket created"<<std::endl;
    return 1;
}