#pragma once
#include<iostream>
#include<string>
#include "Condition.h"
#include "EmployeeManagement.h"
#include "ValidityChecker.h"

using namespace std;


class Command {
private:
protected:
	string commandStr_;
	string option1_;
	string option2_;
	Condition* condition_ = nullptr;
	ValidChecker* validChecker_;
	string type_;

	vector<string> employeeResultToString(vector<Employee> employResult);
public:
	Command() { validChecker_ = new ValidChecker(); }
	void setCommandString(const string& commandStr) { commandStr_ = commandStr; }
	vector<string> makeResult(EmployeeManagement* EM, const string& command);
	virtual vector<Employee> runCommand(EmployeeManagement* EM) { return vector<Employee>(); }
};

class AddCommand :public Command {
public:
	AddCommand() { type_ = "ADD";}
	virtual vector<Employee> runCommand(EmployeeManagement* EM) override;
};


class DelCommand :public Command {
public:
	DelCommand() { type_ = "DEL"; }
	virtual vector<Employee> runCommand(EmployeeManagement* EM) override;
};


class SchCommand :public Command {
public:
	SchCommand() { type_ = "SCH"; }
	virtual vector<Employee> runCommand(EmployeeManagement* EM) override;
};


class ModCommand :public Command {
public:
	ModCommand() { type_ = "MOD"; }
	virtual vector<Employee> runCommand(EmployeeManagement* EM) override;
};

