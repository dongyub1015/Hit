#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "VaildChecker.h"

using namespace std;

const char* const EMPLOYEENUM = "employeeNum";
const char* const NAME = "name";
const char* const CL = "cl";
const char* const PHONENUM = "phoneNum";
const char* const BIRTHDAY = "birthday";
const char* const CERTI = "certi";

vector<string> VaildChecker::parseString(string source, string delimiter)
{
	vector<string> result;
	string token;
	size_t spos = 0, len = delimiter.length(), epos;

	while ((epos = source.find(delimiter, spos)) != string::npos)
	{
		token = source.substr(spos, epos - spos);
		spos = epos + len;
		result.push_back(token);
	}

	result.push_back(source.substr(spos));

	return result;
}

bool VaildChecker::checkEmployeeNum(const string& EmployeeNum)
{
	if (EmployeeNum.size() != 8) return false;

	for (const auto& num : EmployeeNum)
	{
		if (!(num >= '0' && num <= '9')) return false;
	}

	const int intYear = stoi(EmployeeNum.substr(0, 2));
	if ((intYear >= 69 && intYear <= 99) || (intYear >= 00 && intYear <= 21)) return true;

	return false;
}

bool VaildChecker::checkEmployeeName(const string& EmployeeName)
{
	int space = 0, loop = 0;

	if (EmployeeName.size() > 15 || EmployeeName.size() < 3) return false;

	for(auto name : EmployeeName)
	{
		if (name == ' ') space++;
		else if (!(name >= 'A' && name <= 'Z')) return false;
		loop++;

		if ((space > 1) || ((space == 1) && (loop == 1)) || ((space == 0) && (loop == (EmployeeName.size() - 1)))) return false;
	}

	return true;
}

bool VaildChecker::checkCL(const string& ClType)
{
	if (ClType == "CL1" || ClType ==  "CL2" || ClType == "CL3" || ClType == "CL4") return true;

	return false;
}

bool VaildChecker::checkPhoneNum(const string& PhoneNum)
{
	VaildChecker checker;

	if (PhoneNum.size() != 13) return false;
	vector<string> strList = checker.parseString(PhoneNum, "-");
	if (strList[0] != "010") return false;
	if (strList[1].size() != 4 || strList[2].size() != 4) return false;

	for (int i = 0; i < 4; i++)
	{
		if (!(strList[1][i] >= '0' && strList[1][i] <= '9' && strList[2][i] >= '0' && strList[2][i] <= '9')) return false;
	}

	return true;
}

bool VaildChecker::checkBirthday(const string& Birthday)
{
	if (Birthday.size() != 8) return false;

	for (const auto& num : Birthday)
	{
		if (!(num >= '0' && num <= '9')) return false;
	}

	const int intYear = stoi(Birthday.substr(0, 4));
	if (!(intYear >= 1900 && intYear <= 2022)) return false;

	const int intMonth = stoi(Birthday.substr(4, 2));
	if (!(intMonth >= 1 && intMonth <= 12)) return false;

	const int intDay = stoi(Birthday.substr(6, 2)); 	
	if (!(intDay >= 1 && intDay <= 31)) return false;

	return true;
}

bool VaildChecker::checkCertiGrade(const string& CertiGrade)
{
	if (CertiGrade == "ADV" || CertiGrade ==  "PRO" || CertiGrade == "EX") return true;

	return false;
}

int VaildChecker::convertColumnStrToInt(const string& column)
{
	if (column == EMPLOYEENUM) return employeeNum;
	if (column == NAME) return name;
	if (column == PHONENUM) return phoneNum;
	if (column == BIRTHDAY) return birthday;
	if (column == CERTI) return certi;

	return -1;
}

bool VaildChecker::checkOpt1(const string& Opt1)
{
	if (Opt1 == "-p" || Opt1 == " ") return true;

	return false;
}

bool VaildChecker::checkOpt2(const string& Opt2)
{
	if (Opt2 == "-f" || Opt2 == "-l" || Opt2 == "-m" || Opt2 == "-y" || Opt2 == "-d" || Opt2 == " ") return true;

	return false;
}

