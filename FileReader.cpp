#include "FileReader.h"
#include <fstream>
#include <string>

FileReader::FileReader(std::string fileName) {
    stream.open(fileName.c_str());
}

FileReader::~FileReader() {
    stream.close();
}