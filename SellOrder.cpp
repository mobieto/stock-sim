#include "SellOrder.h"
#include "Order.h"
#include <string>
#include <iostream>

SellOrder::SellOrder(std::string orderId, int quantity, bool isMarketOrder, double limitPrice, std::string type) : Order(orderId, quantity, isMarketOrder, limitPrice, type) { };

bool SellOrder::operator<(const Order& other) const {
    if (isMarketOrder && !other.getIsMarketOrder()) return false;
    if (!isMarketOrder && other.getIsMarketOrder()) return true;
    
    if (limitPrice != other.getLimitPrice()) return limitPrice > other.getLimitPrice();

    return arrival > other.getArrival();
};