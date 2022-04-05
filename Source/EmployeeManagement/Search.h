#pragma once
#include<iostream>
#include<vector>
#include <sstream>
#include<map>
#include"Employee.h"
using namespace std;


#define MAX_EMPLOYEE 100000
enum class SEARCHTYPE {
	BYEMPLOYEENUM = 0,
	BYNAME,
	BYCL,
	BYPHONENUM,
	BYBIRTH,
	BYCERTI,
	TYPEERROR
};

enum class PHONEIDX {
	FIRST_F = 0,
	SECOND_F,
	THIRD_F,
	NONE
};

class SearchCond {
private:
	SEARCHTYPE searchType_;
protected:
	string refstr_;
public:
	SearchCond(SEARCHTYPE serchType, string refstr) :searchType_(serchType), refstr_(refstr) {
	}
	virtual bool isMatched(string inputStr) = 0;
	string getReference() {
		return refstr_;
	}	

	SEARCHTYPE getsSearchType() {
		return searchType_;
	}
	vector<string>* spiltStr(string ref, string delim) {
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
};

class SearchCondStr : public SearchCond {
public:
	SearchCondStr(SEARCHTYPE serchType, string refstr) : SearchCond(serchType, refstr) {	
	}
	virtual bool isMatched(string inputStr) {
		if (inputStr == SearchCond::refstr_) {
			return true;
		}
		return false;
	}

};

class SearchCondName : public SearchCond {
private:
	string refstr_;
	bool firstOrLast_;
	bool fullSearch_;
	string del_;
public:
	SearchCondName(SEARCHTYPE serchType, string refstr) : SearchCond(serchType, refstr) {
		del_ = " ";
		fullSearch_ = true;
	}
	bool setFirstNameSearch() {
		firstOrLast_ = true;
		fullSearch_ = false;
		vector<string>* refStrList = SearchCond::spiltStr(SearchCond::getReference(), del_);
		if (refStrList == nullptr) {
			return false;
		}
		refstr_ = (*refStrList)[0];
		return true;
	}
	bool setLastNameSearch() {
		firstOrLast_ = false;
		fullSearch_ = false;
		vector<string>* refStrList = SearchCond::spiltStr(SearchCond::getReference(), del_);
		if (refStrList == nullptr) {
			return false;
		}
		refstr_ = (*refStrList)[refStrList->size() - 1];
		return true;
	}
	virtual bool isMatched(string refstr) override {
		if (fullSearch_ == true) {
			if (refstr == SearchCond::getReference()) {
				return true;
			}
		}
		else {
			vector<string>* refStrList = SearchCond::spiltStr(refstr, del_);
			if (firstOrLast_) {
				if (refstr_ == (*refStrList)[0]) {
					return true;
				}
			}
			else {
				if (refstr_ == (*refStrList)[refStrList->size() - 1]) {
					return true;
				}
			}
		}
		return false;
	}
};

class SearchCondPhonenum : public SearchCond {
private:
	PHONEIDX searchIdx_;
	bool fullSearch_;
	string del_;
public:
	SearchCondPhonenum(SEARCHTYPE serchType, string refstr) : SearchCond(serchType, refstr) {
		del_ = "-";
		fullSearch_ = true;
	}
	bool setSearchIdx(PHONEIDX idx) {
		searchIdx_ = idx;
		fullSearch_ = false;
		return true;
	}
	virtual bool isMatched(string refstr) override {
		vector<string>* refStrList = SearchCond::spiltStr(refstr, del_);
		if (refStrList->size() < 3) {
			return false;
		}
		if (refstr_ == (*refStrList)[(int)searchIdx_]) {
			return true;
		}
		return false;
	}
};


class SearchCondDate : public SearchCond {
private:
	bool fullSearch_;
	PHONEIDX searchIdx_;
	string dateSpilt(string ref) {
		string retStr;
		switch (searchIdx_) {
		case PHONEIDX::FIRST_F:
			retStr = ref.substr(0, 4);
			break;
		case PHONEIDX::SECOND_F:
			retStr = ref.substr(4, 2);
			break;
		case PHONEIDX::THIRD_F:
			retStr = ref.substr(6, 2);
			break;
		}
		return retStr;
	}
public:
	SearchCondDate(SEARCHTYPE serchType, string refstr) : searchIdx_(PHONEIDX::NONE),
		SearchCond(serchType, refstr) {
		fullSearch_ = true;
	}

	bool setSearchIdx(PHONEIDX idx) {
		searchIdx_ = idx;
		fullSearch_ = false;		
		return true;
	}

