#include "pch.h"
#include "../EmployeeManagement/Condition.cpp"
#include "../EmployeeManagement/Employee.h"
#include "MockEmployee.h"


TEST(ConditionTest, ContructorTest) {
	string CompareString;
	Condition* c = new Condition("CompareString");

	EXPECT_EQ(c->getCompareString(), "CompareString");
}

TEST(ConditionTest, isMatchTest) {
	string compareString = "CompareString";
	Condition* c = new ConditionEmployeeNum(compareString);
	MockEmployee* employee = new MockEmployee();

	using  ::testing::Return;
	using  ::testing::AtLeast;

	EXPECT_CALL(*employee, getEmployeeNum()).Times(1).WillOnce(Return(compareString));

	EXPECT_TRUE(c->isMatch(*employee));

}
