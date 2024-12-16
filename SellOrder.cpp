#include "SellOrder.h"
#include "Order.h"
#include <string>

SellOrder::SellOrder(std::string orderId, int quantity, bool isMarketOrder, double limitPrice) : Order(orderId, quantity, isMarketOrder, limitPrice) { };