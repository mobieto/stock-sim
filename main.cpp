#include "FileReader.h"
#include "BuyOrder.h"
#include "SellOrder.h"
#include "Order.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <queue>

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
        if (i < buyList.size()) {
            const BuyOrder& order = buyList[i];
            std::cout << order.print() << std::string(30 - order.print().size(), ' ');
        }

        if (i < sellList.size()) {
            const SellOrder& order = sellList[i];
            std::cout << order.print();
        }

        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::cout << std::fixed << std::setprecision(2);

    std::string fileName(argv[1]);
    FileReader fileReader(fileName);

    std::vector<std::string> inputs = fileReader.getLines();

    double lastTradingPrice = std::stod(inputs[0]);

    std::priority_queue<BuyOrder> buyOrders;
    std::priority_queue<SellOrder> sellOrders;
    std::vector<std::string> successfulTrades;
    std::vector<Order> unexecutedOrders;

    for (std::string input : inputs) {
        std::vector<std::string> split = getParts(input);

        if (split.size() < 2) continue;

        bool isMarketOrder = split.size() < 4;

        if (split[1] == "B") {
            BuyOrder buyOrder(split[0], std::stoi(split[2]), isMarketOrder, isMarketOrder ? -1 : std::stod(split[3]));
            buyOrders.push(buyOrder);
        } else {
            SellOrder sellOrder(split[0], std::stoi(split[2]), isMarketOrder, isMarketOrder ? -1 : std::stod(split[3]));
            sellOrders.push(sellOrder);
        }
    }
    
    display(lastTradingPrice, buyOrders, sellOrders);
}