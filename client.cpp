#include "tcpsocket.h"
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;
void createTest(int threadID, int tradeNum) {
    // Initialize socket.
    TCPSocket tcpSocket;

    // Start receiving from the host.
    tcpSocket.onMessageReceived = [](string message) {
        cout << "Message from the Server: " << message << endl;
    };
    
    // On socket closed:
    tcpSocket.onSocketClosed = []{
        cout << "Connection closed." << endl;
    };

    // Connect to the host.
    tcpSocket.Connect("127.0.0.1", 8888, [&] {
        cout << "Connected to the server successfully." << endl;
    },
    [](int errorCode, std::string errorMessage){
        // CONNECTION FAILED
        cout << errorCode << " : " << errorMessage << endl;
    });

    // You should do an input loop so the program will not end immediately:
    // Because socket listenings are non-blocking.
    for (int i = 1; i <= tradeNum; i++){
        std::string sellMsg = std::to_string(threadID * 1000 + i) + "," + "sell" + "," + std::to_string(3 * i + 2 * threadID) + "," + std::to_string(5 * i + 2 * threadID);
        tcpSocket.Send(sellMsg);
        sleep(1);
        std::string buyMsg = std::to_string(threadID * 1000 + i) + "," + "buy" + "," + std::to_string(2 * i + 3 * threadID) + "," + std::to_string(10 * i + threadID);
        tcpSocket.Send(buyMsg);
        sleep(1);
    }

    tcpSocket.Close();
}


int main()
{   
    int threadNum, tradeNum;
    std::cout << "Welcome to the makeEngine test, please input the number of clients you want to create(0-999): ";
    std::cin >> threadNum;
    std::cout << std::endl;
    std::cout << "Please input the number of trade every clients make: ";
    std::cin >> tradeNum;
    std::cout << std::endl;
    std::vector<std::thread> threads;

    for (int i = 0; i < threadNum; i++) {
        threads.emplace_back(createTest, i, tradeNum);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    return 0;
}
