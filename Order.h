#ifndef ORDER_H_
#define ORDER_H_

#include <string>

class Order {
    public:
        Order(std::string orderId, int quantity, bool isMarketOrder, double limitPrice);

        std::string print() const;

        virtual bool operator<(const Order& other) const = 0;

        std::string getOrderId() const;

        int getQuantity() const;

        double getLimitPrice() const;

        bool getIsMarketOrder() const;

        int getArrival() const;
    protected:
        std::string orderId;

        int quantity;

        double limitPrice;

        bool isMarketOrder;

        int arrival;
};

#endif