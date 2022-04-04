#pragma once
#include<iostream>
#include<vector>
#include"Employee.h"
#include"Condition.h"
#include"Search.h"
#include"ValidityChecker.h"


using namespace std;


class EmployeeManagement {
private:
	bool isValidEmployeeInfo(Employee* empl) {
		ValidChecker checker;

		/* check EmployeeNum */
		if (!checker.IsNumberString(empl->getEmployeeNum())) {
			return false;
		}
		/* Name can be any character and numbers */
		/* check cl */
		if (!checker.checkCL(empl->getCL())) {
			return false;
		}
		/* check Phone Number */
		if (!checker.checkPhoneNum(empl->getPhoneNum())) {
			return false;
		}

		/* check Birthday*/
		if (!checker.checkBirthday(empl->getBirthday())) {
			return false;
		}

		/* check Certi*/
		if (!checker.checkCertiGrade(empl->getCerti())) {
			return false;
		}
		return true;
	}

public:
	vector<Employee*> emList_;
	//vector<SearchEngine*> searchEngineList_;
	SearchEngine* searchEnginePtr_;
	EmployeeManagement() {
		searchEnginePtr_ = new MultiSearch(&emList_);
	};

	bool addEmployee(string employeeNum, string name, string cl, string phoneNum, string birthday, string cert) {
		/* PREMISE: assume all parameters are valid */

		//Employee* empl = new Employee(employeeNum,  name, cl, phoneNum, birthday,cert);
		Employee* empl(new Employee(employeeNum, name, cl, phoneNum, birthday, cert));
		/* TODO: checking if information is valid */
		if (!isValidEmployeeInfo(empl)) {
			return false;
		}

		/*add obj to List */
		emList_.push_back(empl);
		return true;
	}

	bool deleteEmployee(Condition& cond) {
		return true;
	}
	vector<Employee*>* searchEmployee(vector<SearchCond*>* cond, bool findNdel) {
		//	/* TODO: find out Condition type by using decltyp fucntion */

		return searchEnginePtr_->doSearch(cond, findNdel);
	}


	vector<Employee*>* modifyEmployee(vector<SearchCond*>* cond, SEARCHTYPE type, string modField) {
		return searchEnginePtr_->doSearchnModify(cond, type, modField);
	}
};




