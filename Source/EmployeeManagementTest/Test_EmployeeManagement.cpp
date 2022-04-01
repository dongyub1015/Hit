#include "pch.h"
#include "../EmployeeManagement/EmployeeManagement.h"


class EmployeeManagementTest : public ::testing::Test {
protected:
	EmployeeManagement* emMgmt;
	virtual void SetUp() override {
		emMgmt = new EmployeeManagement();
	}
	virtual void TearDown() override {
		delete emMgmt;
	}
};


/*
TITLE : ADDTEST_POSITIVE
PURPOSE:
	add valid input to addEmployee member function and see if anything goes wrongs.
*/
TEST(TestCaseEmployeeManagement, ADDTEST_POSITIVE)
{
	EmployeeManagement emMgmt;
	Condition cond;
	EXPECT_EQ(emMgmt.addEmployee("1", "Name1", "1", "01013543534", "20220331", "2"), true);
	EXPECT_EQ(emMgmt.addEmployee("2", "Name2", "2", "01012353234", "20220331", "1"), true);
	EXPECT_EQ(emMgmt.addEmployee("3", "Name3", "1", "01012325534", "20220331", "2"), true);
	EXPECT_EQ(emMgmt.addEmployee("4", "Name4", "3", "01015425534", "20220331", "3"), true);
	EXPECT_EQ(emMgmt.addEmployee("5", "Name5", "1", "01012335534", "20220331", "2"), true);
	EXPECT_EQ(emMgmt.addEmployee("6", "Name6", "4", "01012325534", "20220331", "4"), true);
	EXPECT_EQ(emMgmt.addEmployee("7", "Name7", "2", "01012455534", "20220331", "2"), true);
	EXPECT_EQ(emMgmt.addEmployee("8", "Name8", "3", "01012555534", "20220331", "1"), true);
	EXPECT_EQ(emMgmt.addEmployee("9", "Name9", "1", "01012333534", "20220331", "1"), true);
}


/*
TITLE : ADDTEST_NATATIVE
PURPOSE :
	add invalid input to addEmployee member function and see if it returns outputs accordingly.
*/
TEST(TestCaseEmployeeManagement, ADDTEST_NATATIVE)
{
	EmployeeManagement emMgmt;
	Condition cond;

	EXPECT_EQ(emMgmt.addEmployee("a", "Name1", "1", "01013543534", "20220331", "2"), true);
	EXPECT_EQ(emMgmt.addEmployee("2", "Name2", "b", "01012353234", "20220331", "1"), true);
	EXPECT_EQ(emMgmt.addEmployee("3", "Name3", "1", "c", "20220331", "2"), true);
	EXPECT_EQ(emMgmt.addEmployee("4", "Name4", "3", "01015425534", "e", "3"), true);
	EXPECT_EQ(emMgmt.addEmployee("5", "Name5", "1", "01012335534", "20220331", "f"), true);
	EXPECT_EQ(emMgmt.addEmployee("6", "12", "4", "01012325534", "20220331", "4"), true);
	EXPECT_EQ(emMgmt.addEmployee("8", "34", "3", "01012555534", "20220331", "1"), true);

}

/*
TITLE : ScenarioTest_01
PURPOSE :
	add valid inputs to addEmployee member function. Search a valid member.
	See if it returns correcnt members.
*/
TEST_F(EmployeeManagementTest, ScenarioTest_01) {
	vector<Employee*>* emList;
	Condition cnd;
	emMgmt->addEmployee("1", "Name1", "1", "01013543534", "20220331", "2");
	emMgmt->addEmployee("2", "Name2", "2", "01013543634", "20220331", "3");
	emMgmt->addEmployee("3", "Name3", "3", "01013543994", "20221231", "1");
	emMgmt->addEmployee("4", "Name4", "4", "01013843534", "20220531", "2");
	cnd.compareString = "Name4";

	emList = emMgmt->searchEmployee(cnd);

	ASSERT_EQ((*emList)[0]->employeeNum_, "4") << "4th Employee employeeNum";
	ASSERT_EQ((*emList)[0]->name_, "Name4") << "4th Employee Name";
	ASSERT_EQ((*emList)[0]->phoneNum_, "01013843534") << "4th Employee Phone Number";
	ASSERT_EQ((*emList)[0]->birthDay_, "20220531") << "4th Employee Birth";
}


