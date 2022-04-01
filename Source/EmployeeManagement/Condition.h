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
	virtual bool isMatch(Employee employee) { return false; }
};

class ConditionEmployeeNum : public Condition {

};

class ConditionCerti : public Condition {


};

class ConditionCL : public Condition {


};


/*Phone Number*/
class ConditionPhoneNumber : public Condition {


};

class ConditionLastPhoneNumber : public ConditionPhoneNumber {


};

class ConditionMiddlePhoneNumber : public ConditionPhoneNumber {


};


/*Name*/
class ConditionName : public Condition {


};

class ConditionFirstName : public ConditionName {


};

class ConditionLastName : public ConditionName {


};

/*Birthday*/
class ConditionBirthday : public Condition {


};

class ConditionDayBirthday : public ConditionBirthday {


};

class ConditionMonthBirthday : public ConditionBirthday {


};
class ConditionYearBirthday : public ConditionBirthday {


};


