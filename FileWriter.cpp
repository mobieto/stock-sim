#include "FileWriter.h"
#include <string>

FileWriter::FileWriter(std::string fileName) {
    file.open(fileName);
}

FileWriter::~FileWriter() {
    file.close();
}

void FileWriter::writeLine(std::string line, bool endline) {
    file << line;
    if (endline) file << std::endl;
}