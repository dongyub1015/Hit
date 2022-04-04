#include "pch.h"
#include "../EmployeeManagement/Condition.cpp"
#include "../EmployeeManagement/Employee.h"

string setName(string firstName, string lastName) {
	return firstName + " " + lastName;
}

class ConditionTest : public testing::Test {
protected:
	Employee* employee;
	string employeeNum = "10123456";
	string lastName = "Last";
	string firstName = "First";
	string name = firstName + " " + lastName;
	string cl = "CLX";
	string phoneNum = "010-1234-5678";
	string birthday = "YYYYMMDD";
	string certi = "GRADE";
	virtual void SetUp() {
		employee = new Employee(employeeNum, name, cl, phoneNum, birthday, certi);
	}
};

TEST_F(ConditionTest, ContructorTest) {
	string CompareString;
	Condition* c = new Condition("CompareString");

	EXPECT_EQ(c->getCompareString(), "CompareString");
}

TEST_F(ConditionTest, isMatchTest) {
	Condition* c = new ConditionEmployeeNum(employeeNum);
	
	EXPECT_TRUE(c->isMatch(*employee));

	c = new ConditionCerti(certi);
	EXPECT_TRUE(c->isMatch(*employee));

	c = new ConditionCL(cl);
	EXPECT_TRUE(c->isMatch(*employee));
	
	/*Phone Number*/
	c = new ConditionPhoneNumber(phoneNum);
	EXPECT_TRUE(c->isMatch(*employee));
	
	c = new ConditionMiddlePhoneNumber("1234");
	EXPECT_TRUE(c->isMatch(*employee));

	c = new ConditionLastPhoneNumber("5678");
	EXPECT_TRUE(c->isMatch(*employee));
	
	/*Name*/
	c = new ConditionName(name);
	EXPECT_TRUE(c->isMatch(*employee));

	c = new ConditionFirstName("First");
	EXPECT_TRUE(c->isMatch(*employee));

	c = new ConditionLastName("Last");
	EXPECT_TRUE(c->isMatch(*employee));

	/*Birthday*/
	c = new ConditionBirthday(birthday);
	EXPECT_TRUE(c->isMatch(*employee));

	c = new ConditionDayBirthday("DD");
	EXPECT_TRUE(c->isMatch(*employee));

	c = new ConditionMonthBirthday("MM");
	EXPECT_TRUE(c->isMatch(*employee));

	c = new ConditionYearBirthday("YYYY");
	EXPECT_TRUE(c->isMatch(*employee));
}

TEST_F(ConditionTest, isNameMatchTest) {
	Condition* c;

	/*Name*/
	c = new ConditionName(name);
	EXPECT_TRUE(c->isMatch(*employee));

	c = new ConditionFirstName(firstName);
	EXPECT_TRUE(c->isMatch(*employee));

	firstName = "John";
	name = setName(firstName, lastName);
	employee->setName(name);
	c = new ConditionFirstName(firstName);
	EXPECT_TRUE(c->isMatch(*employee));

	firstName = "Titter";
	name = setName(firstName, lastName);
	employee->setName(name);
	c = new ConditionFirstName(firstName);
	EXPECT_TRUE(c->isMatch(*employee));

	c = new ConditionLastName(lastName);
	EXPECT_TRUE(c->isMatch(*employee));


	lastName = "Ben";
	name = setName(firstName, lastName);
	employee->setName(name);
	c = new ConditionLastName(lastName);
	EXPECT_TRUE(c->isMatch(*employee));

	lastName = "Allen";
	name = setName(firstName, lastName);
	employee->setName(name);
	c = new ConditionLastName(lastName);
	EXPECT_TRUE(c->isMatch(*employee));
}
