#include <iostream>
#include <string>
#include "FileReader.h"
#include "BuyOrder.h"
#include "SellOrder.h"
#include <vector>

int main(int argc, char* argv[]) {
    std::string fileName(argv[1]);

    FileReader fileReader(fileName);

    std::vector<std::string> x = fileReader.getLines();

    for (std::string a : x) {
        std::cout << a << std::endl;
    }
}