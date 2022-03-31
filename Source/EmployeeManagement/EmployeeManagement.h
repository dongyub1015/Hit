#pragma once



#include<iostream>
#include<vector>
#include"Employee.h"
#include"Condition.h"

using namespace std;

class EmployeeManagement {
private:
	vector<Employee> emList_;

public:
	bool addEmployee(string employeeNum, string name, string cl, string phoneNum, string birthday, string cert) {
		return true;
	}

	bool deleteEmployee(Condition& cond) {
		return true;
	}
	bool searchEmployee(Condition& cond) {
		return true;
	}
	bool modifyEmployee(string employeeNum, string name, string cl, string phoneNum, string birthday, string cert) {
		return true;
	}
};




