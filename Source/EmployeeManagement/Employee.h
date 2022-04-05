#pragma once
#include<iostream>
using namespace std;

#include <string>

class Employee {

private:
	string employeeNum_;
	string name_;
	string cl_;
	string phoneNum_;
	string birthday_;
	string certi_;

protected:
	static int employeeNumToYear(string employeeNum) {
		int employeeNumYear = stoi(employeeNum.substr(0, 2));
		if (68 < employeeNumYear && employeeNumYear < 100)
			employeeNumYear += 1900;
		else
			employeeNumYear += 2000;
		return employeeNumYear;
	}
public:
	Employee() : employeeNum_(""), name_(""), cl_(""), phoneNum_(""), birthday_(""), certi_("") {}

	Employee(string employeeNum, string name, string cl, string phoneNum, string birthday, string certi)
		: employeeNum_(employeeNum), name_(name), cl_(cl), phoneNum_(phoneNum), birthday_(birthday), certi_(certi) {}

	static bool comp(const Employee *e1, const Employee* e2) {
		int e1EmployeeNumYear = employeeNumToYear(e1->employeeNum_);
		int e2EmployeeNumYear = employeeNumToYear(e2->employeeNum_);

		if (e1EmployeeNumYear == e2EmployeeNumYear) {
			return stoi(e1->employeeNum_.substr(2, 6)) < stoi(e2->employeeNum_.substr(2, 6));
		}
		else {
			return e1EmployeeNumYear < e2EmployeeNumYear;
		}
	}

	string toString() {
		return employeeNum_ + "," + name_ + "," + cl_ + "," + phoneNum_ + "," + birthday_ + "," + certi_;
	}

	string getEmployeeNum() {
		return employeeNum_;
	}

	string getName() {
		return name_;
	}

	string getCL() {
		return cl_;
	}

	string getPhoneNum() {
		return phoneNum_;
	}

	string getBirthday() {
		return birthday_;
	}

	string getCerti() {
		return certi_;
	}

	void setEmployeeNum(string employeeNum) {
		employeeNum_ = employeeNum;
	}

	void setName(string name) {
		name_ = name;
	}

	void setCL(string cl) {
		cl_ = cl;
	}

	void setPhoneNum(string phoneNum) {
		phoneNum_ = phoneNum;
	}

	void setBirthday(string birthday) {
		birthday_ = birthday;

	}

	void setCerti(string certi) {
		certi_ = certi;
	}
};

