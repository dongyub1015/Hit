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
	bool isDuplicatedEmployeeNum(Employee* empl) {
		for (auto e : emList_) {
			if (e->getEmployeeNum() == empl->getEmployeeNum()) return true;
		}
		return false;
	}

	bool isValidEmployeeInfo(Employee* empl) {
		ValidChecker checker;

		/* check EmployeeNum */
		if (!checker.IsNumberString(empl->getEmployeeNum())) {
			return false;
		}
		/* check duplicated employee number */
		if (isDuplicatedEmployeeNum(empl)) return false;

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
	void printAllEmployee() {
		cout << "=====================================================" << endl;
		for (auto e : emList_) {
			cout << e->toString() << endl;
		}
		cout << "=====================================================\n" << endl;
	}
	bool addEmployee(const string employeeNum, const string name, const string cl, const string phoneNum, const string birthday, const string cert) {
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
	vector<Employee> deleteEmployee_(Condition& cond) {
		vector<Employee> result;
		for (auto it = emList_.begin(); it != emList_.end();) {
			if (cond.isMatch(**it)) {
				result.push_back(**it);
				it = emList_.erase(it);
			}
			else {
				it++;
			}
		}
		return result;
	}
	vector<Employee*>* searchEmployee(vector<SearchCond*>* cond, bool findNdel) {
	//	/* TODO: find out Condition type by using decltyp fucntion */

		return searchEnginePtr_->doSearch(cond, findNdel);
	}
	
	vector<Employee> searchEmployee(Condition& cond) {
		vector<Employee> result;
		for (auto e : emList_) {
			if (cond.isMatch(*e)) {
				result.push_back(*e);
			}
		}
		return result;
	}

	vector<Employee*>* modifyEmployee(vector<SearchCond*>* cond, const SEARCHTYPE type, const string modField) {
		return searchEnginePtr_->doSearchnModify(cond, type, modField);
	}
	vector<Employee> modifyEmployee(Condition& cond, const string& column, const string& value) {
		vector<Employee> result;
		for (auto e : emList_) {
			if (cond.isMatch(*e)) {
				result.push_back(*e);
				searchEnginePtr_->setEmployeeField(e, column, value);
			}
		}
		return result;
	}
};




