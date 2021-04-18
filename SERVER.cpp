#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <clocale>
#pragma warning(disable: 4996)

SOCKET Connections[100];
int Counter = 0;
int sum = 0;
void ClientOp(int index) {
	int msg_size;
	while (true) {
		recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connections[index], msg, msg_size, NULL);
		std::cout << msg << std::endl;
		std::string msg1 = "Тема вашей работы:\n";
		int msg_size = msg1.size();
		send(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		send(Connections[index], msg1.c_str(), msg_size, NULL);
		if (atoi(msg) == 1) {
			std::string msg = "Методология IDEF0";
			int msg_size = msg.size();
			send(Connections[index], (char*)&msg_size, sizeof(int), NULL);
			send(Connections[index], msg.c_str(), msg_size, NULL);
		}
		else if (atoi(msg) == 2) {
			std::string msg = "Инструменты DevOps";
			int msg_size = msg.size();
			send(Connections[index], (char*)&msg_size, sizeof(int), NULL);
			send(Connections[index], msg.c_str(), msg_size, NULL);
		}
		else if (atoi(msg) == 3) {
			std::string msg = "Методология ITIL";
			int msg_size = msg.size();
			send(Connections[index], (char*)&msg_size, sizeof(int), NULL);
			send(Connections[index], msg.c_str(), msg_size, NULL);
		}
		else if (atoi(msg) == 4) {
			std::string msg = "UI и UX дизайн ";
			int msg_size = msg.size();
			send(Connections[index], (char*)&msg_size, sizeof(int), NULL);
			send(Connections[index], msg.c_str(), msg_size, NULL);
		}
		else if (atoi(msg) == 5) {
			std::string msg = "Библиотека QT";
			int msg_size = msg.size();
			send(Connections[index], (char*)&msg_size, sizeof(int), NULL);
			send(Connections[index], msg.c_str(), msg_size, NULL);
		}
		}
	}

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	for (int i = 0; i < 100; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (newConnection == 0) {
			std::cout << "Error #2\n";
		}
		else {
			std::cout << "Client Connected!\n";
			std::string msg = "Гусакова Елизавета Игоревна 14.04.2021\n Введите номер зачетной книжки";
			int msg_size = msg.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, msg.c_str(), msg_size, NULL);
			Connections[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientOp, (LPVOID)(i), NULL, NULL);
		}
	}
	system("pause");
	return 0;
}