	virtual bool isMatched(string refstr) override {
		string tmpRef;

		tmpRef = dateSpilt(refstr);
		if (tmpRef == SearchCond::getReference()) {
			return true;
		}

		return false;
	}
};


class SearchEngine {
public:
	vector<Employee*>* emList_ = nullptr;
	SearchEngine(vector<Employee*>* emList) :emList_(emList) {
	}
	virtual vector<Employee*>* doSearch(vector<SearchCond*> *searchCondList,bool findNdel) = 0;
	virtual vector<Employee*>* doSearchnModify(vector<SearchCond*>* searchCondList, SEARCHTYPE type, string modField) = 0;
};



class MultiSearch : public SearchEngine {
private:
	vector<string> refStr_ = {"employeeNum", "name", "cl", "phoneNum", "birthday", "certi"};
	string getEmployeeField(Employee* employee, SEARCHTYPE searchType) {
		switch (searchType) {
		case SEARCHTYPE::BYEMPLOYEENUM:
			return employee->getEmployeeNum();
		case SEARCHTYPE::BYNAME:
			return employee->getName();
		case SEARCHTYPE::BYCL:
			return employee->getCL();
		case SEARCHTYPE::BYPHONENUM:
			return employee->getPhoneNum();
		case SEARCHTYPE::BYBIRTH:
			return employee->getBirthday();
		case SEARCHTYPE::BYCERTI:
			return employee->getCerti();
		default:
			break;
		}
		return "";
	}

	void setEmployeeField(Employee* employee, SEARCHTYPE searchType, string modField) {
		switch (searchType) {
		case SEARCHTYPE::BYEMPLOYEENUM:
			return employee->setEmployeeNum(modField);
		case SEARCHTYPE::BYNAME:
			return employee->setName(modField);
		case SEARCHTYPE::BYCL:
			return employee->setCL(modField);
		case SEARCHTYPE::BYPHONENUM:
			return employee->setPhoneNum(modField);
		case SEARCHTYPE::BYBIRTH:
			return employee->setBirthday(modField);
		case SEARCHTYPE::BYCERTI:
			return employee->setCerti(modField);
		default:
			break;
		}
		return;
	}

	bool doCondMatching(vector<Employee*>::iterator it,
		vector<Employee*>* foundList_, vector<SearchCond*>* searchCondList, int &idx) {
		
		for (auto cond : (*searchCondList)) {
			string ret = getEmployeeField(*it, (*cond).getsSearchType());
			if ((*cond).isMatched(ret) == true) {
				Employee* tmpEmployee(new Employee());
				/* copy items */
				(*foundList_)[idx] = tmpEmployee;
				(*foundList_)[idx]->setEmployeeNum((*it)->getEmployeeNum());
				(*foundList_)[idx]->setName((*it)->getName());
				(*foundList_)[idx]->setCL((*it)->getCL());
				(*foundList_)[idx]->setPhoneNum((*it)->getPhoneNum());
				(*foundList_)[idx]->setBirthday((*it)->getBirthday());
				(*foundList_)[idx]->setCerti((*it)->getCerti());
				idx++;
				return true;
			}
		}
		return false;
	}
	void doCondModMatching(Employee* employee, SEARCHTYPE type,
							string modField, vector<Employee*>* foundList_,
							vector<SearchCond*>* searchCondList) {
		for (auto cond : (*searchCondList)) {
			string ret = getEmployeeField(employee, (*cond).getsSearchType());
			if ((*cond).isMatched(ret) == true) {
				Employee* tmpEmployee(new Employee());
				tmpEmployee->setEmployeeNum(employee->getEmployeeNum());
				tmpEmployee->setName(employee->getName());
				tmpEmployee->setCL(employee->getCL());
				tmpEmployee->setPhoneNum(employee->getPhoneNum());
				tmpEmployee->setBirthday(employee->getBirthday());
				tmpEmployee->setCerti(employee->getCerti());
				(*foundList_).push_back(tmpEmployee);
				setEmployeeField(employee, type, modField);
				return;
			}
		}
	}

public:
	MultiSearch(vector<Employee*>* emList) : SearchEngine(emList) {
	}
	virtual vector<Employee*>* doSearch(vector<SearchCond*> *searchCondList, bool findNdel) override {
		vector<Employee*>* foundList_ = new vector<Employee*>(MAX_EMPLOYEE);
		int foundList_idx=0;
		bool pushed;

		for (vector<Employee*>::iterator employee = emList_->begin(); employee != (*emList_).end();) {
			if (doCondMatching(employee, foundList_, searchCondList, foundList_idx)) {
				employee = emList_->erase(employee);
				pushed = true;
			}else{
				++employee;
			}
		}

		foundList_->erase(foundList_->begin() + foundList_idx, foundList_->begin() + MAX_EMPLOYEE);
		return foundList_;
	};

	virtual vector<Employee*>* doSearchnModify(vector<SearchCond*>* searchCondList, SEARCHTYPE type, string modField) override {
		vector<Employee*>* foundList_ = new vector<Employee*>(0);
		bool ret = false;
		for (auto employee : *emList_) {
			doCondModMatching(employee, type, modField, foundList_, searchCondList);
		}		
		return foundList_;
	};

};




