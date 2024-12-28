#ifndef FILEWRITER_H_
#define FILEWRITER_H_

#include <fstream>
#include <string>
#include <vector>

class FileWriter {
    public:
        FileWriter(std::string _fileName);
        ~FileWriter();

        void writeLine(std::string line, bool endl);
    private:
        std::ofstream file;
};

#endif