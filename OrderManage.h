#pragma once
#include "Order.h"
#include "tcpserver.h"
#include "tcpsocket.h"
#include <vector>

class OrderManage {
public:
	void addOrder(const Order& order);
	void matchOrder();
	void clearOrder();
	void printOrder();
	void recvNewOrder(int port);

private:
	std::vector<Order> _buyOrders;
	std::vector<Order> _sellOrders;
	int deal = 0;
};

