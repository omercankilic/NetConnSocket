#include "./SrcDir/SenderSocket.h"
#include "./SrcDir/ReceiverSocket.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]){

    // if(2 == argc){
    //     DiffPacketSizeSender objP(argv[1],8002);    
    // }else{
    //     cout<<"Wrong command argument"<<endl;
    // }

    ReceiverSocket recvSock(52000);
    
}