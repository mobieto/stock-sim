#include "Order.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

int arrivalIndex = 0;

Order::Order(std::string _orderId, int _quantity, bool _isMarketOrder, double _limitPrice) {
    orderId = _orderId;
    quantity = _quantity;
    isMarketOrder = _isMarketOrder;
    limitPrice = _limitPrice;
    arrival = arrivalIndex++;
}

std::string Order::print() const {
    std::stringstream out;
    std::ostringstream doubleStream;
    doubleStream << std::setprecision(3) << std::noshowpoint << limitPrice;
    std::string strLimitPrice = doubleStream.str();

    out << orderId << " " << (isMarketOrder ? "M" : strLimitPrice) << " " << quantity << " " << arrival;

    return out.str();
}

std::string Order::getOrderId() const {
    return orderId;
}

int Order::getQuantity() const {
    return quantity;
}

double Order::getLimitPrice() const {
    return limitPrice;
}

bool Order::getIsMarketOrder() const {
    return isMarketOrder;
}

int Order::getArrival() const {
    return arrival;
}