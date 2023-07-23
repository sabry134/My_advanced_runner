#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <IP> <PORT>" << std::endl;
        return 1;
    }

    const char* ip = argv[1];
    int port = std::stoi(argv[2]);

    int clientSocket;
    sockaddr_in serverAddress;

    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket creation failed!" << std::endl;
        return 1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid address or address not supported!" << std::endl;
        return 1;
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Connection failed!" << std::endl;
        return 1;
    }

    std::cout << "Connected to the server!" << std::endl;

    while (true) {

        char message[1024];
        std::cout << "Enter a message to send to the server (type 'exit' to quit): ";
        std::cin.getline(message, sizeof(message));

        printf("message = %s\n", message);
        send(clientSocket, message, strlen(message), 0);

        char buffer[1024] = {0};
        recv(clientSocket, buffer, sizeof(buffer), 0);

        std::cout << "Server response: " << buffer << std::endl;

        if (std::string(message) == "exit") {
            break;
        }
    }

    close(clientSocket);

    return 0;
}
