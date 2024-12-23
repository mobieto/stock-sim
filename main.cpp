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

std::vector<std::string> getParts(std::string in) {
    std::vector<std::string> out;
    std::stringstream stream(in);
    std::string current;

    while (stream >> current) {
        out.push_back(current);
    }

    return out;
}

void display(double lastTradingPrice, std::priority_queue<BuyOrder> buyOrders, std::priority_queue<SellOrder> sellOrders) {
    std::cout << "Last trading price: " << lastTradingPrice << std::endl;
    std::cout << "Buy                           Sell" << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    std::vector<BuyOrder> buyList;
    std::vector<SellOrder> sellList;

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
            const BuyOrder& order = buyList[i];
            s = order.print().size();
            std::cout << order.print();
        }

        std::cout << std::string(30 - s, ' ');

        if (i < sellList.size()) {
            const SellOrder& order = sellList[i];
            std::cout << order.print();
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

template<typename T>
void processOrder(Order* order,
        T& matchedQueue,
        std::vector<std::string>& successfulTrades) {
    std::cout << order->print() << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << std::fixed << std::setprecision(2);

    std::string fileName(argv[1]);
    FileReader fileReader(fileName);

    std::vector<std::string> inputs = fileReader.getLines();

    double lastTradingPrice = std::stod(inputs[0]);

    std::vector<Order*> allOrders;
    std::priority_queue<BuyOrder> buyOrders;
    std::priority_queue<SellOrder> sellOrders;

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
            buyOrders.push(*dynamic_cast<BuyOrder*>(order));
        } else {
            sellOrders.push(*dynamic_cast<SellOrder*>(order));
        }

        display(lastTradingPrice, buyOrders, sellOrders);
        
        if (order->getType() == "B") {
            processOrder(order, sellOrders, successfulTrades);
        } else {
            processOrder(order, buyOrders, successfulTrades);
        }
    }
}