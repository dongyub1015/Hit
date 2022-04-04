#pragma once

#include <string>
#include <vector>

using namespace std;

class VaildChecker {
private:
	static bool checkEmployeeNum(const string& EmployeeNum);
	static bool checkEmployeeName(const string& EmployeeName);
	static bool checkCL(const string& ClType);
	static bool checkPhoneNum(const string& PhoneNum);
	static bool checkBirthday(const string& Birthday);
	static bool checkCertiGrade(const string& CertiGrade);
	static bool checkOpt1(const string& Opt1);
	static bool checkOpt2(const string& Opt2);
	static bool checkOpt3(const string& Opt3);

	bool IsNumberString(const string& EmployeeNum);
	bool IsCapitalString(const string& Str);
	bool checkOptName(const string& OptName);
	bool checkOptPhoneNum(const string& OptPhoneNum);
	bool checkOptY_Birthday(const string& OptY_Birthday);
	bool checkOptM_Birthday(const string& OptM_Birthday);
	bool checkOptD_Birthday(const string& OptD_Birthday);
	bool checkOptNone(const string& OptNone1, const string& OptNone2);

protected:
	enum ColumnNum {
		employeeNum = 0,
		name,
		cl,
		phoneNum,
		birthday,
		certi,
	};

	vector<bool (*)(const string&)> funcPtr = { checkEmployeeNum, checkEmployeeName, checkCL, checkPhoneNum, checkBirthday, checkCertiGrade };

	template <typename T>
	auto isSameValue(T str1, T str2) { return (str1 == str2); }

	bool checkSrchCond(const string& InputStr);
	int convertColumnStrToInt(const string& column);

public:
	vector<string> parseString(string source, string delimiter);
	virtual bool checkVaild(const string& InputStr) { return false; }
};

class AddVaildChecker : public VaildChecker {
public:
	virtual bool checkVaild(const string& InputStr) ;
};

class DelVaildChecker : public VaildChecker {
public:
	virtual bool checkVaild(const string& InputStr);
};

class SchVaildChecker : public VaildChecker {
public:
	virtual bool checkVaild(const string& InputStr);
};

class ModVaildChecker : public VaildChecker {
public:
	virtual bool checkVaild(const string& InputStr);
};