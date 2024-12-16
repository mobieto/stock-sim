#ifndef ORDER_H_
#define ORDER_H_

#include <string>

class Order {
    public:
        Order(std::string orderId, int quantity, bool isMarketOrder, double limitPrice);

        std::string print() const;
        
    private:
        std::string orderId;

        int quantity;

        double limitPrice;

        bool isMarketOrder;

        bool pending;
};

#endif