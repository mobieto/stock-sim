#include "BuyOrder.h"
#include "Order.h"
#include <iostream>
#include <string>

BuyOrder::BuyOrder(std::string orderId, int quantity, bool isMarketOrder, double limitPrice, std::string type) : Order(orderId, quantity, isMarketOrder, limitPrice, type) { };

bool BuyOrder::operator<(const Order& other) const {
    if (isMarketOrder && !other.getIsMarketOrder()) return false;
    if (!isMarketOrder && other.getIsMarketOrder()) return true;

    if (limitPrice != other.getLimitPrice()) return limitPrice < other.getLimitPrice();

    return arrival > other.getArrival();
};