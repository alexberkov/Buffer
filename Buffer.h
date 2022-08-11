#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

using namespace std;

class Buffer {
    string s;
    bool access = false;
public:
    static bool checkString(const string &st);
    void process();
    void calculate(int sock);
};



