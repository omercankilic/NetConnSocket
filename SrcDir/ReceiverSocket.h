#ifndef RECEIVER_SOCKET_H
#define RECEIVER_SOCKET_H
#include "NetConnSocket.h"

class ReceiverSocket:private NetConnSocket{

    public:
        ReceiverSocket(int receiver_port);
    private:
        unsigned int recv_speed_interval;
        void recvS();

};


#endif