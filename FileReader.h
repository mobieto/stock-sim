#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <iosfwd>
#include <fstream>
#include <string>

class FileReader {
    public:
        FileReader(std::string fileName);

        ~FileReader();
    private:
        std::fstream stream;
};

#endif
