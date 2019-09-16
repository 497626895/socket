/*
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <winsock.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

#define BUFSIZE        1024
#define PORT        1234

int main()
{
	WSAData wsaData;
	SOCKET sHost;
	sockaddr_in addrServ;
	char buf[BUFSIZE];
	int retVal;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WSAStartup()ʧ�ܣ�" << endl;
		return -1;
	}

	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		cout << "socket()����" << endl;
		WSACleanup();
		return -1;
	}

	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(PORT);
	addrServ.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	retVal = connect(sHost, (LPSOCKADDR)& addrServ, sizeof(addrServ));
	if (SOCKET_ERROR == retVal)
	{
		cout << "connect()����" << endl;
		closesocket(sHost);
		WSACleanup();
		return -1;
	}
	retVal = recv(sHost, buf, sizeof(buf) + 1, 0);
	cout << "�ӷ��������ܣ�" << buf << endl << endl << endl;
	while (TRUE)
	{
		cout << "����Ҫ���������������ݣ�";
		//string msg;
		//getline(cin.msg);
		char msg[BUFSIZE];
		//cin.getline(msg, BUFSIZE);
		cin >> msg;
		//cout << endl;
		ZeroMemory(buf, BUFSIZE);
		strcpy(buf, msg);

		retVal = send(sHost, buf, strlen(buf), 0);
		if (SOCKET_ERROR == retVal)
		{
			cout << "����ʧ�ܣ�" << endl;
			closesocket(sHost);
			WSACleanup();
			return -1;
		}

		retVal = recv(sHost, buf, sizeof(buf) + 1, 0);
		if (SOCKET_ERROR == retVal)
		{
			cout << "recv()����������룺#" << WSAGetLastError() << endl;
			closesocket(sHost);
			WSACleanup();
			return -1;
		}
		cout << "�ӷ��������ܣ�" << buf << endl << endl;


		if (strcmp(buf, "quit") == 0)
		{
			cout << "quit" << endl;
			break;
		}
	}

	closesocket(sHost);
	WSACleanup();

	return 0;
}
*/

//  Client.cpp ������
//  ����OpenCV��Winsock��ͼ���䣨���ͣ�

#include "WinsockMatTransmissionClient.h"  

int main()
{
	WinsockMatTransmissionClient socketMat;
	if (socketMat.socketConnect("127.0.0.1", 1234) < 0) //��ַ��������
	{
		return 0;
	}

	cv::VideoCapture capture(0);
	cv::Mat frame;

	while (1)
	{

		if (!capture.isOpened())
			return 0;

		capture >> frame;
		imshow("client", frame);
		cv::waitKey(30);
		if (frame.empty())
			return 0;

		socketMat.transmit(frame);
	}

	socketMat.socketDisconnect();
	return 0;
}