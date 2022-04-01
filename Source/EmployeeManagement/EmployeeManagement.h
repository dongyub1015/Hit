#pragma once




#include<iostream>
#include<vector>
#include"Employee.h"
#include"Condition.h"

#define MAX_EMPLOYEE 100000

using namespace std;
enum class SEARCHTYPE {
	BYNAME,
	BYCL,
	BYPHONENUM,
	BYCERTI,
	BYBIRTH
};

class SearchEngine {
public:
	vector<Employee*>* emList_ = nullptr;
	SearchEngine(vector<Employee*>* emList) :emList_(emList) {
	}
	virtual vector<Employee*>* doSearch(string) = 0;
};

class NameSearch : public SearchEngine {
public:
	NameSearch(vector<Employee*>* emList) : SearchEngine(emList) {
	}
	virtual vector<Employee*>* doSearch(string ref) override {
		vector<Employee*>* foundList_ = new vector<Employee*>(0);
		for (auto it : *emList_) {
			if ((*it).getName() == ref) {
				foundList_->push_back(it);
			}
		}
		return foundList_;
	};
};

class EmployeeManagement {
public:
	vector<Employee*> emList_;
	vector<SearchEngine*> searchEngineList_;
	SearchEngine* searchEnginePtr_;
public:
	EmployeeManagement() {
		searchEngineList_.push_back(new NameSearch(&emList_));
		searchEnginePtr_ = searchEngineList_[0];
	};

	bool addEmployee(string employeeNum, string name, string cl, string phoneNum, string birthday, string cert) {
		/* PREMISE: assume all parameters are valid */
		Employee* empl = new Employee(employeeNum, name, cl, phoneNum, birthday, cert);
		/* TODO: checking if information is valid */
		/*add obj to List */
		emList_.push_back(empl);
		return true;
	}

	bool deleteEmployee(Condition& cond) {
		return true;
	}
	vector<Employee*>* searchEmployee(Condition& cond) {
		/* TODO: find out Condition type by using decltyp fucntion */
		return searchEnginePtr_->doSearch(cond.compareString);
	}
	bool modifyEmployee(string employeeNum, string name, string cl, string phoneNum, string birthday, string cert) {
		return true;
	}
};

