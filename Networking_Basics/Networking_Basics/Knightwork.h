#pragma once
#pragma comment (lib, "wsock32.lib")
#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

namespace nsfw
{
	bool initNetworking()
	{
		//init networking
		WSAData data;
		return WSAStartup(MAKEWORD(2, 2), &data) == NO_ERROR;
	}
	bool termNetworking()
	{
		return WSACleanup() == 0;
	}

	sockaddr_in stoa(const char* src, size_t len)
	{
		sockaddr_in dst;
		union { char values[4]; unsigned ui; } IP;
		unsigned short port;
		const char* ptr = src;

		IP.values[0] = atoi(ptr); ptr += strcspn(ptr, ".") + 1;
		IP.values[1] = atoi(ptr); ptr += strcspn(ptr, ".") + 1;
		IP.values[2] = atoi(ptr); ptr += strcspn(ptr, ".") + 1;
		IP.values[3] = atoi(ptr); ptr += strcspn(ptr, ".") + 1;
		port = atoi(ptr);

		dst.sin_family = AF_INET;
		dst.sin_addr.S_un.S_addr = IP.ui;
		dst.sin_port = htons(port);
		return dst;
	}

	class Socket
	{
		int handle = 0;
	public:
		~Socket() { close(); };

		bool IsOpen() const { return handle != 0; };

		bool open(unsigned port = 0)
		{
			SOCKET handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //UDP or TCP, only difference is different functions. failed on <= 0
			sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_addr.S_un.S_addr = INADDR_ANY;
			addr.sin_port = htons(port);

			//bind socket to a port
			bind(handle, (sockaddr*)&addr, sizeof(sockaddr_in)); //failed < 0
		}
		bool close()
		{
			if (!IsOpen()) return false;
			closesocket(handle);
			handle = 0;
			return true;
		}

		bool SendPAcket()
		{

		}
		bool RecievePacket()
		{

		}
	};
}