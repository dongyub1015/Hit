#include "pch.h"
#include "../EmployeeManagement/Command.h"
#include "../EmployeeManagement/Command.cpp"
#include "../EmployeeManagement/EmployeeManagement.h"
#include "../EmployeeManagement/ValidityChecker.h"
#include "../EmployeeManagement/ValidityChecker.cpp"


class CommandTest : public testing::Test {
protected:
	EmployeeManagement* EM;
	Command* command;
	vector<string> resultReal;
	vector<string> resultExpected;

	virtual void SetUp() {
		EM = new EmployeeManagement();
		command = new Command();

		command->makeResult(EM, "ADD, , , ,19129568,SRERLALH HMEF,CL2,010-7260-9521,19640910,PRO");
		command->makeResult(EM, "ADD, , , ,20123566,SRERL ALHHMEF,CL2,010-1258-5486,19640910,PRO");
		command->makeResult(EM, "ADD, , , ,09129568,SLALH HMEFFEU,CL2,010-7260-1258,19640910,PRO");
		command->makeResult(EM, "ADD, , , ,12002541,ALWPW HMEFFEU,CL3,010-1522-7258,19640910,ADV");
	}

};

TEST_F(CommandTest, AddTest) {
	command->makeResult(EM, "ADD, , , ,19129568,SRERLALH HMEF,CL2,010-7260-9521,19640910,PRO");
	EXPECT_EQ(EM->emList_.size(), 4);

	command->makeResult(EM, "ADD, , , ,20123566,SRERL ALHHMEF,CL2,010-1258-5486,19640910,PRO");
	EXPECT_EQ(EM->emList_.size(), 4);

	command->makeResult(EM, "ADD, , , ,09129568,SLALH HMEFFEU,CL2,010-7260-1258,19640910,PRO");
	EXPECT_EQ(EM->emList_.size(), 4);

	command->makeResult(EM, "ADD, , , ,20129568,SLALH HMEFFEU,CL2,010-7260-1258,19640910,PRO");
	EXPECT_EQ(EM->emList_.size(), 5);

	command->makeResult(EM, "ADD, , , ,00139568,SSDGH HMEFFEU,CL4,010-7260-4828,19840910,EX");
	EXPECT_EQ(EM->emList_.size(), 6);
}

TEST_F(CommandTest, DelTest) {
	command->makeResult(EM, "DEL, , , ,name,SLALH HMEFFEU");
	EXPECT_EQ(EM->emList_.size(), 3);

	command->makeResult(EM, "DEL, ,-m, ,phoneNum,1258");
	EXPECT_EQ(EM->emList_.size(), 2);

	command->makeResult(EM, "DEL, , , ,employeeNum,19129568");
	EXPECT_EQ(EM->emList_.size(), 1);
}

TEST_F(CommandTest, SchTest) {
	for (auto stringLine : command->makeResult(EM, "SCH, , , ,name,SLALH HMEFFEU")) {
		resultReal.push_back(stringLine);
	}
	resultExpected.push_back("SCH,1");

	for (auto stringLine : command->makeResult(EM, "SCH,-p,-m, ,phoneNum,1258")) {
		resultReal.push_back(stringLine);
	}
	resultExpected.push_back("SCH,20123566,SRERL ALHHMEF,CL2,010-1258-5486,19640910,PRO");

	for (auto stringLine : command->makeResult(EM, "SCH, , , ,employeeNum,19129568")) {
		resultReal.push_back(stringLine);
	}
	resultExpected.push_back("SCH,1");

	for (auto stringLine : command->makeResult(EM, "SCH, , , ,employeeNum,11111111")) {
		resultReal.push_back(stringLine);
	}
	resultExpected.push_back("SCH,NONE");

	ASSERT_EQ(resultReal.size(), resultExpected.size());
	for (int i = 0; i < resultReal.size(); i++)
	{
		EXPECT_EQ(resultReal[i], resultExpected[i]);
	}
}

