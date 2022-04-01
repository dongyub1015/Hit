#pragma once

#include<iostream>
#include<string>
#include "IEmployee.h"

using namespace std;

class MockEmployee : public IEmployee
{
public:
    MOCK_METHOD(string, getEmployeeNum, (), (const, override));
    MOCK_METHOD(string, getName, (), (const, override));
    MOCK_METHOD(string, getCL, (), (const, override));
    MOCK_METHOD(string, getPhoneNum, (), (const, override));
    MOCK_METHOD(string, getBirthday, (), (const, override));
    MOCK_METHOD(string, getCerti, (), (const, override));
    MOCK_METHOD(void, setName, (string name), (override));
    MOCK_METHOD(void, setCL, (string cl), (override));
    MOCK_METHOD(void, setPhoneNum, (string phoneNum), (override));
    MOCK_METHOD(void, setBirthday, (string birthday), (override));
    MOCK_METHOD(void, setCerti, (string certi), (override));
};

