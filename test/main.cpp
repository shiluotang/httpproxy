#include "../src/httpproxy.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <cstdlib>
#include <iostream>
#include <vector>
#include <system_error>

using namespace std;

int test_socket(int argc, char* argv[]) {
    try {
        httpproxy::socket_environment env;
        vector<httpproxy::inet_address> addresses;
        int cnt = httpproxy::inet_address::lookup("127.0.0.1", "10003", addresses);
        cout << "There're " << cnt << " addresses found!"<< endl;
        httpproxy::socket s;
        if(s.bind(addresses[0]) && s.listen(100))
            clog << "listening at " << addresses[0] << endl;
        string message = "Hello, beauty!";
        httpproxy::socket remote = s.accept();
        if(remote)
            remote.send(message.data(), message.size());
    } catch(exception &e) {
        cerr << e.what() << endl;
    }
    return EXIT_SUCCESS;
}

void foo() {
    for(int i = 0; i < 5; ++i) {
        httpproxy::this_thread::sleep_for(chrono::seconds(1));
        cout << "Hello!" << endl;
    }
}

int test_sleep(int argc, char* argv[]) {
    httpproxy::thread t(foo);
    t.join();
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    clock_t t1, t2;
    try {
        t1 = clock();
        int retcode = test_socket(argc, argv);
        t2 = clock();
        clog << "Running time is " << static_cast<double>(t2 - t1) / CLOCKS_PER_SEC << " seconds." << endl;
        return retcode;
    } catch(exception &e) {
        cerr << "[exception]: " << e.what() << endl;
    } catch(...) {
        throw;
    }
    return EXIT_SUCCESS;
}
