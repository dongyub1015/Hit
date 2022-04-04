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
	EXPECT_EQ(emMgmt.addEmployee("1", "em1", "CL1", "010-1354-3734", "19770312", "ADV"), true);
	EXPECT_EQ(emMgmt.addEmployee("2", "aaa dd", "CL2", "010-1354-7094", "19780521", "ADV"), true);
	EXPECT_EQ(emMgmt.addEmployee("3", "ddd aa", "CL3", "010-3354-3994", "20011211", "PRO"), true);
	EXPECT_EQ(emMgmt.addEmployee("4", "rea aga", "CL2", "010-4384-3574", "20040110", "EX"), true);
	EXPECT_EQ(emMgmt.addEmployee("5", "et co", "CL3", "010-1584-3537", "20160311", "PRO"), true);
	EXPECT_EQ(emMgmt.addEmployee("6", "tyrs xo", "CL3", "010-1364-9734", "20140930", "EX"), true);
	EXPECT_EQ(emMgmt.addEmployee("7", "qqwd sti", "CL1", "010-9384-3734", "20110327", "PRO"), true);
	EXPECT_EQ(emMgmt.addEmployee("8", "bta ayi", "CL4", "010-2384-9597", "19900719", "PRO"), true);
	EXPECT_EQ(emMgmt.addEmployee("9", "tax eyu", "CL4", "010-6384-3739", "20110406", "EX"), true);
}


/*
TITLE : ADDTEST_NATATIVE
PURPOSE :
	add invalid input to addEmployee member function and see if it returns outputs accordingly.
*/
TEST(TestCaseEmployeeManagement, ADDTEST_NATATIVE)
{
	EmployeeManagement emMgmt;

	EXPECT_EQ(emMgmt.addEmployee("a", "Name1", "CL1", "010-1354-3534", "20220331", "ADV"), false);
	EXPECT_EQ(emMgmt.addEmployee("2", "Name2", "CL5", "010-1235-3234", "20220331", "EX"), false);
	EXPECT_EQ(emMgmt.addEmployee("3", "Name2", "CL2", "0100-1235-3234", "20220331", "EX"), false);
	EXPECT_EQ(emMgmt.addEmployee("4", "Name2", "CL2", "010-123a-3234", "20220331", "EX"), false);
	EXPECT_EQ(emMgmt.addEmployee("5", "Name2", "CL2", "010-123a-3234", "18000331", "EX"), false);
	EXPECT_EQ(emMgmt.addEmployee("6", "Name2", "CL2", "010-123a-3234", "20001331", "EX"), false);
	EXPECT_EQ(emMgmt.addEmployee("7", "Name2", "CL2", "010-123a-3234", "20001215", "EE"), false);
	EXPECT_EQ(emMgmt.addEmployee("8", "Name2", "CL2", "010-123a-3234", "20001215", "PRx"), false);

}

