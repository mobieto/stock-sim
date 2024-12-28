#include "FileReader.h"

FileReader::FileReader(std::string _fileName) {
    file.open(_fileName);
}

FileReader::~FileReader() {
    file.close();
}

std::vector<std::string> FileReader::getLines() {
    std::string line;
    std::vector<std::string> out;

    while (std::getline(file, line)) {
        out.push_back(line);
    }

    return out;
}