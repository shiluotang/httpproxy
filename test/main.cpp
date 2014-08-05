#include "../src/httpproxy.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
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

int test_http(int argc, char* argv[]) {
	httpproxy::socket_environment env;
	vector<httpproxy::inet_address> addresses;
	if (httpproxy::inet_address::lookup("www.baidu.com", "80", addresses) < 1)
		return EXIT_FAILURE;
	string const REQUEST = "GET http://www.baidu.com/ HTTP/1.1\r\n"
		"Host: www.baidu.com\r\n"
		"\r\n\r\n";
	httpproxy::socket s(AF_INET, SOCK_STREAM, IPPROTO_IP);
	s.connect(addresses[0]);
	clog << "sending data..." << endl;
	clog << "REQUEST is " << REQUEST << endl;
	s.send(REQUEST.data(), REQUEST.size());
	char buf[4096];
	int cnt;
	stringstream ss;
	while ((cnt = s.receive(buf, sizeof(buf))) > 0) {
		clog << "reading " << cnt << " bytes." << endl;
		ss.write(buf, cnt);
	}
	cout << "received data is " << ss.str() << endl;
	return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    try {
		httpproxy::stop_watch watch;
		watch.start();
        int retcode = test_http(argc, argv);
		watch.stop();
        clog << "Running time is " << watch << "." << endl;
        return retcode;
    } catch(exception &e) {
        cerr << "[exception]: " << e.what() << endl;
    } catch(...) {
        throw;
    }
    return EXIT_SUCCESS;
}