bool VaildChecker::checkOpt3(const string& Opt3)
{
	if (Opt3 == " ") return true;

	return false;
}

bool VaildChecker::checkSrchCond(const string& InputStr)
{
	int checkedCnt = 1;
	vector<string> strList = parseString(InputStr, ",");	
	vector<bool (*)(const string&)> checkOption = { checkOpt1, checkOpt2, checkOpt3 };

	for (auto optFunc : checkOption)
	{
		if (optFunc(strList[checkedCnt]) == false)	return false;
		checkedCnt++;
	}

	if (strList[2] == "-f")  // first name
	{
		if (strList[4] != NAME) return false;

		if (!((strList[5].size() >= 1) && (strList[5].size() <= 13))) return false;

		for (auto name : strList[5])
		{
			if (!(name >= 'A' && name <= 'Z')) return false;
		}
	}
	else if (strList[2] == "-l") // last name, phonenum
	{
		if (strList[4] == NAME)
		{
			if (!((strList[5].size() >= 1) && (strList[5].size() <= 13))) return false;

			for (auto name : strList[5])
			{
				if (!(name >= 'A' && name <= 'Z')) return false;
			}
		}
		else if (strList[4] == PHONENUM)
		{
			if (strList[5].size() != 4) return false;

			for (auto num : strList[5])
			{
				if (!(num >= '0' && num <= '9')) return false;
			}
		}
		else
		{
			return false;
		}
	}
	else if (strList[2] == "-m") // middle phonenum, month brithday
	{
		if (strList[4] == PHONENUM)
		{
			if (strList[5].size() != 4) return false;

			for (auto num : strList[5])
			{
				if (!(num >= '0' && num <= '9')) return false;
			}
		}
		else if (strList[4] == BIRTHDAY)
		{
			if (strList[5].size() != 2) return false;

			int intMonth = stoi(strList[5]);
			if (!(intMonth >= 1 && intMonth <= 12)) return false;
		}
		else
		{
			return false;
		}
	}
	else if (strList[2] == "-y") // year
	{
		if (strList[4] != BIRTHDAY) return false;
		if (strList[5].size() != 4) return false;

		int intYear = stoi(strList[5]);
		if (!(intYear >= 1900 && intYear <= 2022)) return false;
	}
	else if (strList[2] == "-d") // day
	{
		if (strList[4] != BIRTHDAY) return false;
		if (strList[5].size() != 2) return false;

		int intDay = stoi(strList[5]);
		if (!(intDay >= 1 && intDay <= 31)) return false;
	}

	return true;
}

bool AddVaildChecker::checkVaild(const string& InputStr)
{
	int checkedPara = 0;

	vector<string> strList = parseString(InputStr, ",");
	if (!(isSameValue<size_t>(strList.size(), 10))) return false;

	vector<pair<string, string>> checkCmd = { {strList[0], "ADD"},  {strList[1], " "}, {strList[2], " "}, {strList[3], " "} };
	for (const auto& param : checkCmd)
	{
		if (!(isSameValue<string>(param.first, param.second))) return false;
		checkedPara++;
	}

	for (const auto& fp : funcPtr)
	{
		if (fp(strList[checkedPara++]) == false) return false;
	}

	return true;
}

bool DelVaildChecker::checkVaild(const string& InputStr)
{
	vector<string> strList = parseString(InputStr, ",");

	if (!((strList.size() == 6) && (strList[0] == "DEL"))) return false;

	return checkSrchCond(InputStr);
}

bool SchVaildChecker::checkVaild(const string& InputStr)
{
	vector<string> strList = parseString(InputStr, ",");

	if (!((strList.size() == 6) && (strList[0] == "SCH"))) return false;

	return checkSrchCond(InputStr);
}

bool ModVaildChecker::checkVaild(const string& InputStr)
{
	vector<string> strList = parseString(InputStr, ",");

	if (!((strList.size() == 8) && (strList[0] == "MOD"))) return false;
	if (checkSrchCond(InputStr) == false) return false;

	int column = convertColumnStrToInt(strList[6]);
	if (!(column >= name && column <= certi)) return false;

	return funcPtr[column](strList[7]);
}