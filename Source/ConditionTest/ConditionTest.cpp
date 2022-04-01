#include "pch.h"
#include "../EmployeeManagement/Condition.cpp"

TEST(ConditionTest, ContructorTest) {
	string CompareString;
	Condition* c = new Condition("CompareString");

	EXPECT_EQ(c->getCompareString(), "CompareString");
}
