/*Command.cpp*/

#include "Command.h"
#include "Condition.h"


vector<Command*> commandList = {
	new AddCommand(),new DelCommand(),new SchCommand(),new ModCommand()
};

Condition* selectCondition(const string& option2, const string& column, const string& compareValue) {
	if (column == "employeeNum") return new ConditionEmployeeNum(compareValue);
	else if (column == "cl") return new ConditionCL(compareValue);
	else if (column == "certi") return new ConditionCerti(compareValue);
	else if (column == "name") {
		// f l
		if (option2 == "-f") return new ConditionFirstName(compareValue);
		else if (option2 == "-l") return new ConditionLastName(compareValue);
		return new ConditionName(compareValue);
	}
	else if (column == "phoneNum") {
		// m l
		if (option2 == "-m") return new ConditionMiddlePhoneNumber(compareValue);
		else if (option2 == "-l") return new ConditionLastPhoneNumber(compareValue);
		return new ConditionPhoneNumber(compareValue);

	}
	else if (column == "birthday") {
		// y m d
		if (option2 == "-y") return new ConditionYearBirthday(compareValue);
		else if (option2 == "-m") return new ConditionMonthBirthday(compareValue);
		else if (option2 == "-d") return new ConditionDayBirthday(compareValue);
		return new ConditionBirthday(compareValue);
	}
}

vector<string> Command::employeeResultToString(vector<Employee> employeeResult) {
	if(this->type_=="ADD") return vector<string>();

	vector<string> result;
	if (employeeResult.empty()) {
		result.push_back(this->type_ + ",NONE");
		return result;
	}
	if (option1_ != "-p") {
		result.push_back(this->type_ + "," + to_string(employeeResult.size()));
		return result;
	}
	// TODO: employeeResult sorting
	//vector<pair<int, Employee>> v;
	//for (auto match : employeeResult) {

	//	if (stoi(match.getEmployeeNum().substr(0, 2)) >= 0 && stoi(match.getEmployeeNum().substr(0, 2)) <= 21) {
	//		v.push_back(pair<int, Employee>(stoi("1" + match.getEmployeeNum()), match));
	//	}
	//	else {
	//		v.push_back(pair<int, Employee>(stoi(match.getEmployeeNum()), match));
	//	}
	//}
	//sort(v.begin(), v.end());

	//{}// TODO: employeeResult sorting

	//int maxReturnCnt = 5;
	//for (auto e : v) {
	//	if (maxReturnCnt <= 0) break;
	//	string toString = this->type_ + "," + e.second.toString();
	//	result.push_back(toString);
	//	maxReturnCnt--;
	//}

	int maxReturnCnt = 5;
	for (auto e : employeeResult) {
		if (maxReturnCnt <= 0) break;
		string toString = this->type_ + "," + e.toString();
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

vector<Employee> AddCommand::runCommand(EmployeeManagement* EM) {
	validChecker_ = new AddValidChecker();
	if (!validChecker_->checkValid(commandStr_)) return vector<Employee>();

	vector<string> strList;
	strList = validChecker_->parseString(commandStr_, ",");
	string employeeNum = strList[4];
	string name = strList[5];
	string cl = strList[6];
	string phoneNum = strList[7];
	string birthday = strList[8];
	string certi = strList[9];

	EM->addEmployee(employeeNum, name, cl, phoneNum, birthday, certi);
	return vector<Employee>();
}

vector<Employee> DelCommand::runCommand(EmployeeManagement* EM) {
	validChecker_ = new DelValidChecker();
	if (!validChecker_->checkValid(commandStr_)) return vector<Employee>();

	vector<string> strList;
	strList = validChecker_->parseString(commandStr_, ",");
	option1_ = strList[1];
	option2_ = strList[2];
	string compareColumn = strList[4];
	string compareValue = strList[5];
	condition_ = selectCondition(option2_, compareColumn, compareValue);

	return EM->deleteEmployee_(*condition_);
}

vector<Employee> SchCommand::runCommand(EmployeeManagement* EM) {
	validChecker_ = new SchValidChecker();
	if (!validChecker_->checkValid(commandStr_)) return vector<Employee>();

	vector<string> strList;
	strList = validChecker_->parseString(commandStr_, ",");
	option1_ = strList[1];
	option2_ = strList[2];
	string compareColumn = strList[4];
	string compareValue = strList[5];
	condition_ = selectCondition(option2_, compareColumn, compareValue);

	return EM->searchEmployee(*condition_);
}

vector<Employee> ModCommand::runCommand(EmployeeManagement* EM) {
	validChecker_ = new ModValidChecker();
	if (!validChecker_->checkValid(commandStr_)) return vector<Employee>();

	vector<string> strList;
	strList = validChecker_->parseString(commandStr_, ",");
	option1_ = strList[1];
	option2_ = strList[2];
	string compareColumn = strList[4];
	string compareValue = strList[5];
	string modifyColumn = strList[6];
	string modifyValue = strList[7];
	condition_ = selectCondition(option2_, compareColumn, compareValue);

	return EM->modifyEmployee(*condition_, modifyColumn, modifyValue);
}
