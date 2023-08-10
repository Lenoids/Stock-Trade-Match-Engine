#include "OrderManage.h"
#include "Order.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>

void OrderManage::addOrder(const Order& order) {
	if (order.getType() == "buy") {
		_buyOrders.push_back(order);
	}
	else if (order.getType() == "sell") {
		_sellOrders.push_back(order);
	}
	
	matchOrder();
    return;
}

void OrderManage::matchOrder() {
	for (auto& s : _sellOrders) {
		for (auto& b : _buyOrders) {
			if (s.getPrice() <= b.getPrice()) {
				int dealNum = std::min(s.getQuantity(), b.getQuantity());
				s.setQuantity(s.getQuantity() - dealNum);
				b.setQuantity(b.getQuantity() - dealNum);
                std::cout << "Buy order ID: " << b.getID() << "  " << "Sell order ID: " << s.getID() << " matches, volume is: " << dealNum << std::endl;
                std::cout << "Buy order remains: " << b.getQuantity() << "  " << "Sell order remains: " << s.getQuantity() << std::endl;
                deal++;
                if (deal == 5) {
                    deal = 0;
                    printOrder();
                }
            }
		}
	}

	clearOrder();
    return;
}

void OrderManage::clearOrder() {
	auto newBuyPtr = std::remove_if(_buyOrders.begin(), _buyOrders.end(), [](Order& order)
		{ return order.getQuantity() == 0; }
	);
	_buyOrders.erase(newBuyPtr, _buyOrders.end());

	auto newSellPtr = std::remove_if(_sellOrders.begin(), _sellOrders.end(), [](Order& order)
		{ return order.getQuantity() == 0; }
	);
	_sellOrders.erase(newSellPtr, _sellOrders.end());
	return;
}

void OrderManage::printOrder() {
    std::cout << "<---------BUY ORDER SUM:---------->" << std::endl;
    for (auto& b : _buyOrders) {    
        std::cout << "Buy order ID: " << b.getID() << " | ";
        std::cout << "Price: " << b.getPrice() << " | ";
        std::cout << "Remain quantity: " << b.getQuantity() << " | ";
        std::cout << std::endl;
    }
    std::cout << "<---------SELL ORDER SUM:--------->" << std::endl;
    for (auto& s : _sellOrders) {
        std::cout << "Sell order ID: " << s.getID() << " | ";
        std::cout << "Price: " << s.getPrice() << " | ";
        std::cout << "Remain quantity: " << s.getQuantity() << " | ";
        std::cout << std::endl;
    }
    return;
}

void OrderManage::recvNewOrder(int port) {
    TCPServer* tcpServer = new TCPServer;
    tcpServer->Bind("127.0.0.1", port, [](int errorCode, std::string errorMessage) {
        // BINDING FAILED:
        std::cout << errorCode << " : " << errorMessage << std::endl;
        });

    // Start Listening the server.
    tcpServer->Listen([](int errorCode, std::string errorMessage) {
        // LISTENING FAILED:
        std::cout << errorCode << " : " << errorMessage << std::endl;
        });

    tcpServer->onNewConnection = [&](TCPSocket* newClient) {
        std::cout << "New client: [";
        std::cout << newClient->remoteAddress() << ":" << newClient->remotePort() << "]" << std::endl;

        newClient->onMessageReceived = [newClient, this](std::string message) {
            std::cout << newClient->remoteAddress() << ":" << newClient->remotePort() << " => " << message << std::endl;
		
            // Init new order
            int ID;
            std::string type;
            double price;
            int quantity;
            std::stringstream ss(message);

            // Receive, split new message and add to order 
            std::getline(ss, message, ',');
            ID = std::stoi(message);

            std::getline(ss, type, ',');

            std::getline(ss, message, ',');
            price = std::stod(message);

            std::getline(ss, message);
            quantity = std::stoi(message);

            Order order(ID, price, type, quantity);
			addOrder(order);
            
        };

        newClient->onSocketClosed = [newClient]() {
            std::cout << "Socket closed:" << newClient->remoteAddress() << ":" << newClient->remotePort() << std::endl;
        };
    };
    return;
}
	