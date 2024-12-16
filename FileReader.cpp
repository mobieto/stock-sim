#include "FileReader.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

FileReader::FileReader(std::string _fileName) {
    fileName = _fileName;
}

std::vector<std::string> FileReader::getLines() const {
    std::string line;
    std::ifstream file(fileName);
    std::vector<std::string> out;

    while (std::getline(file, line)) {
        out.push_back(line);
    }

    file.close();

    return out;
}