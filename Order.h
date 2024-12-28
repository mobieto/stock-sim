#ifndef ORDER_H_
#define ORDER_H_

#include <string>
#include <vector>
#include <queue>

class BuyOrder;
class SellOrder;
class Comparison;

class Order {
    public:
        Order(std::string orderId, int quantity, bool isMarketOrder, double limitPrice);

        std::string print() const;

        std::string getOrderId() const;

        int getQuantity() const;

        double getLimitPrice() const;

        bool getIsMarketOrder() const;

        int getArrival() const;

        void setQuantity(int _quantity);

        virtual bool operator<(const Order& other) const = 0;

        virtual void process(std::priority_queue<BuyOrder*, std::vector<BuyOrder*>, Comparison>& buyQueue,
            std::priority_queue<SellOrder*, std::vector<SellOrder*>, Comparison>& sellQueue, 
            std::vector<std::string>& tradeResults, double& lastTradingPrice) = 0;
    protected:
        std::string orderId;

        int quantity;

        double limitPrice;

        bool isMarketOrder;

        int arrival;
};

class Comparison {
    public:
        bool operator()(Order* a, Order* b) { return *a < *b; };
};

#endif