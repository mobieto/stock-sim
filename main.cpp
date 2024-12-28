#include "FileReader.h"
#include "BuyOrder.h"
#include "SellOrder.h"
#include "FileWriter.h"
#include "Order.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <queue>
#include <sstream>

std::vector<std::string> getParts(std::string in) { // Helper function to split string into vector of words
    std::vector<std::string> out;
    std::stringstream stream(in);
    std::string current;

    while (stream >> current) {
        out.push_back(current);
    }

    return out;
}

void display(double lastTradingPrice, // Function to pretty print pending orders
        std::priority_queue<BuyOrder*, std::vector<BuyOrder*>, Comparison> buyOrders,
        std::priority_queue<SellOrder*, std::vector<SellOrder*>, Comparison> sellOrders) {
    std::cout << std::endl << "------------------- PENDING ORDERS -------------------" << std::endl;
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
            s = buyList[i]->print().size();
            std::cout << buyList[i]->print();
        }

        std::cout << std::string(30 - s, ' ');

        if (i < sellList.size()) {
            std::cout << sellList[i]->print();
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    std::string fileName(argv[1]);
    std::string suffix = fileName.substr(5);

    FileReader fileReader(fileName);
    FileWriter fileWriter("output" + suffix);

    std::vector<std::string> inputs = fileReader.getLines();
    std::vector<std::string> tradeResults;
    std::vector<std::unique_ptr<Order>> allOrders;
    std::priority_queue<BuyOrder*, std::vector<BuyOrder*>, Comparison> buyOrders;
    std::priority_queue<SellOrder*, std::vector<SellOrder*>, Comparison> sellOrders;

    double lastTradingPrice = std::stod(inputs[0]);

    for (std::string input : inputs) { // Go through input lines and create new Order object for each
        std::vector<std::string> split = getParts(input);

        if (split.size() < 2) continue; // Skip first line (last trading price)

        std::string id = split[0];
        int quantity = std::stoi(split[2]);
        bool isMarketOrder = split.size() < 4;
        double price = isMarketOrder ? -1 : std::stod(split[3]);

        if (split[1] == "B") {
            allOrders.push_back(std::unique_ptr<BuyOrder>( 
                new BuyOrder(id, quantity, isMarketOrder, price)
            ));
        } else {
            allOrders.push_back(std::unique_ptr<SellOrder>(
                new SellOrder(id, quantity, isMarketOrder, price)
            ));
        }
    }

    std::cout << std::fixed << std::setprecision(2);

    for (auto&& order : allOrders) { // Loop through each order, process and display pending
        order->process(buyOrders, sellOrders, tradeResults, lastTradingPrice);
        display(lastTradingPrice, buyOrders, sellOrders);
    }

    int numUnexecuted = 0;
    int numTrades = 0;

    for (auto&& order : allOrders) { // Log unexecuted orders
        if (order->getQuantity() <= 0) continue;

        std::stringstream out;
        out << std::fixed << std::setprecision(2);
        out << "order " << order->getOrderId() << " " << order->getQuantity() << " shares unexecuted";
        tradeResults.push_back(out.str());
        numUnexecuted++;
    }

    for (std::string tradeResult : tradeResults) // Write successful & unexecuted orders to file
        fileWriter.writeLine(tradeResult, numTrades++ < tradeResults.size() - 1); // Dont put endl at end of file

    std::cout << "ALL ORDERS MATCHED, " << numUnexecuted << " ORDERS NOT FULLY EXECUTED" << std::endl;
}