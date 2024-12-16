#include "BuyOrder.h"
#include "Order.h"
#include <string>

BuyOrder::BuyOrder(std::string orderId, int quantity, bool isMarketOrder, double limitPrice) : Order(orderId, quantity, isMarketOrder, limitPrice) { };