TEST_F(CommandTest, SchWithSortingTest) {

	command->makeResult(EM, "ADD, , , ,69139568,SSDGH HMEFFEU,CL4,010-7260-4828,19640910,PRO");
	EXPECT_EQ(EM->emList_.size(), 5);
	command->makeResult(EM, "ADD, , , ,69149568,SSDGH HMEFFEU,CL4,010-7260-4828,19640910,PRO");
	EXPECT_EQ(EM->emList_.size(), 6);

	for (auto stringLine : command->makeResult(EM, "SCH,-p,-m, ,birthday,09")) {
		resultReal.push_back(stringLine);
	}
	resultExpected.push_back("SCH,69139568,SSDGH HMEFFEU,CL4,010-7260-4828,19640910,PRO");
	resultExpected.push_back("SCH,69149568,SSDGH HMEFFEU,CL4,010-7260-4828,19640910,PRO");
	resultExpected.push_back("SCH,09129568,SLALH HMEFFEU,CL2,010-7260-1258,19640910,PRO");
	resultExpected.push_back("SCH,12002541,ALWPW HMEFFEU,CL3,010-1522-7258,19640910,ADV");
	resultExpected.push_back("SCH,19129568,SRERLALH HMEF,CL2,010-7260-9521,19640910,PRO");

	ASSERT_EQ(resultReal.size(), resultExpected.size());
	for (int i = 0; i < resultReal.size(); i++)
	{

		EXPECT_EQ(resultReal[i], resultExpected[i]);
	}
}

TEST_F(CommandTest, DelAndSchWithSortingTest) {

	command->makeResult(EM, "ADD, , , ,69139568,SSDGH HMEFFEU,CL4,010-7260-4828,19640910,PRO");
	EXPECT_EQ(EM->emList_.size(), 5);
	command->makeResult(EM, "ADD, , , ,69149568,SSDGH HMEFFEU,CL4,010-7260-4828,19640910,PRO");
	EXPECT_EQ(EM->emList_.size(), 6);

	command->makeResult(EM, "DEL, , , ,employeeNum,69139568");
	EXPECT_EQ(EM->emList_.size(), 5);
	command->makeResult(EM, "DEL, , , ,employeeNum,69149568");
	EXPECT_EQ(EM->emList_.size(), 4);
	command->makeResult(EM, "DEL, , , ,employeeNum,19129568");
	EXPECT_EQ(EM->emList_.size(), 3);

	for (auto stringLine : command->makeResult(EM, "SCH,-p,-m, ,birthday,09")) {
		resultReal.push_back(stringLine);
	}
	resultExpected.push_back("SCH,09129568,SLALH HMEFFEU,CL2,010-7260-1258,19640910,PRO");
	resultExpected.push_back("SCH,12002541,ALWPW HMEFFEU,CL3,010-1522-7258,19640910,ADV");
	resultExpected.push_back("SCH,20123566,SRERL ALHHMEF,CL2,010-1258-5486,19640910,PRO");

	ASSERT_EQ(resultReal.size(), resultExpected.size());
	for (int i = 0; i < resultReal.size(); i++)
	{

		EXPECT_EQ(resultReal[i], resultExpected[i]);
	}
}

TEST_F(CommandTest, ModAndDeleteTest) {
	command->makeResult(EM, "MOD, , , ,name,SRERLALH HMEF,phoneNum,010-1258-9521");
	EXPECT_EQ(EM->emList_.size(), 4);

	command->makeResult(EM, "DEL, ,-m, ,phoneNum,1258");
	EXPECT_EQ(EM->emList_.size(), 2);
	
	for (auto stringLine : command->makeResult(EM, "SCH, ,-m, ,phoneNum,1258")) {
		resultReal.push_back(stringLine);
	}
	resultExpected.push_back("SCH,NONE");
	EXPECT_EQ(EM->emList_.size(), 2);

	ASSERT_EQ(resultReal.size(), resultExpected.size());
	for (int i = 0; i < resultReal.size(); i++)
	{
		EXPECT_EQ(resultReal[i], resultExpected[i]);
	}

}