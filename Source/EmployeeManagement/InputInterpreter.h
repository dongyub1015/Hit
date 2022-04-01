#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


class InputInterpreter {
public:
    InputInterpreter(string fileName) : inputFileName_(fileName) {}
    
    //Todo : main의 파라미터로 넘어온 파일이름에 대한 유효성 검사 필요

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

    bool isValidFileName() {
        
        return true;
    }

private:
    string inputFileName_;
};
