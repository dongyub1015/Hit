#pragma once

#include <string>

using namespace std;

class VaildChecker {

public :
	virtual bool checkVaild(string InputStr) = 0;

protected:
	bool checkCommonCond(string InputStr)
	{
		// ToDo : implementaion
		return false;
	}
};


class ModVaildChecker : public VaildChecker {

public:
	virtual bool checkVaild(string InputStr)
	{
		// ToDo : implementaion for ModVaildChecker
		return checkCommonCond(InputStr);
	}
};

class SchVaildChecker : public VaildChecker {

public:
	virtual bool checkVaild(string InputStr)
	{
		// ToDo : implementaion for SchVaildChecker
		return checkCommonCond(InputStr);
	}
};


class DelVaildChecker : public VaildChecker {

public:
	virtual bool checkVaild(string InputStr)
	{
		// ToDo : implementaion for DelVaildChecker
		return checkCommonCond(InputStr);
	}
};


class AddVaildChecker : public VaildChecker {

public:
	virtual bool checkVaild(string InputStr)
	{
		// ToDo : implementaion for AddVaildChecker
		return checkCommonCond(InputStr);
	}
};
