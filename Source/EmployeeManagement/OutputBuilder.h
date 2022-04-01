#pragma once

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class OutputBuilder {
public:
	OutputBuilder(string fileName) : outputFileName_(fileName) {}

	vector<string> outputList;

	bool writeFile(vector<string> outputStrAll) {

		return true;
	}


private:
	string outputFileName_;
};
