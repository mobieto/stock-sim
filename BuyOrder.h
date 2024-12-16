#ifndef BUYORDER_H_
#define BUYORDER_H_

#include <string>

class BuyOrder {
    public:
        BuyOrder(std::string orderId, int quantity, bool isMarketOrder, double limitPrice);

    private:
        std::string orderId;

        int quantity;

        double limitPrice;

        bool isMarketOrder;
};

#endif