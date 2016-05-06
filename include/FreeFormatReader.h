#ifndef FREEFORMATREADER_H
#define FREEFORMATREADER_H
#include "InputReader.h"

class FreeFormatReader : public InputReader {
public:
    FreeFormatReader(string fileName): InputReader(fileName) {}
    bool hasNextLine() override;
    void parse(string &line);
protected:
private:

};

#endif // FREEFORMATREADER_H
