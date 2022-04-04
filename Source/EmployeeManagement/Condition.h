#pragma once
#include<iostream>
#include<string>
#include "Employee.h"

using namespace std;

class Condition {
private:
	string compareString_;
public:
	Condition() {}
	Condition(string compareString) :compareString_(compareString) {}
	string getCompareString();
	virtual bool isMatch(Employee employee) { return false; };
};

class ConditionEmployeeNum : public Condition {
public:
	ConditionEmployeeNum(string compareString) :Condition(compareString) {}
	virtual bool isMatch(Employee employee) override {
		if (getCompareString() == employee.getEmployeeNum())return true;
		return false;
	}
};

class ConditionCerti : public Condition {
public:
	ConditionCerti(string compareString) :Condition(compareString) {}
	virtual bool isMatch(Employee employee) override {
		if (getCompareString() == employee.getCerti())return true;
		return false;
	}

};

class ConditionCL : public Condition {
public:
	ConditionCL(string compareString) :Condition(compareString) {}
	virtual bool isMatch(Employee employee) override {
		if (getCompareString() == employee.getCL())return true;
		return false;
	}
};


/*Phone Number*/
class ConditionPhoneNumber : public Condition {
public:
	ConditionPhoneNumber(string compareString) :Condition(compareString) {}
	virtual bool isMatch(Employee employee) override {
		if (getCompareString() == employee.getPhoneNum())return true;
		return false;
	}
};

class ConditionMiddlePhoneNumber : public ConditionPhoneNumber {
public:
	ConditionMiddlePhoneNumber(string compareString) :ConditionPhoneNumber(compareString) {}
	virtual bool isMatch(Employee employee) override {
		const size_t sPos = 4;
		const size_t subLen = 4;
		if (getCompareString() == employee.getPhoneNum().substr(sPos, subLen))return true;
		return false;
	}
};

class ConditionLastPhoneNumber : public ConditionPhoneNumber {
public:
	ConditionLastPhoneNumber(string compareString) :ConditionPhoneNumber(compareString) {}
	virtual bool isMatch(Employee employee) override {
		const size_t sPos = 9;
		const size_t subLen = 4;
		if (getCompareString() == employee.getPhoneNum().substr(sPos, subLen))return true;
		return false;
	}
};

/*Name*/
class ConditionName : public Condition {
public:
	ConditionName(string compareString) :Condition(compareString) {}
	virtual bool isMatch(Employee employee) override {
		if (getCompareString() == employee.getName())return true;
		return false;
	}
};

class ConditionFirstName : public ConditionName {
public:
	ConditionFirstName(string compareString) :ConditionName(compareString) {}
	virtual bool isMatch(Employee employee) override {
		const size_t sPos = 0;
		const size_t subLen = employee.getName().find(' ');
		if (getCompareString() == employee.getName().substr(sPos, subLen))return true;
		return false;
	}
};

class ConditionLastName : public ConditionName {
public:
	ConditionLastName(string compareString) :ConditionName(compareString) {}
	virtual bool isMatch(Employee employee) override {
		const size_t sPos = employee.getName().find(' ') + 1;
		const size_t subLen = employee.getName().length() - sPos;
		if (getCompareString() == employee.getName().substr(sPos, subLen))return true;
		return false;
	}
};

/*Birthday*/
class ConditionBirthday : public Condition {
public:
	ConditionBirthday(string compareString) :Condition(compareString) {}
	virtual bool isMatch(Employee employee) override {
		if (getCompareString() == employee.getBirthday())return true;
		return false;
	}
};

class ConditionDayBirthday : public ConditionBirthday {
public:
	ConditionDayBirthday(string compareString) :ConditionBirthday(compareString) {}
	virtual bool isMatch(Employee employee) override {
		const size_t sPos = 6;
		const size_t subLen = 2;
		if (getCompareString() == employee.getBirthday().substr(sPos, subLen))return true;
		return false;
	}
};

class ConditionMonthBirthday : public ConditionBirthday {
public:
	ConditionMonthBirthday(string compareString) :ConditionBirthday(compareString) {}
	virtual bool isMatch(Employee employee) override {
		const size_t sPos = 4;
		const size_t subLen = 2;
		if (getCompareString() == employee.getBirthday().substr(sPos, subLen))return true;
		return false;
	}
};

class ConditionYearBirthday : public ConditionBirthday {
public:
	ConditionYearBirthday(string compareString) :ConditionBirthday(compareString) {}
	virtual bool isMatch(Employee employee) override {
		const size_t sPos = 0;
		const size_t subLen = 4;
		if (getCompareString() == employee.getBirthday().substr(sPos, subLen))return true;
		return false;
	}
};
