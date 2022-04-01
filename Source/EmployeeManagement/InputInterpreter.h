#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


class InputInterpreter {
public:
    InputInterpreter(string name) : inputName_(name) {}

    bool openFile() {
        ifstream fin(inputName_); 
        fin.close();
        return fin.is_open();
    }

    string readFile() {
        ifstream fin(inputName_);
        fin.close();
        return "aa";
    }

private:
    string inputName_;
};
