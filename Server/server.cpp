#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#define PORT 8080

using namespace std;

int main() {
    int server, newSocket;
    size_t val;
    char buffer[1024] = { 0 };
    if ((server = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr =INADDR_ANY;
    address.sin_port = htons(PORT);
    socklen_t len = sizeof(address);
    if (bind(server, (const struct sockaddr*) &address, len) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((newSocket = accept(server, (struct sockaddr*) &address, (socklen_t*)&len)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    while (true) {
        val = read(newSocket, buffer, 1024);
        string str(buffer);
        if (str == "stop") break;
        if (str.length() > 2 && (stoi(str) % 32 == 0)) {
            cout << "Data successfully transferred." << endl;
        } else cerr << "Error: incorrect data" << endl;
    }
    close(newSocket);
    shutdown(server, SHUT_RDWR);
    return 0;
}
