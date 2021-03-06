#include "IntermediateReader.h"

bool IntermediateReader::hasNextLine() {
    string line;
    bool isTrue;
    do {
        isTrue = ((bool) getline(in, line));
        line = autalities::removeLeadingSpaces(line);
    } while (isTrue && line.empty());
    initVariables();
    currentLine = line;
    if (isTrue) {
        stringstream ss(line);
        string tmp;
        ss >> tmp;
        if (tmp[0] != '*') {
            ss >> locator;
            getline(ss, line);
            if (locator[0] == '.') {
                isComment = true;
            } else {
                parse(line);
            }
        } else {
            //comment or warning
            isComment = true;
        }
    }
    return isTrue;
}
