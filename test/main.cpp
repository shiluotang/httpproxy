#include "../src/httpproxy.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <cstdlib>
#include <iostream>
#include <vector>
#include <system_error>


using namespace std;

void foo() {
    cout << "log " << endl;
}

int main(int argc, char* argv[]) {
    httpproxy::thread t(&foo);
    //t.join();
    

    //try {
    //    httpproxy::socket_environment env;
    //    vector<httpproxy::inet_address> addresses;
    //    int cnt = httpproxy::inet_address::lookup("127.0.0.1", "10003", addresses);
    //    cout << "There're " << cnt << " addresses found!"<< endl;
    //    httpproxy::socket s;
    //    if(s.bind(addresses[0]) && s.listen(100))
    //        clog << "listening at " << addresses[0] << endl;
    //    string message = "Hello, beauty!";
    //    httpproxy::socket remote = s.accept();
    //    if(remote)
    //        remote.send(message.data(), message.size());
    //} catch(exception &e) {
    //    cerr << e.what() << endl;
    //}
    return EXIT_SUCCESS;
}
