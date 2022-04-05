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
TEST_F(CommandTest, SortResultTest ) {

	command->makeResult(EM, "ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV");
	command->makeResult(EM, "ADD, , , ,17112609,FB NTAWR,CL4,010-5645-6122,19861203,PRO");
	command->makeResult(EM, "ADD, , , ,18115040,TTETHU HBO,CL3,010-4581-2050,20080718,ADV");
	command->makeResult(EM, "ADD, , , ,88114052,NQ LVARW,CL4,010-4528-3059,19911021,PRO");
	command->makeResult(EM, "ADD, , , ,19129568,SRERLALH HMEF,CL2,010-3091-9521,19640910,PRO");
	command->makeResult(EM, "ADD, , , ,17111236,VSID TVO,CL1,010-3669-1077,20120718,PRO");
	command->makeResult(EM, "ADD, , , ,18117906,TWU QSOLT,CL4,010-6672-7186,20030413,PRO");
	command->makeResult(EM, "ADD, , , ,08123556,WN XV,CL1,010-7986-5047,20100614,PRO");
	command->makeResult(EM, "ADD, , , ,02117175,SBILHUT LDEXRI,CL4,010-2814-1699,19950704,ADV");
	command->makeResult(EM, "ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,19791018,PRO");
	command->makeResult(EM, "ADD, , , ,14130827,RPO JK,CL4,010-3231-1698,20090201,ADV");
	command->makeResult(EM, "ADD, , , ,01122329,DN WD,CL4,010-7174-5680,20071117,PRO");
	command->makeResult(EM, "ADD, , , ,08108827,RTAH VNUP,CL4,010-9031-2726,19780417,ADV");
	command->makeResult(EM, "ADD, , , ,85125741,FBAH RTIJ,CL1,010-8900-1478,19780228,ADV");
	command->makeResult(EM, "ADD, , , ,08117441,BMU MPOSXU,CL3,010-2703-3153,20010215,ADV");
	command->makeResult(EM, "ADD, , , ,10127115,KBU MHU,CL3,010-3284-4054,19660814,ADV");
	command->makeResult(EM, "ADD, , , ,12117017,LFIS JJIVL,CL1,010-7914-4067,20120812,PRO");
	command->makeResult(EM, "ADD, , , ,11125777,TKOQKIS HC,CL1,010-6734-2289,19991001,PRO");
	command->makeResult(EM, "ADD, , , ,11109136,QKAHCEX LTODDO,CL4,010-2627-8566,19640130,PRO");
	command->makeResult(EM, "ADD, , , ,05101762,VCUHLE HMU,CL4,010-3988-9289,20030819,PRO");
	command->makeResult(EM, "SCH,-p,-d, ,birthday,04");
	command->makeResult(EM, "MOD,-p, , ,name,FB NTAWR,birthday,20050520");
	command->makeResult(EM, "SCH, , , ,employeeNum,79110836");
	command->makeResult(EM, "DEL, , , ,employeeNum,18115040");
	command->makeResult(EM, "DEL,-p,-l, ,name,MPOSXU");

	ASSERT_EQ(resultReal.size(), resultExpected.size());
	for (auto stringLine : command->makeResult(EM, "SCH,-p, , ,certi,PRO")) {
		resultReal.push_back(stringLine);
	}
	resultExpected.push_back("SCH,88114052,NQ LVARW,CL4,010-4528-3059,19911021,PRO");
	resultExpected.push_back("SCH,01122329,DN WD,CL4,010-7174-5680,20071117,PRO");
	resultExpected.push_back("SCH,03113260,HH LTUPF,CL2,010-5798-5383,19791018,PRO");
	resultExpected.push_back("SCH,05101762,VCUHLE HMU,CL4,010-3988-9289,20030819,PRO");
	resultExpected.push_back("SCH,08123556,WN XV,CL1,010-7986-5047,20100614,PRO");
	
	EXPECT_EQ(resultReal, resultExpected);
}


TEST_F(CommandTest, ModReturnTest) {
	for (auto stringLine : command->makeResult(EM, "MOD,-p, , ,birthday,19640910,birthday,20050520")) {
		resultReal.push_back(stringLine);
	}
	resultExpected.push_back("MOD,09129568,SLALH HMEFFEU,CL2,010-7260-1258,19640910,PRO");
	resultExpected.push_back("MOD,12002541,ALWPW HMEFFEU,CL3,010-1522-7258,19640910,ADV");
	resultExpected.push_back("MOD,19129568,SRERLALH HMEF,CL2,010-7260-9521,19640910,PRO");
	resultExpected.push_back("MOD,20123566,SRERL ALHHMEF,CL2,010-1258-5486,19640910,PRO");

	ASSERT_EQ(resultReal.size(), resultExpected.size());
	for (int i = 0; i < resultReal.size(); i++)
	{
		EXPECT_EQ(resultReal[i], resultExpected[i]);
	}
}