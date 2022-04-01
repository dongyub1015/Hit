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
        if (inputFileName_.length() <= 4) return false;
        if (inputFileName_.find("/") != string::npos) return false;
        if (inputFileName_.find("\\") != string::npos) return false;
        if (inputFileName_.substr(inputFileName_.size() - 4, 4) != ".txt") return false;

        int dotCount = 0;
        for (auto character : inputFileName_) {
            if (character == '.') dotCount++;
            if (dotCount > 1) return false;
        }
        return true;
    }

private:
    string inputFileName_;
};
