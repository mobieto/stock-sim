#ifndef BUYORDER_H_
#define BUYORDER_H_

#include "Order.h"
#include <string>

class BuyOrder : public Order {
    using Order::Order;
    
    public:
        BuyOrder(std::string orderId, int quantity, bool isMarketOrder, double limitPrice);

        bool operator<(const Order& other) const;
};

#endif