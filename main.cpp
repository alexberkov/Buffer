#include "Buffer.h"
#include <thread>
#define PORT 8080

int main() {
    int sock = 0, client;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cerr << "Socket creation error" << endl;
        return -1;
    }
    struct sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        cerr << "Invalid address / Address not supported" << endl;
        return -1;
    }
    if ((client = connect(sock, (struct sockaddr*) &serverAddress, sizeof(serverAddress))) < 0) {
        cerr << "Connection failed" << endl;
        return -1;
    }
    Buffer b;
    thread p(&Buffer::process, ref(b));
    thread c(&Buffer::calculate, ref(b), ref(sock));
    p.join();
    c.join();
    return 0;
}
