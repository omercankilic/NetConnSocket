#include "SenderSocket.h"
#include <cstring>
#include <iostream>

SenderSocket::SenderSocket(string trgt_ip,int trgt_port):sleep_time(1),\
                target_ip(trgt_ip),target_port(trgt_port),\
                NetConnSocket(SELF_PORT)
{

    memset(&this->target_addr,0,sizeof(this->target_addr));
    this->target_addr.sin_family      = AF_INET;
    this->target_addr.sin_port        = htons(target_port);
    this->target_addr.sin_addr.s_addr = inet_addr(target_ip.c_str());
    
}

DiffPacketSizeSender::DiffPacketSizeSender(string trgt_ip,int trgt_port):\
                                           SenderSocket(trgt_ip,trgt_port)
{
    this->PACKET_TYPES = 6;

    this->packet_size.push_back(1400);
    this->packet_size.push_back(4000);
    this->packet_size.push_back(8000);
    this->packet_size.push_back(16000);
    this->packet_size.push_back(32000);
    this->packet_size.push_back(64000);
    
    this->send(NULL);
    shutdown(this->sockfd,SHUT_RDWR);
}

void DiffPacketSizeSender::send(void* argument_list)
{
    if(NULL != argument_list){
        std::cout<<"Not null argument list"<<std::endl;
    }

    int stop,initial_packet =0;
    long long totalBytesSend = 0;
    double time_taken;
    struct timespec highResStart,highResEnd;
    char *char_pack;
    long long res = 0;
        
    int j = 0;
    int k = 0;
    int i = 0;

    while (k < PACKET_TYPES)
    {
        i = 0;
        while(i < PACKET_TYPES)
        {
            char_pack = new char[packet_size[i]];
            memset(char_pack,'a',packet_size[i]);
            j = 0;
            std::cout<<"{\r\nPacket size: "<<packet_size[i]<<std::endl;
            while(j<2)
            {
                totalBytesSend = 0;
                initial_packet = 0;
                do
                {
                    if(0 == initial_packet)
                    {
                        clock_gettime(CLOCK_MONOTONIC,&highResStart);
                        initial_packet = 1;
                    }
                    res = sendto(this->sockfd,char_pack,packet_size[i],0,(struct sockaddr*)&this->target_addr,sizeof(target_addr));

                    if(0>res)
                    {
                        std::cout<<"Sendto failed"<<std::endl;
                    }
                    else
                    {
                        totalBytesSend +=res;
                    }
                    clock_gettime(CLOCK_MONOTONIC,&highResEnd);
                } while ((highResEnd.tv_sec - highResStart.tv_sec)<30);
                
                time_taken = (highResEnd.tv_sec - highResStart.tv_sec);
                time_taken = (time_taken + (highResEnd.tv_nsec - highResStart.tv_nsec)*1e-9);
                std::cout<<"Total bytes send : "<<totalBytesSend<<"\r\nTest nb : "<<j<<" Send speed : "<<(8*totalBytesSend)/(time_taken*1024*1024)<<" Mbps"<<std::endl;
                j++;
            }
            delete char_pack;
            i++;
            std::cout<<" }"<<std::endl<<std::endl;
        }
        k++;
    }
    shutdown(this->sockfd,SHUT_RDWR);
}