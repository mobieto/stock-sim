#ifndef SELLORDER_H_
#define SELLORDER_H_

#include <string>

class SellOrder {
    public:
        SellOrder(std::string orderId, int quantity, bool isMarketOrder, double limitPrice);

    private:
        std::string orderId;

        int quantity;

        double limitPrice;

        bool isMarketOrder;

        bool pending;
};

#endif