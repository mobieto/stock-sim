#include "Order.h"
#include "SellOrder.h"
#include "BuyOrder.h"
#include <iostream>
#include <sstream>
#include <iomanip>

SellOrder::SellOrder(std::string orderId, int quantity, bool isMarketOrder, double limitPrice) : Order(orderId, quantity, isMarketOrder, limitPrice) { };

bool SellOrder::operator<(const Order& other) const { // For priority queue sorting
    if (this->getIsMarketOrder() && !other.getIsMarketOrder()) return false;
    if (!this->getIsMarketOrder() && other.getIsMarketOrder()) return true;
    
    if (this->getLimitPrice() != other.getLimitPrice()) return this->getLimitPrice() > other.getLimitPrice();

    return this->getArrival() > other.getArrival();
};

void SellOrder::process(std::priority_queue<BuyOrder*, std::vector<BuyOrder*>, Comparison>& buyQueue,
        std::priority_queue<SellOrder*, std::vector<SellOrder*>, Comparison>& sellQueue, 
        std::vector<std::string>& tradeResults, double& lastTradingPrice) {
    while (this->getQuantity() > 0 && !buyQueue.empty()) { // Loop until order fully executed or no matchable orders
        BuyOrder* top = buyQueue.top();

        if ((this->getLimitPrice() > top->getLimitPrice()) && (!this->getIsMarketOrder() && !top->getIsMarketOrder()))
            break; // Stop if buy order is buying for too little
        
        int tradeQuantity = std::min(this->getQuantity(), top->getQuantity());
        double executionPrice = (this->getIsMarketOrder() && top->getIsMarketOrder()) ? lastTradingPrice :
            (this->getIsMarketOrder() && !top->getIsMarketOrder()) ? top->getLimitPrice() :
            (!this->getIsMarketOrder() && top->getIsMarketOrder()) ? this->getLimitPrice() :
            top->getLimitPrice(); // Last trading price if both market orders, limit price if other is market order, or earlier limit price if neither market order
        
        std::stringstream purOut;
        std::stringstream sellOut;
        purOut << std::fixed << std::setprecision(2);
        sellOut << std::fixed << std::setprecision(2);

        purOut << "order " << top->getOrderId() << " " << tradeQuantity << " shares purchased at price " << executionPrice;
        sellOut << "order " << this->getOrderId() << " " << tradeQuantity << " shares sold at price " << executionPrice;

        std::cout << "Matched orders: " << this->getOrderId() << " & " << top->getOrderId() << " | Executed at price: " << executionPrice << " | Shares traded: " << tradeQuantity << std::endl;

        tradeResults.push_back(purOut.str());
        tradeResults.push_back(sellOut.str());

        this->setQuantity(this->getQuantity() - tradeQuantity);
        top->setQuantity(top->getQuantity() - tradeQuantity);

        lastTradingPrice = executionPrice; // Set last trading price to this traded price

        if (top->getQuantity() <= 0) // Remove the other order from queue if it's fully executed
            buyQueue.pop();
    }

    if (this->getQuantity() > 0) // Add this order to pending orders if not fully executed
        sellQueue.push(this);
}