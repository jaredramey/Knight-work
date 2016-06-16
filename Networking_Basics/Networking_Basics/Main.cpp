#pragma comment (lib, "wsock32.lib")
#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

int main()
{
	//init networking
	WSAData data;
	if(WSAStartup(MAKEWORD(2, 2), &data) != NO_ERROR)
	{
		exit(0);
	}

	//settup sockets
	//Socket is really just an int
						   //IPV4
	SOCKET handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //UDP or TCP, only difference is different functions. failed on <= 0
	//fail case
	if (handle <= 0)
	{
		cout << "Failed to create socket" << endl;
		exit(0);
	}
	else
	{
		cout << handle << endl;
	}

	sockaddr_in addr; //Internet address intended for use with sockets

	//visual rep of an IP address
	union
	{
		unsigned int ui;
		char c[4];
	} IPADDRESS;

	IPADDRESS.c[0] = 172;
	IPADDRESS.c[1] = 0;
	IPADDRESS.c[2] = 0;
	IPADDRESS.c[3] = 1;

	//fill out address to represent local IP
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	addr.sin_port = htons(50000);

	//bind socket to a port
	bind(handle, (sockaddr*)&addr, sizeof(sockaddr_in)); //failed < 0

	DWORD param = 1;
	ioctlsocket(handle, FIONBIO, &param); //non-blocking, failed on != 0

	sockaddr_in out_addr, in_addr;
	int in_len = sizeof(sockaddr_in);
	char out_buffer[40] = "Dinosaur!"; //packet is 40 bytes
	char in_buffer[40];  

	//targeting my local host
	out_addr.sin_family = AF_INET;
	out_addr.sin_addr.S_un.S_un_b.s_b1 = 127; //10.
	out_addr.sin_addr.S_un.S_un_b.s_b2 = 0; //15.
	out_addr.sin_addr.S_un.S_un_b.s_b3 = 0;  //0.
	out_addr.sin_addr.S_un.S_un_b.s_b4 = 1;  //1
	out_addr.sin_port = htons(50000);

	//UDP
	//how many bytes were successfully sent
	int out_Byte = sendto(handle, out_buffer, 40, 0, (sockaddr*)&out_addr, sizeof(sockaddr_in)); //address data
	//how many bytes were successfully recieved
	int in_Byte = recvfrom(handle, in_buffer, 40, 0, (sockaddr*)&in_addr, &in_len); // recieves ANY packet in this sockets address (port)

	//TCP
	/*
	connect(...);
	send(...);
	recv(...);
	*/

	//close open sockets
	closesocket(handle);
	//cleanup or else VS could crash
	WSACleanup();
	getchar();
	return 0;
}