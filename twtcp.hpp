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
        TCP_Client(const char* serv_ip, int serv_port)
        {
            WORD w = MAKEWORD(2, 2);
            WSADATA wsa;
            if (WSAStartup(w, &wsa) != 0) 
            {
                err = 1; 
                return;
            }

            serv_add.sin_family = AF_INET;
            serv_add.sin_port = htons(serv_port);
            serv_add.sin_addr.S_un.S_addr = inet_addr(serv_ip);  
            //inet_pton(AF_INET,serv_ip,&serv_add.sin_addr);   //新函数
            sock_client = socket(AF_INET, SOCK_STREAM, 0);
            if (SOCKET_ERROR == sock_client) 
            {
                err = 2;
                return;
            }
        }

        int Connect()
        {
            if(connect(sock_client, (struct sockaddr*) & serv_add, sizeof(serv_add) ) == INVALID_SOCKET) 
            {
                err = 3;
                return 0;  //ERROR
            }
            state = 1;
            return 1;
        }

        void Recv(char* data)
        {
            int end=recv(sock_client, data, size, 0);
            data[end] = '\0';
        }

        inline void Send(const char * data)
        {
            send(sock_client, data, strlen(data), 0);
        }
};
        
#endif  //_TW_TCP_HPP_
