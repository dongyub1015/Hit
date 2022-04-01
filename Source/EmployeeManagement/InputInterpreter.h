#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


class InputInterpreter {
public:
    InputInterpreter(string name) : inputName_(name) {}

    vector<string> readFile() {
        ifstream fin(inputName_);
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
    string inputName_;
};
