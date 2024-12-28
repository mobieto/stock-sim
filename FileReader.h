#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <iosfwd>
#include <fstream>
#include <string>
#include <vector>

class FileReader {
    public:
        FileReader(std::string _fileName);
        ~FileReader();

        std::vector<std::string> getLines();
    private:
        std::ifstream file;
};

#endif
