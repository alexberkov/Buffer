#include "Buffer.h"
#include <fstream>
#include <thread>

bool Buffer::checkString(const string &st) {
    size_t len = st.length();
    if (len > 64) return false;
    for (auto c: st)
        if (!isalnum(c)) return false;
    return true;
}

void Buffer::process() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(10));
        cout << "Enter string: ";
        cin >> s;
        if (s == "stop") break;
        if (checkString(s)) {
            sort(s.begin(), s.end(), [](auto &l, auto &r) {
                return l > r;
            });
            string r;
            for (int i = 0; i < s.length(); ++i) {
                if (i % 2 == 0) r += s[i];
                else r += "KB";
            }
            ofstream file("../buffer.txt");
            if (file.is_open()) file << r;
            file.close();
            this->access = true;
        }
    }
}

void Buffer::calculate(int sock) {
    while (true) {
        if (this->s == "stop") {
            send(sock, s.c_str(), strlen(s.c_str()), 0);
            break;
        }
        if (this->access) {
            ifstream file("../buffer.txt");
            string r;
            if (file.is_open()) file >> r;
            int res = 0;
            for (auto c: r) if (isdigit(c)) res += ((int)(c - '0'));
            cout << "Total sum: " << res << " KB" << endl;
            file.close();
            this->access = false;
            string str = to_string(res);
            send(sock, str.c_str(), strlen(str.c_str()), 0);
        }
    }
}