/*
TITLE : ScenarioTest_01
PURPOSE :
	add valid inputs to addEmployee member function. Search a valid member.
	See if it returns correcnt members.
*/
TEST_F(EmployeeManagementTest, ScenarioTest_01) {
	vector <Employee*>* matchingList;
	EXPECT_EQ(emMgmt->addEmployee("1", "em1", "CL1", "010-1354-3734", "19770312", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("2", "aaa dd", "CL2", "010-1354-7094", "19780521", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("3", "ddd aa", "CL3", "010-3354-3994", "20011211", "PRO"), true);
	EXPECT_EQ(emMgmt->addEmployee("4", "rea aga", "CL2", "010-4384-3574", "20040110", "EX"), true);

	vector<SearchCond*> searchCond;
	SearchCondStr tempCond(SEARCHTYPE::BYEMPLOYEENUM, "1");
	searchCond.push_back(&tempCond);
	matchingList = emMgmt->searchEmployee(&searchCond, false);

	ASSERT_EQ((*matchingList)[0]->getEmployeeNum(), "1") << "1th Employee's employeeNum";
	ASSERT_EQ((*matchingList)[0]->getName(), "em1") << "1th Employee's Name";
	ASSERT_EQ((*matchingList)[0]->getCL(), "CL1") << "1th Employee's CL";
	ASSERT_EQ((*matchingList)[0]->getPhoneNum(), "010-1354-3734") << "1th Employee's Phone Number";
	ASSERT_EQ((*matchingList)[0]->getBirthday(), "19770312") << "1th Employee's Birth Day";
	ASSERT_EQ((*matchingList)[0]->getCerti(), "ADV") << "4th Employee's Certi";
}


/*
TITLE : ScenarioTest_02
PURPOSE :
	add valid inputs to addEmployee member function. Delete a valid member.
	See if it deletes member correctly.
*/
TEST_F(EmployeeManagementTest, ScenarioTest_02) {
	vector <Employee*>* matchingList;
	EXPECT_EQ(emMgmt->addEmployee("1", "em1", "CL1", "010-1354-3734", "19770312", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("2", "aaa dd", "CL2", "010-1354-7094", "19780521", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("3", "ddd aa", "CL3", "010-3354-3994", "20011211", "PRO"), true);
	EXPECT_EQ(emMgmt->addEmployee("4", "rea aga", "CL2", "010-4384-3574", "20040110", "EX"), true);

	vector<SearchCond*> searchCond;
	SearchCondStr tempCond(SEARCHTYPE::BYEMPLOYEENUM, "1");
	searchCond.push_back(&tempCond);
	matchingList = emMgmt->searchEmployee(&searchCond, true);

	ASSERT_EQ(emMgmt->emList_.size(), 3) << "Number of Employee";
	ASSERT_EQ(emMgmt->emList_[0]->getEmployeeNum(), "2") << "1th Employee's employeeNum";
	ASSERT_EQ(emMgmt->emList_[0]->getName(), "aaa dd") << "1th Employee's Name";
	ASSERT_EQ(emMgmt->emList_[0]->getCL(), "CL2") << "1th Employee's CL";
	ASSERT_EQ(emMgmt->emList_[0]->getPhoneNum(), "010-1354-7094") << "1th Employee's Phone Number";
	ASSERT_EQ(emMgmt->emList_[0]->getBirthday(), "19780521") << "1th Employee's Birth Day";
	ASSERT_EQ(emMgmt->emList_[0]->getCerti(), "ADV") << "4th Employee's Certi";
}

/*
TITLE : ScenarioTest_03
PURPOSE :
	add valid inputs to addEmployee member function. Search a valid member and then Delete a valid member.
	See if all outputs are correct.
*/
//TEST_F(EmployeeManagementTest, ScenarioTest_03) {
//	vector<Employee*>* emList;
//	Condition cnd;
//	emMgmt->addEmployee("1", "Name1", "1", "01013543534", "20220331", "2");
//	emMgmt->addEmployee("2", "Name2", "2", "01013543634", "20220331", "3");
//	emMgmt->addEmployee("3", "Name3", "3", "01013543994", "20221231", "1");
//	emMgmt->addEmployee("4", "Name4", "4", "01013843534", "20220531", "2");
//
//}

/*
TITLE : ScenarioTest_04
PURPOSE :
	add valid inputs to addEmployee member function. Search a valid member and then Delete a valid member.
	See if all outputs are correct.
*/
//TEST_F(EmployeeManagementTest, ScenarioTest_04) {
//	vector<Employee*>* emList;
//	Condition cnd;
//	emMgmt->addEmployee("1", "Name1", "1", "01013543534", "20220331", "2");
//	emMgmt->addEmployee("2", "Name2", "2", "01013543634", "20220331", "3");
//	emMgmt->addEmployee("3", "Name3", "3", "01013543994", "20221231", "1");
//	emMgmt->addEmployee("4", "Name4", "4", "01013843534", "20220531", "2");
//
//	emList = emMgmt->searchEmployee(cnd);
//
//	EXPECT_EQ(emMgmt->modifyEmployee("8", "34", "3", "01012555534", "20220331", "1"), true);
//}


/*
TITLE : ScenarioTest_101
PURPOSE :
	Find items with employee numbure and modify phone number
	See if all outputs are correct.
*/
TEST_F(EmployeeManagementTest, ScenarioTest_101) {
	vector <Employee*>* matchingList;
	EXPECT_EQ(emMgmt->addEmployee("1", "em1", "CL1", "010-1354-3734", "19770312", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("2", "aaa dd", "CL2", "010-1354-7094", "19780521", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("3", "ddd aa", "CL3", "010-3354-3994", "20011211", "PRO"), true);
	EXPECT_EQ(emMgmt->addEmployee("4", "rea aga", "CL2", "010-4384-3574", "20040110", "EX"), true);

	SearchCondStr fistmodCond(SEARCHTYPE::BYEMPLOYEENUM, "1");
	vector<SearchCond*> searchCond;
	string modContent = "010-1234-1234";
	searchCond.push_back(&fistmodCond);

	matchingList = emMgmt->modifyEmployee(&searchCond, SEARCHTYPE::BYPHONENUM, modContent);

	ASSERT_EQ((*matchingList)[0]->getEmployeeNum(), "1") << "1th Employee's employeeNum";
	ASSERT_EQ((*matchingList)[0]->getName(), "em1") << "1th Employee's Name";
	ASSERT_EQ((*matchingList)[0]->getCL(), "CL1") << "1th Employee's CL";
	ASSERT_EQ((*matchingList)[0]->getPhoneNum(), "010-1234-1234") << "1th Employee's Phone Number";
	ASSERT_EQ((*matchingList)[0]->getBirthday(), "19770312") << "1th Employee's Birth Day";
	ASSERT_EQ((*matchingList)[0]->getCerti(), "ADV") << "4th Employee's Certi";
}

/*
TITLE : ScenarioTest_102
PURPOSE :
	Find items with employee's first name and modify phone number
	See if all outputs are correct.
*/
TEST_F(EmployeeManagementTest, ScenarioTest_102) {
	vector <Employee*>* matchingList;
	EXPECT_EQ(emMgmt->addEmployee("1", "em1", "CL1", "010-1354-3734", "19770312", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("2", "aaa dd", "CL2", "010-1354-7094", "19780521", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("3", "ddd aa", "CL3", "010-3354-3994", "20011211", "PRO"), true);
	EXPECT_EQ(emMgmt->addEmployee("4", "rea aga", "CL2", "010-4384-3574", "20040110", "EX"), true);


	SearchCondName secondmodCond(SEARCHTYPE::BYNAME, "ddd");
	secondmodCond.setFirstNameSearch();
	vector<SearchCond*> searchCond;
	string modContent = "010-1234-1234";
	searchCond.push_back(&secondmodCond);

	matchingList = emMgmt->modifyEmployee(&searchCond, SEARCHTYPE::BYPHONENUM, modContent);

	ASSERT_EQ((*matchingList)[0]->getEmployeeNum(), "3") << "1th Employee's employeeNum";
	ASSERT_EQ((*matchingList)[0]->getName(), "ddd aa") << "1th Employee's Name";
	ASSERT_EQ((*matchingList)[0]->getCL(), "CL3") << "1th Employee's CL";
	ASSERT_EQ((*matchingList)[0]->getPhoneNum(), "010-1234-1234") << "1th Employee's Phone Number";
	ASSERT_EQ((*matchingList)[0]->getBirthday(), "20011211") << "1th Employee's Birth Day";
	ASSERT_EQ((*matchingList)[0]->getCerti(), "PRO") << "4th Employee's Certi";
}

/*
TITLE : ScenarioTest_103
PURPOSE :
	Find items with employee's last name and modify phone number
	See if all outputs are correct.
*/
TEST_F(EmployeeManagementTest, ScenarioTest_103) {
	vector <Employee*>* matchingList;
	EXPECT_EQ(emMgmt->addEmployee("1", "em1", "CL1", "010-1354-3734", "19770312", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("2", "aaa dd", "CL2", "010-1354-7094", "19780521", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("3", "ddd aa", "CL3", "010-3354-3994", "20011211", "PRO"), true);
	EXPECT_EQ(emMgmt->addEmployee("4", "rea aga", "CL2", "010-4384-3574", "20040110", "EX"), true);


	SearchCondName secondmodCond(SEARCHTYPE::BYNAME, "aa");
	secondmodCond.setLastNameSearch();
	vector<SearchCond*> searchCond;
	string modContent = "010-1234-1234";
	searchCond.push_back(&secondmodCond);

	matchingList = emMgmt->modifyEmployee(&searchCond, SEARCHTYPE::BYPHONENUM, modContent);

	ASSERT_EQ((*matchingList)[0]->getEmployeeNum(), "3") << "1th Employee's employeeNum";
	ASSERT_EQ((*matchingList)[0]->getName(), "ddd aa") << "1th Employee's Name";
	ASSERT_EQ((*matchingList)[0]->getCL(), "CL3") << "1th Employee's CL";
	ASSERT_EQ((*matchingList)[0]->getPhoneNum(), "010-1234-1234") << "1th Employee's Phone Number";
	ASSERT_EQ((*matchingList)[0]->getBirthday(), "20011211") << "1th Employee's Birth Day";
	ASSERT_EQ((*matchingList)[0]->getCerti(), "PRO") << "4th Employee's Certi";
}


/*
TITLE : ScenarioTest_104
PURPOSE :
	Find items with employee's last name and modify phone number
	See if all outputs are correct.
*/
TEST_F(EmployeeManagementTest, ScenarioTest_104) {
	vector <Employee*>* matchingList;
	EXPECT_EQ(emMgmt->addEmployee("1", "em1", "CL1", "010-1354-3734", "19770312", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("2", "aaa dd", "CL2", "010-1354-7094", "19780521", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("3", "ddd aa", "CL3", "010-3354-3994", "20011211", "PRO"), true);
	EXPECT_EQ(emMgmt->addEmployee("4", "rea aga", "CL2", "010-4384-3574", "20040110", "EX"), true);


	SearchCondName secondmodCond(SEARCHTYPE::BYNAME, "aa");
	secondmodCond.setLastNameSearch();
	vector<SearchCond*> searchCond;
	string modContent = "010-1234-1234";
	searchCond.push_back(&secondmodCond);

	matchingList = emMgmt->modifyEmployee(&searchCond, SEARCHTYPE::BYPHONENUM, modContent);

	ASSERT_EQ((*matchingList)[0]->getEmployeeNum(), "3") << "1th Employee's employeeNum";
	ASSERT_EQ((*matchingList)[0]->getName(), "ddd aa") << "1th Employee's Name";
	ASSERT_EQ((*matchingList)[0]->getCL(), "CL3") << "1th Employee's CL";
	ASSERT_EQ((*matchingList)[0]->getPhoneNum(), "010-1234-1234") << "1th Employee's Phone Number";
	ASSERT_EQ((*matchingList)[0]->getBirthday(), "20011211") << "1th Employee's Birth Day";
	ASSERT_EQ((*matchingList)[0]->getCerti(), "PRO") << "4th Employee's Certi";
}

/*
TITLE : ScenarioTest_105
PURPOSE :
	Find items with employee's middle phone number and modify phone number
	See if all outputs are correct.
*/
TEST_F(EmployeeManagementTest, ScenarioTest_105) {
	vector <Employee*>* matchingList;
	EXPECT_EQ(emMgmt->addEmployee("1", "em1", "CL1", "010-1354-3734", "19770312", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("2", "aaa dd", "CL2", "010-1354-7094", "19780521", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("3", "ddd aa", "CL3", "010-3354-3994", "20011211", "PRO"), true);
	EXPECT_EQ(emMgmt->addEmployee("4", "rea aga", "CL2", "010-4384-3574", "20040110", "EX"), true);


	SearchCondPhonenum secondmodCond(SEARCHTYPE::BYPHONENUM, "3354");
	secondmodCond.setSearchIdx(PHONEIDX::SECOND_F);
	vector<SearchCond*> searchCond;
	string modContent = "010-1234-1234";
	searchCond.push_back(&secondmodCond);

	matchingList = emMgmt->modifyEmployee(&searchCond, SEARCHTYPE::BYPHONENUM, modContent);

	ASSERT_EQ((*matchingList)[0]->getEmployeeNum(), "3") << "1th Employee's employeeNum";
	ASSERT_EQ((*matchingList)[0]->getName(), "ddd aa") << "1th Employee's Name";
	ASSERT_EQ((*matchingList)[0]->getCL(), "CL3") << "1th Employee's CL";
	ASSERT_EQ((*matchingList)[0]->getPhoneNum(), "010-1234-1234") << "1th Employee's Phone Number";
	ASSERT_EQ((*matchingList)[0]->getBirthday(), "20011211") << "1th Employee's Birth Day";
	ASSERT_EQ((*matchingList)[0]->getCerti(), "PRO") << "4th Employee's Certi";
}

/*
TITLE : ScenarioTest_106
PURPOSE :
	Find items with employee's birth year and modify phone number
	See if all outputs are correct.
*/
TEST_F(EmployeeManagementTest, ScenarioTest_106) {
	vector <Employee*>* matchingList;
	EXPECT_EQ(emMgmt->addEmployee("1", "em1", "CL1", "010-1354-3734", "19770312", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("2", "aaa dd", "CL2", "010-1354-7094", "19780521", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("3", "ddd aa", "CL3", "010-3354-3994", "20011211", "PRO"), true);
	EXPECT_EQ(emMgmt->addEmployee("4", "rea aga", "CL2", "010-4384-3574", "20040110", "EX"), true);


	SearchCondDate secondmodCond(SEARCHTYPE::BYBIRTH, "2001");
	secondmodCond.setSearchIdx(PHONEIDX::FIRST_F);
	vector<SearchCond*> searchCond;
	string modContent = "010-1234-1234";
	searchCond.push_back(&secondmodCond);

	matchingList = emMgmt->modifyEmployee(&searchCond, SEARCHTYPE::BYPHONENUM, modContent);

	ASSERT_EQ((*matchingList)[0]->getEmployeeNum(), "3") << "1th Employee's employeeNum";
	ASSERT_EQ((*matchingList)[0]->getName(), "ddd aa") << "1th Employee's Name";
	ASSERT_EQ((*matchingList)[0]->getCL(), "CL3") << "1th Employee's CL";
	ASSERT_EQ((*matchingList)[0]->getPhoneNum(), "010-1234-1234") << "1th Employee's Phone Number";
	ASSERT_EQ((*matchingList)[0]->getBirthday(), "20011211") << "1th Employee's Birth Day";
	ASSERT_EQ((*matchingList)[0]->getCerti(), "PRO") << "4th Employee's Certi";
}


/*
TITLE : ScenarioTest_107
PURPOSE :
	Find items with employee's certi and modify phone number
	See if all outputs are correct.
*/
TEST_F(EmployeeManagementTest, ScenarioTest_107) {
	vector <Employee*>* matchingList;
	EXPECT_EQ(emMgmt->addEmployee("1", "em1", "CL1", "010-1354-3734", "19770312", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("2", "aaa dd", "CL2", "010-1354-7094", "19780521", "ADV"), true);
	EXPECT_EQ(emMgmt->addEmployee("3", "ddd aa", "CL3", "010-3354-3994", "20011211", "PRO"), true);
	EXPECT_EQ(emMgmt->addEmployee("4", "rea aga", "CL2", "010-4384-3574", "20040110", "EX"), true);


	SearchCondStr secondmodCond(SEARCHTYPE::BYCERTI, "PRO");
	vector<SearchCond*> searchCond;
	string modContent = "010-1234-1234";
	searchCond.push_back(&secondmodCond);

	matchingList = emMgmt->modifyEmployee(&searchCond, SEARCHTYPE::BYPHONENUM, modContent);

	ASSERT_EQ((*matchingList)[0]->getEmployeeNum(), "3") << "1th Employee's employeeNum";
	ASSERT_EQ((*matchingList)[0]->getName(), "ddd aa") << "1th Employee's Name";
	ASSERT_EQ((*matchingList)[0]->getCL(), "CL3") << "1th Employee's CL";
	ASSERT_EQ((*matchingList)[0]->getPhoneNum(), "010-1234-1234") << "1th Employee's Phone Number";
	ASSERT_EQ((*matchingList)[0]->getBirthday(), "20011211") << "1th Employee's Birth Day";
	ASSERT_EQ((*matchingList)[0]->getCerti(), "PRO") << "4th Employee's Certi";
}


/*
TITLE : NagativeScenarioTest_01
PURPOSE :
	add valid inputs to addEmployee member function. Search a invalid member.
	See if all outputs are correct.
*/
//TEST_F(EmployeeManagementTest, NagativeScenarioTest_01) {
//	vector<Employee*>* emList;
//	Condition cnd;
//	emMgmt->addEmployee("1", "Name1", "1", "01013543534", "20220331", "2");
//	emMgmt->addEmployee("2", "Name2", "2", "01013543634", "20220331", "3");
//	emMgmt->addEmployee("3", "Name3", "3", "01013543994", "20221231", "1");
//	emMgmt->addEmployee("4", "Name4", "4", "01013843534", "20220531", "2");
//}

/*
TITLE : NagativeScenarioTest_02
PURPOSE :
	add valid inputs to addEmployee member function. Delete a invalid member.
	See if all outputs are correct.
*/
//TEST_F(EmployeeManagementTest, NagativeScenarioTest_02) {
//	vector<Employee*>* emList;
//	Condition cnd;
//	emMgmt->addEmployee("1", "Name1", "1", "01013543534", "20220331", "2");
//	emMgmt->addEmployee("2", "Name2", "2", "01013543634", "20220331", "3");
//	emMgmt->addEmployee("3", "Name3", "3", "01013543994", "20221231", "1");
//	emMgmt->addEmployee("4", "Name4", "4", "01013843534", "20220531", "2");
//}

/*
TITLE : NagativeScenarioTest_03
PURPOSE :
	add valid inputs to addEmployee member function. Modify a invalid member.
	See if all outputs are correct.
*/
//TEST_F(EmployeeManagementTest, NagativeScenarioTest_03) {
//	vector<Employee*>* emList;
//	Condition cnd;
//	emMgmt->addEmployee("1", "Name1", "1", "01013543534", "20220331", "2");
//	emMgmt->addEmployee("2", "Name2", "2", "01013543634", "20220331", "3");
//	emMgmt->addEmployee("3", "Name3", "3", "01013543994", "20221231", "1");
//	emMgmt->addEmployee("4", "Name4", "4", "01013843534", "20220531", "2");
//}



/*
TITLE : StressTest_01
PURPOSE :
	add MAX_EMPLOYEE inputs to addEmployee member function.
	See if it handles correctly.
*/
TEST_F(EmployeeManagementTest, StressTest_01) {
	Employee* emTemp;
	vector<Employee*>* emList;
	for (int i = 0; i < MAX_EMPLOYEE; i++) {
		emMgmt->addEmployee("1", "em1", "CL1", "010-1354-3734", "19770312", "ADV");
	}
	ASSERT_EQ(emMgmt->emList_.size(), MAX_EMPLOYEE);

}

/*
TITLE : StressTest_02
PURPOSE :
	add MAX_EMPLOYEE inputs to addEmployee member function.

	See if it handles correctly.
*/
TEST_F(EmployeeManagementTest, StressTest_02) {
	vector <Employee*>* matchingList;
	Employee* emTemp;
	vector<Employee*>* emList;
	for (int i = 0; i < MAX_EMPLOYEE; i++) {
		emMgmt->addEmployee("1", "em1", "CL1", "010-1354-3734", "19770312", "ADV");
	}
	vector<SearchCond*> searchCond;
	SearchCondStr tempCond(SEARCHTYPE::BYEMPLOYEENUM, "1");
	searchCond.push_back(&tempCond);
	matchingList = emMgmt->searchEmployee(&searchCond, false);

	ASSERT_EQ(matchingList->size(), MAX_EMPLOYEE);

}






