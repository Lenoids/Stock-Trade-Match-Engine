#include "Order.h"

int Order::getID() {
	return _ID;
}

double Order::getPrice() {
	return _price;
}

std::string Order::getType() const {
	return _type;
}

int Order::getQuantity() {
	return _quantity;
}

void Order::setQuantity(int q) {
	_quantity = q;
}



