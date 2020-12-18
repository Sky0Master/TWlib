#pragma once

#ifndef _UDP_H_
#define _UDP_H_
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#define BLOW 2
#define BHIGH 2

#include <winsock2.h>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#pragma comment(lib,"ws2_32.lib")

enum ERR_TYPE {
	NONE_ERR	 =	0,
	WSA_ERR		 = -1,
	SOCKET_ERR   = -2,
	TRANSMIT_ERR = -3,
	FILE_ERR     = -4
};


class UdpSender {
private:
	SOCKET S;
	sockaddr_in ADDR = {0};
	int ERR = 0;
public:
	UdpSender()
	{
		WSADATA wsa;
		if (WSAStartup(MAKEWORD(BHIGH, BLOW), &wsa) != 0)
		{
			this->ERR = WSA_ERR;
			return;
		}
		this->S = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (this->S == INVALID_SOCKET)
		{
			this->ERR = SOCKET_ERR;
			return;
		}
		this->ADDR.sin_family = AF_INET;
	}

	~UdpSender()
	{
		closesocket(this->S);
		WSACleanup();	
	}

	inline int SendTo(
		const char* ip,  //目标IP
		int port,        //目标端口
		const char* send_data,  //数据
		int buffsize
		)
	{
		if (this->ERR) return this->ERR;
		this->ADDR.sin_port = htons(port);
		this->ADDR.sin_addr.S_un.S_addr = inet_addr(ip);
		int dwSent = sendto(this->S, send_data , strlen(send_data), 0 ,(const SOCKADDR *)&this->ADDR , sizeof(SOCKADDR));
		if (!dwSent)
		{
			this->ERR = TRANSMIT_ERR;
			return this->ERR;
		}
		return dwSent;
	}


	inline int SendTo(
		sockaddr_in & client_addr,
		const char * send_data,
		int buffsize
	)
	{
		if (this->ERR) return this->ERR;
		int dwSent = sendto(this->S, send_data, strlen(send_data), 0, (const SOCKADDR*)&client_addr, sizeof(SOCKADDR));
		if (!dwSent)
		{
			this->ERR = TRANSMIT_ERR;
			return this->ERR;
		}
		return dwSent;
	}
	
};

class UdpRecv
{
private:
	SOCKET S;
	int ERR = 0;
	sockaddr_in ADDR = {0};
	 

public:
	UdpRecv(int port)
	{
		WSADATA wsa;
		if (WSAStartup(MAKEWORD(BHIGH, BLOW), &wsa) != 0)   
		{
			this->ERR = WSA_ERR;
			return;
		}
		this->S = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);   //create socket
		if (this->S == SOCKET_ERROR || this->S==INVALID_SOCKET)
		{
			this->ERR = SOCKET_ERR;
			return;
		}
		this->ADDR.sin_family = AF_INET;
		this->ADDR.sin_port = htons(port);
		this->ADDR.sin_addr.S_un.S_addr = htonl(INADDR_ANY);    
		bind(S, (sockaddr*)&ADDR, sizeof(sockaddr));          //bind socket to local port
	}
	
	inline size_t RecvTextFrom(
		char* &recv_data,
		char* &client_ip,
		int & client_port,
		int buffsize
	)
	{
		recv_data = (char*)malloc(10 * sizeof(char)*(buffsize) );
		client_ip = (char*)malloc(sizeof(char) * 1024);
		if (recv_data == NULL || client_ip == NULL || ERR) return ERR;
		memset(recv_data, 0, sizeof(recv_data));
		sockaddr_in client_addr = { 0 };
		int addrlen = sizeof(sockaddr_in);
		size_t ret = recvfrom(S, recv_data, buffsize, 0, (sockaddr*)&client_addr,&addrlen);
		recv_data[ret] = '\0';
		strcpy_s(client_ip,1024,inet_ntoa(client_addr.sin_addr));
		client_port = ntohs(client_addr.sin_port);
		return ret;
	}

	inline sockaddr_in RecvTextFrom(
		char * &recv_data,
		int buffsize
	)
	{
		sockaddr_in client_addr = { 0 };
		recv_data = (char*)malloc(10 * sizeof(char) * (buffsize));
		if (recv_data == NULL || ERR) return { 0 };
		memset(recv_data, 0, sizeof(recv_data));

		int addrlen = sizeof(sockaddr_in);
		size_t ret = recvfrom(S, recv_data, buffsize, 0, (sockaddr*)&client_addr, &addrlen);
		recv_data[ret] = '\0';
		return client_addr;
	}
};

#endif