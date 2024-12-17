#ifndef SELLORDER_H_
#define SELLORDER_H_

#include <string>
#include "Order.h"

class SellOrder : public Order {
    using Order::Order;
    
    public:
        SellOrder(std::string orderId, int quantity, bool isMarketOrder, double limitPrice);

        bool operator<(const Order& other) const;
};

#endif