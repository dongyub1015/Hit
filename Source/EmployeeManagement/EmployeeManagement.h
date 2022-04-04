#pragma once
#include<iostream>
#include<vector>
#include"Employee.h"
#include"Condition.h"
#include"Search.h"


using namespace std;


class EmployeeManagement {
private:
	bool isNumber(const string& str)
	{
		for (char const& c : str) {
			if (std::isdigit(c) == 0) return false;
		}
		return true;
	}

	vector<string>* spiltStr(const string ref, const string delim) {
		vector<string>* spiltStr = new vector<string>(0);
		string token;
		int spos = 0, len = delim.size(), epos;

		while ((epos = ref.find(delim, spos)) != string::npos) {
			token = ref.substr(spos, epos - spos);
			spos = epos + len;
			spiltStr->push_back(token);
		}

		spiltStr->push_back(ref.substr(spos));
		return spiltStr;
	}

	bool isValidEmployeeInfo(Employee* empl) {
		/* check EmployeeNum */
		if (!isNumber(empl->getEmployeeNum())) {
			return false;
		}
		/* Name can be any character and numbers */
		/* check cl */
		if (empl->getCL() != "CL1" && empl->getCL() != "CL2" &&
			empl->getCL() != "CL3" && empl->getCL() != "CL4") {
			return false;
		}
		/* check Phone Number */
		vector<string>* phonenumlList = spiltStr(empl->getPhoneNum(), "-");
		if (phonenumlList->size() != 3 || (*phonenumlList)[0] != "010" || (*phonenumlList)[1].size() != 4 ||
			(*phonenumlList)[2].size() != 4 || !isNumber((*phonenumlList)[1]) || !isNumber((*phonenumlList)[2])) {
			return false;
		}	

		/* check Birthday*/
		if ((empl->getBirthday()).size() != 8) {
			return false;
		}
		string yyyy = (empl->getBirthday()).substr(0, 4);
		string mm = (empl->getBirthday()).substr(4, 2);
		string dd = (empl->getBirthday()).substr(6, 2);

		if (stoi(yyyy) < 1900 || stoi(yyyy) > 2021) {
			return false;
		}
		if (stoi(mm) < 1 || stoi(mm) > 12) {
			return false;
		}
		if (stoi(dd) < 1 || stoi(dd) > 31) {
			return false;
		}
		/* check Certi*/
		if (empl->getCerti() != "ADV" && empl->getCerti() != "PRO" && empl->getCerti() != "EX") {
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
	vector<Employee*>* searchEmployee(vector<SearchCond*>* cond, bool findNdel) {
	//	/* TODO: find out Condition type by using decltyp fucntion */

		return searchEnginePtr_->doSearch(cond, findNdel);
	}
	

	vector<Employee*>* modifyEmployee(vector<SearchCond*>* cond, const SEARCHTYPE type, const string modField) {
		return searchEnginePtr_->doSearchnModify(cond, type, modField);
	}
};




