#include "FileWriter.h"
#include <string>

FileWriter::FileWriter(std::string fileName) {
    file.open(fileName);
}

FileWriter::~FileWriter() {
    file.close();
}

void FileWriter::writeLine(std::string line) {
    file << line << std::endl;
}