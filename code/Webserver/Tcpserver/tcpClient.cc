#include "tcpClient.hpp"
#include <memory>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <ip> <port>" << std::endl;
        return 1;
    }

    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    std::unique_ptr<TcpClient> client(new TcpClient(ip, port));

    if (client->Connect()) {
        std::cout << "Connect Success! Start chatting..." << std::endl;
        client->Request();
    } else {
        std::cout << "Connect Failed." << std::endl;
    }

    return 0;
}