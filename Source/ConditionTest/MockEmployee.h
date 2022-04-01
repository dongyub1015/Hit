#pragma once

#include<iostream>
#include<string>
#include "../EmployeeManagement/Employee.h"

using namespace std;

class MockEmployee : public Employee
{
public:
    MOCK_METHOD(string, getEmployeeNum, (), ());
    MOCK_METHOD(string, getName, (), ());
    MOCK_METHOD(string, getCL, (), ());
    MOCK_METHOD(string, getPhoneNum, (), ());
    MOCK_METHOD(string, getBirthday, (), ());
    MOCK_METHOD(string, getCerti, (), ());
    MOCK_METHOD(void, setName, (string name), ());
    MOCK_METHOD(void, setCL, (string cl), ());
    MOCK_METHOD(void, setPhoneNum, (string phoneNum), ());
    MOCK_METHOD(void, setBirthday, (string birthday), ());
    MOCK_METHOD(void, setCerti, (string certi), ());
};

