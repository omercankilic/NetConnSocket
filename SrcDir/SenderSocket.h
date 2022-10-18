#ifndef SENDER_SOCKET_H
#define SENDER_SOCKET_H
#include "NetConnSocket.h"
#include <string>
#include <vector>

using namespace std;

class SenderSocket:protected NetConnSocket
{
    protected:
        int sleep_time;
        string target_ip;
        int target_port;
        struct sockaddr_in target_addr;

        SenderSocket(string target_ip,int target_port);
        
        virtual void send(void * argument_list) = 0;
};


class DiffPacketSizeSender:private SenderSocket
{
    public:
        DiffPacketSizeSender(string target_ip,int target_port);
    private:
        int PACKET_TYPES;
        vector<int> packet_size;
        void send(void* argument_list);
};

#endif