#pragma once

#include <iostream>
#include <string>
using namespace std;

class IOChecker {
public:
    bool isValidFileName(const string fileName) {
        if (fileName.length() <= 4) return false;
        if (fileName.find("/") != string::npos) return false;
        if (fileName.find("\\") != string::npos) return false;
        if (fileName.substr(fileName.size() - 4, 4) != ".txt") return false;

        int dotCount = 0;
        for (const auto character : fileName) {
            if (character == '.') dotCount++;
            if (dotCount > 1) return false;
        }
        return true;
    }

};