/*
TITLE : ScenarioTest_02
PURPOSE :
	add valid inputs to addEmployee member function. Delete a valid member.
	See if it deletes member correctly.
*/
TEST_F(EmployeeManagementTest, ScenarioTest_02) {
	vector<Employee*>* emList;
	Condition cnd;
	emMgmt->addEmployee("1", "Name1", "1", "01013543534", "20220331", "2");
	emMgmt->addEmployee("2", "Name2", "2", "01013543634", "20220331", "3");
	emMgmt->addEmployee("3", "Name3", "3", "01013543994", "20221231", "1");
	emMgmt->addEmployee("4", "Name4", "4", "01013843534", "20220531", "2");
	cnd.compareString = "Name4";

	EXPECT_EQ(emMgmt->deleteEmployee(cnd), true);
}

/*
TITLE : ScenarioTest_03
PURPOSE :
	add valid inputs to addEmployee member function. Search a valid member and then Delete a valid member.
	See if all outputs are correct.
*/
TEST_F(EmployeeManagementTest, ScenarioTest_03) {
	vector<Employee*>* emList;
	Condition cnd;
	emMgmt->addEmployee("1", "Name1", "1", "01013543534", "20220331", "2");
	emMgmt->addEmployee("2", "Name2", "2", "01013543634", "20220331", "3");
	emMgmt->addEmployee("3", "Name3", "3", "01013543994", "20221231", "1");
	emMgmt->addEmployee("4", "Name4", "4", "01013843534", "20220531", "2");

}

/*
TITLE : ScenarioTest_04
PURPOSE :
	add valid inputs to addEmployee member function. Search a valid member and then Delete a valid member.
	See if all outputs are correct.
*/
TEST_F(EmployeeManagementTest, ScenarioTest_04) {
	vector<Employee*>* emList;
	Condition cnd;
	emMgmt->addEmployee("1", "Name1", "1", "01013543534", "20220331", "2");
	emMgmt->addEmployee("2", "Name2", "2", "01013543634", "20220331", "3");
	emMgmt->addEmployee("3", "Name3", "3", "01013543994", "20221231", "1");
	emMgmt->addEmployee("4", "Name4", "4", "01013843534", "20220531", "2");

	emList = emMgmt->searchEmployee(cnd);

	EXPECT_EQ(emMgmt->modifyEmployee("8", "34", "3", "01012555534", "20220331", "1"), true);
}



/*
TITLE : NagativeScenarioTest_01
PURPOSE :
	add valid inputs to addEmployee member function. Search a invalid member.
	See if all outputs are correct.
*/
TEST_F(EmployeeManagementTest, NagativeScenarioTest_01) {
	vector<Employee*>* emList;
	Condition cnd;
	emMgmt->addEmployee("1", "Name1", "1", "01013543534", "20220331", "2");
	emMgmt->addEmployee("2", "Name2", "2", "01013543634", "20220331", "3");
	emMgmt->addEmployee("3", "Name3", "3", "01013543994", "20221231", "1");
	emMgmt->addEmployee("4", "Name4", "4", "01013843534", "20220531", "2");
}

/*
TITLE : NagativeScenarioTest_02
PURPOSE :
	add valid inputs to addEmployee member function. Delete a invalid member.
	See if all outputs are correct.
*/
TEST_F(EmployeeManagementTest, NagativeScenarioTest_02) {
	vector<Employee*>* emList;
	Condition cnd;
	emMgmt->addEmployee("1", "Name1", "1", "01013543534", "20220331", "2");
	emMgmt->addEmployee("2", "Name2", "2", "01013543634", "20220331", "3");
	emMgmt->addEmployee("3", "Name3", "3", "01013543994", "20221231", "1");
	emMgmt->addEmployee("4", "Name4", "4", "01013843534", "20220531", "2");
}

/*
TITLE : NagativeScenarioTest_03
PURPOSE :
	add valid inputs to addEmployee member function. Modify a invalid member.
	See if all outputs are correct.
*/
TEST_F(EmployeeManagementTest, NagativeScenarioTest_03) {
	vector<Employee*>* emList;
	Condition cnd;
	emMgmt->addEmployee("1", "Name1", "1", "01013543534", "20220331", "2");
	emMgmt->addEmployee("2", "Name2", "2", "01013543634", "20220331", "3");
	emMgmt->addEmployee("3", "Name3", "3", "01013543994", "20221231", "1");
	emMgmt->addEmployee("4", "Name4", "4", "01013843534", "20220531", "2");
}

/*
TITLE : StressTest_01
PURPOSE :
	add MAX_EMPLOYEE inputs to addEmployee member function.
	See if it handles correctly.
*/
TEST_F(EmployeeManagementTest, StressTest_01) {
	Employee* emTemp;
	vector<Employee*>* emList;
	Condition cnd;
	for (int i = 0; i < MAX_EMPLOYEE; i++) {
		emMgmt->addEmployee("1", "em1", "1", "01013543534", "20220331", "2");
	}

	ASSERT_EQ(emMgmt->emList_.size(), MAX_EMPLOYEE);

}




