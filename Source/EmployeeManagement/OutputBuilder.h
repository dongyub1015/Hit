#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include"Employee.h"
using namespace std;

class OutputBuilder {
public:
	OutputBuilder(const string fileName) : outputFileName_(fileName) {}

	vector<string> outputList;

	bool writeFile(vector<string> outputStrAll) {
        ofstream fout(outputFileName_);

        if (fout.fail()) {
            return false;
        }

        for (auto str : outputStrAll) {
            fout << str << endl;
        }
        return true;
    }

private:
    const string outputFileName_;
};
