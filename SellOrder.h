#ifndef SELLORDER_H_
#define SELLORDER_H_

#include "Order.h"

class BuyOrder;

class SellOrder : public Order {
    using Order::Order;
    
    public:
        SellOrder(std::string orderId, int quantity, bool isMarketOrder, double limitPrice);

        bool operator<(const Order& other) const;

        void process(std::priority_queue<BuyOrder*, std::vector<BuyOrder*>, Comparison>& buyQueue,
            std::priority_queue<SellOrder*, std::vector<SellOrder*>, Comparison>& sellQueue, 
            std::vector<std::string>& tradeResults, double& lastTradingPrice);
};

#endif