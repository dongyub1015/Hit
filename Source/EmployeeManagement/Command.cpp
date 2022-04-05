/*Command.cpp*/

#include "Command.h"
#include <algorithm>


vector<Command*> commandList = {
	new AddCommand(),new DelCommand(),new SchCommand(),new ModCommand()
};

map<string, SEARCHTYPE> typeMapper = {
	{"employeeNum", SEARCHTYPE::BYEMPLOYEENUM},
	{"name",SEARCHTYPE::BYNAME},
	{"cl",SEARCHTYPE::BYCL},
	{"phoneNum",SEARCHTYPE::BYPHONENUM},
	{"birthday",SEARCHTYPE::BYBIRTH},
	{"certi",SEARCHTYPE::BYCERTI}
};

SEARCHTYPE getSearchType(string column) {
	return typeMapper.at(column);
};

SearchCond* getOptionSearch(string option2, string compareColumn, string compareValue) {
	SEARCHTYPE searchType = getSearchType(compareColumn);
	if (compareColumn == "name") {
		SearchCondName* returnCond = new SearchCondName(searchType, compareValue);
		if (option2 == "-f") returnCond->setFirstNameSearch();
		else if (option2 == "-l") returnCond->setLastNameSearch();
		return returnCond;
	}
		else if (compareColumn == "phoneNum") {
		SearchCondPhonenum* returnCond = new SearchCondPhonenum(searchType, compareValue);
		if (option2 == "-m") returnCond->setSearchIdx(PHONEIDX::SECOND_F);
		else if (option2 == "-l") returnCond->setSearchIdx(PHONEIDX::THIRD_F);
		return returnCond;

	}
		else if (compareColumn == "birthday") {
		// y m d
		SearchCondDate* returnCond = new SearchCondDate(searchType, compareValue);
		if (option2 == "-y") returnCond->setSearchIdx(PHONEIDX::FIRST_F);
		else if (option2 == "-m") returnCond->setSearchIdx(PHONEIDX::SECOND_F);
		else if (option2 == "-d") returnCond->setSearchIdx(PHONEIDX::THIRD_F);
		return returnCond;
	}
	return new SearchCondStr(searchType, compareValue);
}


int employeeNumToYear(string employeeNum) {
	int employeeNumYear = stoi(employeeNum.substr(0, 2));
	if (68 < employeeNumYear && employeeNumYear < 100)
		employeeNumYear += 1900;
	else
		employeeNumYear += 2000;
	return employeeNumYear;
}

vector<string> Command::employeeResultToString(vector<Employee*>* employeeResult) {
	if(employeeResult == nullptr || this->type_=="ADD") return vector<string>();

	vector<string> result;
	if (employeeResult->empty()) {
		result.push_back(this->type_ + ",NONE");
		return result;
	}
	if (option1_ != "-p") {
		result.push_back(this->type_ + "," + to_string(employeeResult->size()));
		return result;
	}

	sort(employeeResult->begin(), employeeResult->end(), Employee::comp);

	int maxReturnCnt = 5;
	for (auto e : *employeeResult) {
		if (maxReturnCnt <= 0) break;
		string toString = this->type_ + "," + e->toString();
		result.push_back(toString);
		maxReturnCnt--;
	}
	return result;
}

vector<string> Command::makeResult(EmployeeManagement* EM, const string& commandStr) {

	vector<string> strList;
	validChecker_ = new ValidChecker();
	strList = validChecker_->parseString(commandStr, ",");

	string command_type = strList[0];

	for (auto c : commandList) {
		if (c->type_ == command_type) {
			c->setCommandString(commandStr);
			return c->employeeResultToString(c->runCommand(EM));
		}
	}
}

vector<Employee*>* AddCommand::runCommand(EmployeeManagement* EM) {
	validChecker_ = new AddValidChecker();
	if (!validChecker_->checkValid(commandStr_)) return nullptr;

	vector<string> strList;
	strList = validChecker_->parseString(commandStr_, ",");
	string employeeNum = strList[4];
	string name = strList[5];
	string cl = strList[6];
	string phoneNum = strList[7];
	string birthday = strList[8];
	string certi = strList[9];

	EM->addEmployee(employeeNum, name, cl, phoneNum, birthday, certi);
	return nullptr;
}

vector<Employee*>* DelCommand::runCommand(EmployeeManagement* EM) {
	validChecker_ = new DelValidChecker();
	if (!validChecker_->checkValid(commandStr_)) return nullptr;

	vector<string> strList;
	strList = validChecker_->parseString(commandStr_, ",");
	option1_ = strList[1];
	option2_ = strList[2];
	string compareColumn = strList[4];
	string compareValue = strList[5];

	vector<SearchCond*> searchCond;
	searchCond.push_back(getOptionSearch(option2_, compareColumn, compareValue));

	return EM->searchEmployee(&searchCond, true);
}

vector<Employee*>* SchCommand::runCommand(EmployeeManagement* EM) {
	validChecker_ = new SchValidChecker();
	if (!validChecker_->checkValid(commandStr_)) return nullptr;

	vector<string> strList;
	strList = validChecker_->parseString(commandStr_, ",");
	option1_ = strList[1];
	option2_ = strList[2];
	string compareColumn = strList[4];
	string compareValue = strList[5];

	vector<SearchCond*> searchCond;
	searchCond.push_back(getOptionSearch(option2_, compareColumn, compareValue));

	return EM->searchEmployee(&searchCond, false);
}

vector<Employee*>* ModCommand::runCommand(EmployeeManagement* EM) {
	validChecker_ = new ModValidChecker();
	if (!validChecker_->checkValid(commandStr_)) return nullptr;

	vector<string> strList;
	strList = validChecker_->parseString(commandStr_, ",");
	option1_ = strList[1];
	option2_ = strList[2];
	string compareColumn = strList[4];
	string compareValue = strList[5];
	string modifyColumn = strList[6];
	string modifyValue = strList[7];

	vector<SearchCond*> searchCond;
	searchCond.push_back(getOptionSearch(option2_, compareColumn, compareValue));

	SEARCHTYPE searchType = getSearchType(modifyColumn);

	return EM->modifyEmployee(&searchCond, searchType, modifyValue);
}
