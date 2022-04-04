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
        vector<string> inputStrAll;
        ifstream fin(inputFileName_);

        if (fin.fail()) {
            cout << "Fail to open Input file" << endl;
            return inputStrAll;
        }

        string line;
        while (getline(fin, line)) {
            inputStrAll.push_back(line);
        }
        fin.close();
        return inputStrAll;
    }

private:
    string inputFileName_;
};
