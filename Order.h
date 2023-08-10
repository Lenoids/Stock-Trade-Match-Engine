#pragma once
#include <string>

class Order {
public:
	Order(int ID, double price, std::string type, int quantity) : 
		_ID(ID), _price(price), _type(type), _quantity(quantity){}

	~Order() = default;

	int getID();
	double getPrice();
	std::string getType() const;
	int getQuantity();
	void setQuantity(int q);

private:
	int _ID;
	double _price;
	std::string _type;
	int _quantity;
};

