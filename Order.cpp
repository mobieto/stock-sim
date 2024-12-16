#include "Order.h"
#include <string>
#include <iostream>

Order::Order(std::string _orderId, int _quantity, bool _isMarketOrder, double _limitPrice) {
    orderId = _orderId;
    quantity = _quantity;
    isMarketOrder = _isMarketOrder;
    limitPrice = _limitPrice;
    pending = true;
}

std::string Order::print() const {
    return orderId;
}