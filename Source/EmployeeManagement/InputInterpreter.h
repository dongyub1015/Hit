#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


class InputInterpreter {
public:
    InputInterpreter(string fileName) : inputFileName_(fileName) {}

    vector<string> readFile() {
        ifstream fin(inputFileName_);
        vector<string> inputStrAll;
        string line;
        while (!fin.eof()) {
            getline(fin, line);
            inputStrAll.push_back(line);
        }
        fin.close();
        return inputStrAll;
    }

private:
    string inputFileName_;
};
