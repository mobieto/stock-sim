#include "FileReader.h"
#include "BuyOrder.h"
#include "SellOrder.h"
#include "Order.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <queue>
#include <sstream>

class compare {
    public:
        bool operator() (Order* a, Order* b) { return *a < *b; };
};

std::vector<std::string> getParts(std::string in) {
    std::vector<std::string> out;
    std::stringstream stream(in);
    std::string current;

    while (stream >> current) {
        out.push_back(current);
    }

    return out;
}

void display(double lastTradingPrice, std::priority_queue<BuyOrder*, std::vector<BuyOrder*>, compare> buyOrders, std::priority_queue<SellOrder*, std::vector<SellOrder*>, compare> sellOrders) {
    std::cout << "Last trading price: " << lastTradingPrice << std::endl;
    std::cout << "Buy                           Sell" << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    std::vector<BuyOrder*> buyList;
    std::vector<SellOrder*> sellList;

    while (!buyOrders.empty()) {
        buyList.push_back(buyOrders.top());
        buyOrders.pop();
    }

    while (!sellOrders.empty()) {
        sellList.push_back(sellOrders.top());
        sellOrders.pop();
    }

    int maxSize = std::max(buyList.size(), sellList.size());

    for (int i = 0; i < maxSize; i++) {
        int s = 0;

        if (i < buyList.size()) {
            const BuyOrder* order = buyList[i];
            s = order->print().size();
            std::cout << order->print();
        }

        std::cout << std::string(30 - s, ' ');

        if (i < sellList.size()) {
            const SellOrder* order = sellList[i];
            std::cout << order->print();
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

template<typename T>
void processOrder(Order* order,
        T& matchedQueue,
        std::vector<std::string>& successfulTrades,
        double& lastTradingPrice) {
    while (order->getQuantity() > 0 && !matchedQueue.empty()) {
        Order* top = matchedQueue.top();

        if (((order->getType() == "B" && order->getLimitPrice() < top->getLimitPrice()) ||
            (order->getType() == "S" && order->getLimitPrice() > top->getLimitPrice())) &&
            (!order->getIsMarketOrder() && !top->getIsMarketOrder()))
            break;
        
        int tradeQuantity = std::min(order->getQuantity(), top->getQuantity());
        double executionPrice = (order->getIsMarketOrder() && top->getIsMarketOrder()) ? lastTradingPrice :
            (order->getIsMarketOrder() && !top->getIsMarketOrder()) ? top->getLimitPrice() :
            (!order->getIsMarketOrder() && top->getIsMarketOrder()) ? order->getLimitPrice() :
            top->getLimitPrice();
        
        std::stringstream purOut;
        std::stringstream sellOut;
        purOut << std::fixed << std::setprecision(2);
        sellOut << std::fixed << std::setprecision(2);

        if (order->getType() == "B")
            purOut << "order " << order->getOrderId() << " " << tradeQuantity << " shares purchased at price " << executionPrice;
        if (top->getType() == "B")    
            purOut << "order " << top->getOrderId() << " " << tradeQuantity << " shares purchased at price " << executionPrice;
        if (order->getType() == "S")
            sellOut << "order " << order->getOrderId() << " " << tradeQuantity << " shares sold at price " << executionPrice;
        if (top->getType() == "S")
            sellOut << "order " << top->getOrderId() << " " << tradeQuantity << " shares sold at price " << executionPrice;

        successfulTrades.push_back(purOut.str());
        successfulTrades.push_back(sellOut.str());

        order->setQuantity(order->getQuantity() - tradeQuantity);
        top->setQuantity(top->getQuantity() - tradeQuantity);

        lastTradingPrice = executionPrice;

        if (top->getQuantity() <= 0) {
            matchedQueue.pop();
        }
    }
}

int main(int argc, char* argv[]) {
    std::string fileName(argv[1]);
    FileReader fileReader(fileName);

    std::vector<std::string> inputs = fileReader.getLines();

    double lastTradingPrice = std::stod(inputs[0]);

    std::vector<Order*> allOrders;
    std::priority_queue<BuyOrder*, std::vector<BuyOrder*>, compare> buyOrders;
    std::priority_queue<SellOrder*, std::vector<SellOrder*>, compare> sellOrders;

    std::vector<std::string> successfulTrades;

    for (std::string input : inputs) {
        std::vector<std::string> split = getParts(input);

        if (split.size() < 2) continue;

        bool isMarketOrder = split.size() < 4;

        if (split[1] == "B") {
            allOrders.push_back(new BuyOrder(split[0], std::stoi(split[2]), isMarketOrder, isMarketOrder ? -1 : std::stod(split[3]), "B"));
        } else {
            allOrders.push_back(new SellOrder(split[0], std::stoi(split[2]), isMarketOrder, isMarketOrder ? -1 : std::stod(split[3]), "S"));
        }
    }

    for (Order* order : allOrders) {
        if (order->getType() == "B") {
            processOrder(order, sellOrders, successfulTrades, lastTradingPrice);
        } else {
            processOrder(order, buyOrders, successfulTrades, lastTradingPrice);
        }

        if (order->getQuantity() <= 0) continue;

        if (order->getType() == "B") {
            buyOrders.push(dynamic_cast<BuyOrder*>(order));
        } else {
            sellOrders.push(dynamic_cast<SellOrder*>(order));
        }

        display(lastTradingPrice, buyOrders, sellOrders);
    }

    std::cout << std::endl << std::endl;

    for (std::string successfulTrade : successfulTrades) {
        std::cout << successfulTrade << std::endl;
    }

    for (Order* order : allOrders) {
        if (order->getQuantity() <= 0) continue;
        std::stringstream out;
        out << std::fixed << std::setprecision(2);
        out << "order " << order->getOrderId() << " " << order->getQuantity() << " shares unexecuted";
        std::cout << out.str() << std::endl;
    }
}