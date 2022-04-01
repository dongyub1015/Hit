#pragma once
#include<iostream>
using namespace std;

class Employee {
public:
	string employeeNum_;
	string name_;
	string cl_;
	string phoneNum_;
	string birthDay_;
	string certi_;
	Employee(string employeeNum, string name, string cl, string phoneNum, string birthDay, string certi) :
		employeeNum_(employeeNum), name_(name), cl_(cl), phoneNum_(phoneNum), birthDay_(birthDay), certi_(certi) {

	}

};

