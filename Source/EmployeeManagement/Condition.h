#pragma once

#include<iostream>
#include<string>

using namespace std;

class Condition {
private:
	string compareString_;
public:
	Condition(string compareString) :compareString_(compareString) {}
	string getCompareString();
};