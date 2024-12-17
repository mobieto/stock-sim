#include "SellOrder.h"
#include "Order.h"
#include <string>

SellOrder::SellOrder(std::string orderId, int quantity, bool isMarketOrder, double limitPrice) : Order(orderId, quantity, isMarketOrder, limitPrice) { };

bool SellOrder::operator<(const Order& other) const {
    if (isMarketOrder && !other.getIsMarketOrder()) return false;
    if (!isMarketOrder && other.getIsMarketOrder()) return true;
    
    if (limitPrice != other.getLimitPrice()) return limitPrice > other.getLimitPrice();

    return arrival > other.getArrival();
};