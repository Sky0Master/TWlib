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
	UdpSender();

	~UdpSender();


	int SendTo(
		const char* ip,  //目标IP
		int port,        //目标端口
		const char* send_data,  //数据
		int buffsize
		);


	int SendTo(
		sockaddr_in & client_addr,
		const char * send_data,
		int buffsize
	);
	
};

class UdpRecv
{
private:
	SOCKET S;
	int ERR = 0;
	sockaddr_in ADDR = {0};

public:
	UdpRecv(int port);
	
	size_t RecvTextFrom(
		char* &recv_data,
		char* &client_ip,
		int & client_port,
		int buffsize
	);
	
	sockaddr_in RecvTextFrom(
		char * &recv_data,
		int buffsize
	);
};

#endif