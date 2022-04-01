#pragma once
#include<string>

using std::string;

class IEmployee
{
public:
    virtual ~IEmployee() {}
    virtual string getEmployeeNum() const = 0;
    virtual string getName() const = 0;
    virtual string getCL() const = 0;
    virtual string getPhoneNum() const = 0;
    virtual string getBirthday() const = 0;
    virtual string getCerti() const = 0;
    virtual void setName(string name) = 0;
    virtual void setCL(string cl) = 0;
    virtual void setPhoneNum(string phoneNum) = 0;
    virtual void setBirthday(string birthday) = 0;
    virtual void setCerti(string certi) = 0;
};

