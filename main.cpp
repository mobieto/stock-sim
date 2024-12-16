#include "FileReader.h"
#include "BuyOrder.h"
#include "SellOrder.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::cout << std::fixed << std::setprecision(2);

    std::string fileName(argv[1]);

    FileReader fileReader(fileName);

    std::vector<std::string> inputs = fileReader.getLines();

    double lastTradingPrice = std::stod(inputs[0]);

    std::cout << "Last trading price: " << lastTradingPrice << std::endl;

    for (std::string a : inputs) {
        // split - item 0 is B/S, item 1 is quant, item 2 is market order/limit price
        
    }
}