#include "SellOrder.h"
#include <string>

SellOrder::SellOrder(std::string orderId, int quantity, bool isMarketOrder, double limitPrice) {
    orderId = orderId;
    quantity = quantity;
    isMarketOrder = isMarketOrder;
    limitPrice = limitPrice;
    pending = true;
};