#include "BuyOrder.h"
#include <string>

BuyOrder::BuyOrder(std::string orderId, int quantity, bool isMarketOrder, double limitPrice) {
    orderId = orderId;
    quantity = quantity;
    isMarketOrder = isMarketOrder;
    limitPrice = limitPrice;
};