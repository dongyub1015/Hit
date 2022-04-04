#pragma once

class MockValidChecker
{
public:
    string str1;

    MockValidChecker() {}
    MockValidChecker(string str) : str1(str) {}

    MOCK_METHOD(bool, checkValid, (string str1), ());
    MOCK_METHOD(bool, checkEmployeeNum, (string str1), ());
    MOCK_METHOD(bool, checkEmployeeName, (string str1), ());
    MOCK_METHOD(bool, checkCL, (string str1), ());
    MOCK_METHOD(bool, checkPhoneNum, (string str1), ());
    MOCK_METHOD(bool, checkBirthday, (string str1), ());
    MOCK_METHOD(bool, checkCertiGrade, (string str1), ());
    MOCK_METHOD(bool, checkOpt1, (string str1), ());
    MOCK_METHOD(bool, checkOpt2, (string str1), ());
    MOCK_METHOD(bool, checkOpt3, (string str1), ());
};