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

	vector<string> resultToString(vector <Employee*>* matchingList, string option, string command)
	{
		vector<string> outputStrAll;
		if ((*matchingList).size() == 0) {
			outputStrAll.push_back(command + ",NONE");
			return outputStrAll;
		}

		if (option != "-p") {
			string size_str = to_string((*matchingList).size());
			outputStrAll.push_back(command + "," + size_str);
			return outputStrAll;
		}

		vector<pair<int, Employee*>> v;
		for (auto match : (*matchingList)) {			
			if (stoi(match->getEmployeeNum().substr(0, 2)) >= 0 && stoi(match->getEmployeeNum().substr(0, 2)) <= 21) {
				v.push_back(pair<int, Employee*>(stoi("1" + match->getEmployeeNum()), match));
			}
			else {
				v.push_back(pair<int, Employee*>(stoi(match->getEmployeeNum()), match));
			}
		}
		
		sort(v.begin(), v.end());

		for (int i = 0; i < 5 && i < v.size(); i++) {
			string output = command + ",";
			// Todo : EmployeeNum 뿐 아니라 전체 data 입력 필요
			output += (v[i].second->getEmployeeNum());
			outputStrAll.push_back(output);
		}
		return outputStrAll;
	}

private:
    const string outputFileName_;
};
