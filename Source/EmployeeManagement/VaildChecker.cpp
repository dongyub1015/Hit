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

bool VaildChecker::IsNumberString(const string& str)
{
	for (const auto& num : str) 
	{
		if (!(num >= '0' && num <= '9')) return false;
	}
	return true;
}

bool VaildChecker::IsCapitalString(const string& Str)
{
	for (const auto& name : Str)
	{
		if (!(name >= 'A' && name <= 'Z')) return false;
	}
	return true;
}

bool VaildChecker::checkEmployeeNum(const string& EmployeeNum)
{
	VaildChecker checker;

	if (EmployeeNum.size() != 8) return false;
	if (!checker.IsNumberString(EmployeeNum)) return false;
	if (stoi(EmployeeNum.substr(0, 2)) >= 69 && stoi(EmployeeNum.substr(0, 2)) <= 99) return true;
	if (stoi(EmployeeNum.substr(0, 2)) >= 00 && stoi(EmployeeNum.substr(0, 2)) <= 21) return true;
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
	vector<string> strList = checker.parseString(PhoneNum, "-");

	if (PhoneNum.size() != 13) return false;
	if (strList[0] != "010") return false;
	if (strList[1].size() != 4 || strList[2].size() != 4) return false;
	if (!checker.IsNumberString(strList[1])) return false;
	if (!checker.IsNumberString(strList[2])) return false;
	return true;
}

bool VaildChecker::checkBirthday(const string& Birthday)
{
	VaildChecker checker;

	if (Birthday.size() != 8) return false;
	if (!checker.IsNumberString(Birthday)) return false;
	if (!(stoi(Birthday.substr(0, 4)) >= 1900 && stoi(Birthday.substr(0, 4)) <= 2022)) return false;
	if (!(stoi(Birthday.substr(4, 2)) >= 1 && stoi(Birthday.substr(4, 2)) <= 12)) return false;
	if (!(stoi(Birthday.substr(6, 2)) >= 1 && stoi(Birthday.substr(6, 2)) <= 31)) return false;
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

bool VaildChecker::checkOptName(const string& OptName)
{
	if (!((OptName.size() >= 1) && (OptName.size() <= 13))) return false;
	if (!IsCapitalString(OptName)) return false;
	return true;
}

bool VaildChecker::checkOptPhoneNum(const string& OptPhoneNum)
{
	if (OptPhoneNum.size() != 4) return false;
	if (!IsNumberString(OptPhoneNum)) return false;
	return true;
}

bool VaildChecker::checkOptY_Birthday(const string& OptY_Birthday)
{
	if (OptY_Birthday.size() != 4) return false;
	if (!(stoi(OptY_Birthday) >= 1900 && stoi(OptY_Birthday) <= 2022)) return false;
	return true;
}

bool VaildChecker::checkOptM_Birthday(const string& OptM_Birthday)
{
	if (OptM_Birthday.size() != 2) return false;
	if (!(stoi(OptM_Birthday) >= 1 && stoi(OptM_Birthday) <= 12)) return false;
	return true;
}

bool VaildChecker::checkOptD_Birthday(const string& OptD_Birthday)
{
	if (OptD_Birthday.size() != 2) return false;
	if (!(stoi(OptD_Birthday) >= 1 && stoi(OptD_Birthday) <= 31)) return false;
	return true;
}

bool VaildChecker::checkOptNone(const string& OptNone1, const string& OptNone2)
{
	if (!(convertColumnStrToInt(OptNone1) >= employeeNum && convertColumnStrToInt(OptNone1) <= certi)) return false;
	return funcPtr[convertColumnStrToInt(OptNone1)](OptNone2);
}

bool VaildChecker::checkSrchCond(const string& InputStr)
{
	int checkedCnt = 1;
	vector<string> strList = parseString(InputStr, ",");	
	vector<bool (*)(const string&)> checkOption = { checkOpt1, checkOpt2, checkOpt3 };

	for (auto optFunc : checkOption)
	{
		if (!optFunc(strList[checkedCnt]))	return false;
		checkedCnt++;
	}

	if (strList[2] == "-f")
	{
		if (strList[4] != NAME) return false;
		return checkOptName(strList[5]);
	}
	else if (strList[2] == "-l")
	{
		if (strList[4] == NAME) return checkOptName(strList[5]);
		if (strList[4] == PHONENUM) return checkOptPhoneNum(strList[5]);
		return false;
	}
	else if (strList[2] == "-m")
	{
		if (strList[4] == PHONENUM) return checkOptPhoneNum(strList[5]);
		else if (strList[4] == BIRTHDAY) return checkOptM_Birthday(strList[5]);
		return false;
	}
	else if (strList[2] == "-y")
	{
		if (strList[4] != BIRTHDAY) return false;
		return checkOptY_Birthday(strList[5]);
	}
	else if (strList[2] == "-d")
	{
		if (strList[4] != BIRTHDAY) return false;
		return checkOptD_Birthday(strList[5]);
	}

	return checkOptNone(strList[4], strList[5]);
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
		if (!fp(strList[checkedPara++])) return false;
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
	if (!checkSrchCond(InputStr)) return false;
	if (!(convertColumnStrToInt(strList[6]) >= name && convertColumnStrToInt(strList[6]) <= certi)) return false;
	return funcPtr[convertColumnStrToInt(strList[6])](strList[7]);
}