#include "pch.h"
#include "../EmployeeManagement/EmployeeManagement.h"


TEST(TestCaseEmployeeManagement, ADDTEST_POSITIVE)
{
	EmployeeManagement emMgmt;
	EXPECT_EQ(emMgmt.addEmployee("1", "em1", "1", "01013543534", "20220331", "2"), true);
	EXPECT_EQ(emMgmt.addEmployee("2", "em2", "2", "01012353234", "20220331", "1"), true);
	EXPECT_EQ(emMgmt.addEmployee("3", "em3", "1", "01012325534", "20220331", "2"), true);
	EXPECT_EQ(emMgmt.addEmployee("4", "em4", "3", "01015425534", "20220331", "3"), true);
	EXPECT_EQ(emMgmt.addEmployee("5", "em5", "1", "01012335534", "20220331", "2"), true);
	EXPECT_EQ(emMgmt.addEmployee("6", "em6", "4", "01012325534", "20220331", "4"), true);
	EXPECT_EQ(emMgmt.addEmployee("7", "em7", "2", "01012455534", "20220331", "2"), true);
	EXPECT_EQ(emMgmt.addEmployee("8", "em8", "3", "01012555534", "20220331", "1"), true);
	EXPECT_EQ(emMgmt.addEmployee("9", "em9", "1", "01012333534", "20220331", "1"), true);
}






