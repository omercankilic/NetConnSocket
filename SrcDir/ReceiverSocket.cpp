#include "ReceiverSocket.h"
#include <chrono>
#include <ctime>
#include <cstring>
#include <iostream>

ReceiverSocket::ReceiverSocket(int receiver_port):NetConnSocket(receiver_port),\
                                                  recv_speed_interval(10)
{
    this->recvS();
}

void ReceiverSocket::recvS()
{

    int res = 0;
    int initial = 0;
    long long total_bytes_recvd = 0;
    std::chrono::time_point<std::chrono::system_clock> start,end;
    std::chrono::duration<double> elapsed_seconds;
    std::time_t end_time;
    char msg_buff[64000];
    memset(msg_buff,0,64000);
    
    while(1)
    {
        initial = 0;
        total_bytes_recvd = 0;
        do
        {
            res = recv(this->sockfd,msg_buff,64000,0);
            if(initial = 0)
            {
                start = std::chrono::system_clock::now();
                initial = 1;
            }
            if(res > 0){
                total_bytes_recvd +=res;
            }
            end = std::chrono::system_clock::now();

            elapsed_seconds = end - start;

        }while(elapsed_seconds.count() < this->recv_speed_interval);
        
        std::cout<<"Receiver speed : "<< (total_bytes_recvd / elapsed_seconds.count())<<" Mbps"<<std::endl;

    }
    shutdown(this->sockfd,SHUT_RDWR);
}