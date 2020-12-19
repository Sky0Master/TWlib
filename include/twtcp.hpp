#pragma once
#ifndef _TW_TCP_HPP_
#define _TW_TCP_HPP_
#include <Winsock2.h>
#include <WS2tcpip.h>  //InetPton声明文件
#include <windows.h>

#pragma comment(lib,"ws2_32.lib")

class TCP_Client 
{
    private:
        SOCKET sock_client;
        SOCKADDR_IN serv_add;
    public:
        int err          =  0;  
        //0: no error 1:winsock load error  2:failed to create socket  3:failed to connect
        int state        =  0 ;
        int size         =  10240;
        const char * END =  "$END$";
        TCP_Client(const char* serv_ip, int serv_port);

        int Connect();

        void Recv(char* data);

        void Send(const char* data);
};
        
#endif  //_TW_TCP_HPP_
