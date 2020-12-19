#include "include/twudp.hpp"

	UdpSender::UdpSender()
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

	UdpSender::~UdpSender()
	{
		closesocket(this->S);
		WSACleanup();	
	}

	 int UdpSender::SendTo(
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


	 int UdpSender::SendTo(sockaddr_in & client_addr,const char * send_data,int buffsize)
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
	


	UdpRecv::UdpRecv(int port)
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
	
	 size_t UdpRecv::RecvTextFrom(char* &recv_data,char* &client_ip,int & client_port,int buffsize)
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

	 sockaddr_in UdpRecv::RecvTextFrom(char * &recv_data,int buffsize)
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


