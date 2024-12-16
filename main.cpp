#include "FileReader.h"
#include "BuyOrder.h"
#include "SellOrder.h"
#include "Order.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <string>

std::vector<std::string> getParts(std::string in) {
    std::vector<std::string> out;
    std::stringstream stream(in);
    std::string current;

    while (stream >> current) {
        out.push_back(current);
    }

    return out;
}

int main(int argc, char* argv[]) {
    std::cout << std::fixed << std::setprecision(2);

    std::string fileName(argv[1]);
    FileReader fileReader(fileName);

    std::vector<std::string> inputs = fileReader.getLines();

    double lastTradingPrice = std::stod(inputs[0]);
    std::vector<Order> orders;

    for (std::string input : inputs) {
        std::vector<std::string> split = getParts(input);

        if (split.size() < 2) continue;

        bool isMarketOrder = split.size() < 4;

        if (split[1] == "B") {
            BuyOrder buyOrder(split[0], std::stoi(split[2]), isMarketOrder, split.size() < 4 ? 0 : std::stod(split[3]));
            orders.push_back(buyOrder);
        } else {
            SellOrder sellOrder(split[0], std::stoi(split[2]), isMarketOrder, split.size() < 4 ? 0 : std::stod(split[3]));
            orders.push_back(sellOrder);
        }
    }

    std::cout << "Last trading price: " << lastTradingPrice << std::endl;

    for (Order order : orders) {
        std::cout << order.print() << std::endl;
    }
}