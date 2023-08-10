#include "Order.h"
#include "OrderManage.h"
#include "tcpserver.h"
#include "tcpsocket.h"

int main() {
	OrderManage order1;
	order1.recvNewOrder(8888);
	while (true) {
	}
}

