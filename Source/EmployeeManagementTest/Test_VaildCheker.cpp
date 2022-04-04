#include "pch.h"
#include "../EmployeeManagement/VaildChecker.h"
#include "../EmployeeManagement/VaildChecker.cpp"

class VaildCheckerTest : public ::testing::Test 
{
public:
	VaildCheckerTest() {}
	~VaildCheckerTest() {}

	vector<string> strList;
	VaildChecker* checker;

protected:
	virtual void SetUp() override
	{
		checker = new VaildChecker();
	}

	virtual void TearDown() override
	{
	}
};

TEST_F(VaildCheckerTest, Parsing1) {
	strList = checker->parseString("ADD,,,,123,432", ",");

	EXPECT_EQ((strList[0] == "ADD"), true) << "This is not ADD command";
	EXPECT_EQ((strList.size() == 6), true) << "size should be 6";
	EXPECT_NE((strList[2] == "123"), true);

	strList = checker->parseString("MOD,-p,-m,,KIM,CL2,PRO", ",");

	ASSERT_EQ((strList[0] == "MOD"), true) << "This is not MOD command";
	EXPECT_EQ((strList.size() == 7), true) << "size should be 6";
	EXPECT_EQ((strList[1] == "-p"), true);
	EXPECT_EQ((strList[2] == "-m"), true);
	EXPECT_EQ((strList[3] == ""), true);
	ASSERT_EQ((strList[4] == "KIM"), true);
}

TEST_F(VaildCheckerTest, Parsing2) {
	strList = checker->parseString("ADD, , , ,02117175,SBILHUT LDEXRI,CL4,010-2814-1699,19950704,ADV", ",");

	EXPECT_STREQ(strList[0].c_str(), "ADD") << strList[0].c_str() << " == ADD �� �ƴϴ�";
	EXPECT_STREQ(strList[1].c_str(), " ") << strList[1].c_str() << " == " " �� �ƴϴ�";
	EXPECT_STREQ(strList[2].c_str(), " ") << strList[2].c_str() << " == " " �� �ƴϴ�";

	EXPECT_STRNE(strList[3].c_str(), "") << strList[3].c_str() << " != "" �� �ƴϴ�";
	EXPECT_STRNE(strList[4].c_str(), " ") << strList[4].c_str() << " != " " �� �ƴϴ�";

	ASSERT_STREQ(strList[4].c_str(), "02117175") << strList[4].c_str() << " == 02117175 �� �ƴϴ�";
	ASSERT_STRNE(strList[5].c_str(), " ") << strList[5].c_str() << " != " " �� �ƴϴ�";
	ASSERT_STRNE(strList[5].c_str(), "") << strList[5].c_str() << " != "" �� �ƴϴ�";

	ASSERT_STRCASEEQ(strList[6].c_str(), "CL4") << strList[6].c_str() << " == CL4 �� �ƴϴ�";
	ASSERT_STRCASENE(strList[6].c_str(), " ") << strList[6].c_str() << " != " " �� �ƴϴ�";

	EXPECT_STRCASEEQ(strList[6].c_str(), "cl4") << strList[6].c_str() << " == cl4 �� �ƴϴ�";
	EXPECT_STRCASEEQ(strList[0].c_str(), "add") << strList[0].c_str() << " == add �� �ƴϴ�";
	EXPECT_STRCASENE(strList[6].c_str(), " ") << strList[6].c_str() << " != " " �� �ƴϴ�";

	EXPECT_STREQ(strList[7].c_str(), "010-2814-1699") << strList[7].c_str() << " == 010-2814-1699 �� �ƴϴ�";
	EXPECT_STREQ(strList[8].c_str(), "19950704") << strList[8].c_str() << " == 19950704 �� �ƴϴ�";
	ASSERT_STRCASEEQ(strList[9].c_str(), "adv") << strList[9].c_str() << "!== ADV �� �ƴϴ�";
}

TEST(AddVaildChecker, CheckCmdOpt) {
	VaildChecker* checker = new AddVaildChecker();

	EXPECT_FALSE(checker->checkVaild("ADD, , , ,08117441,BMU MPOSXU,CL3,010-2703-3153"));
	EXPECT_FALSE(checker->checkVaild("SCH, , , ,19129568,SRERLALH HMEF,CL2,010-3091-9521,19640910,PRO"));
	ASSERT_FALSE(checker->checkVaild("ADD,, , ,14130827,RPO JK,CL4,010-3231-1698,20090201,ADV"));
	EXPECT_FALSE(checker->checkVaild("ADD, ,fes , ,14130827,RPO JK,CL4,010-3231-1698,20090201,ADV"));
	EXPECT_FALSE(checker->checkVaild("ADD, , ,OPOP,03113260,HH LTUPF,CL2,010-5798-5383,19791018,PRO"));
}

TEST(AddVaildChecker, CheckEmployeeNum) {
	VaildChecker* checker = new AddVaildChecker();

	ASSERT_TRUE(checker->checkVaild("ADD, , , ,19129568,SRERLALH HMEF,CL2,010-3091-9521,19640910,PRO"));
	ASSERT_FALSE(checker->checkVaild("ADD, , , ,115040,TTETHU HBO,CL3,010-4581-2050,20080718,ADV"));
	EXPECT_FALSE(checker->checkVaild("ADD, , , ,68129568,BILHUT LDEXRI,CL4,010-2814-1699,19950704,ADV"));
	EXPECT_FALSE(checker->checkVaild("ADD, , , ,22129568,QKAHCEX LTODDO,CL4,010-2627-8566,19640130,PRO"));
}

TEST(AddVaildChecker, CheckEmployeeName) {
	VaildChecker* checker = new AddVaildChecker();

	EXPECT_FALSE(checker->checkVaild("ADD, , , ,19129568,SRERLALHHMEF,CL2,010-3091-9521,19640910,PRO"));
	EXPECT_FALSE(checker->checkVaild("ADD, , , ,19129568, SRERLALH HMEF,CL2,010-3091-9521,19640910,PRO"));
	EXPECT_FALSE(checker->checkVaild("ADD, , , ,19129568,SRERLALHHMEF ,CL2,010-3091-9521,19640910,PRO"));
	ASSERT_FALSE(checker->checkVaild("ADD, , , ,19129568,SRERLALH HMEFFEU,CL2,010-3091-9521,19640910,PRO"));
	ASSERT_TRUE(checker->checkVaild("ADD, , , ,19129568,S H,CL2,010-3091-9521,19640910,PRO"));
}

TEST(AddVaildChecker, CheckCL) {
	VaildChecker* checker = new AddVaildChecker();

	EXPECT_FALSE(checker->checkVaild("ADD, , , ,19129568,SRERLALH HMEF,CL5,010-3091-9521,19640910,PRO"));
	ASSERT_FALSE(checker->checkVaild("ADD, , , ,19129568,SRERLALH HMEF, ,010-3091-9521,19640910,PRO"));
}

TEST(AddVaildChecker, CheckPhoneNum) {
	VaildChecker* checker = new AddVaildChecker();

	EXPECT_EQ(checker->checkVaild("ADD, , , ,19129568,S H,CL2,01030919521,19640910,PRO"), false);
	EXPECT_EQ(checker->checkVaild("ADD, , , ,19129568,S H,CL2,011-3091-9521,19640910,PRO"), false);
	EXPECT_FALSE(checker->checkVaild("ADD, , , ,19129568,S H,CL2,010-3091-921,19640910,PRO"));
	EXPECT_FALSE(checker->checkVaild("ADD, , , ,19129568,S H,CL2,010-391-9521,19640910,PRO"));
	ASSERT_FALSE(checker->checkVaild("ADD, , , ,19129568,S H,CL2,0103091-9521,19640910,PRO"));
	EXPECT_FALSE(checker->checkVaild("ADD, , , ,19129568,S H,CL2,010-30919521,19640910,PRO"));
	EXPECT_FALSE(checker->checkVaild("ADD, , , ,19129568,S H,CL2,010-3091-95231,19640910,PRO"));
}

TEST(AddVaildChecker, CheckBirthday) {
	VaildChecker* checker = new AddVaildChecker();

	EXPECT_FALSE(checker->checkVaild("ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,18791018,PRO"));
	ASSERT_FALSE(checker->checkVaild("ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,19791518,PRO"));
	EXPECT_FALSE(checker->checkVaild("ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,19790018,PRO"));
	ASSERT_FALSE(checker->checkVaild("ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,19791000,PRO"));
	EXPECT_FALSE(checker->checkVaild("ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,19791032,PRO"));
	EXPECT_FALSE(checker->checkVaild("ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,20231018,PRO"));
	ASSERT_FALSE(checker->checkVaild("ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,19791318,PRO"));
}

TEST(AddVaildChecker, CheckCertiGrade) {
	VaildChecker* checker = new AddVaildChecker();

	EXPECT_FALSE(checker->checkVaild("ADD, , , ,19129568,S H,CL2,010-3091-9521,19640910,NO"));
	EXPECT_EQ(checker->checkVaild("ADD, , , ,19129568,S H,CL2,010-3091-9521,19640910, "), false);
}

TEST(DelVaildChecker, CheckCmdOpt) {
	VaildChecker* checker = new DelVaildChecker();

	EXPECT_TRUE(checker->checkVaild("DEL,-p,-l, ,name,MPOSXU"));
	EXPECT_FALSE(checker->checkVaild("MOD,-p,-l, ,name,MPOSXU"));
	EXPECT_FALSE(checker->checkVaild("DEL,-p,-l, ,name,MPOSXU,CL2"));
	ASSERT_FALSE(checker->checkVaild("DEL, ,-q, ,employeeNum,18115040"));
	EXPECT_FALSE(checker->checkVaild("DEL, , ,-f ,name,MPOSXU"));
}

TEST(DelVaildChecker, checkSrchCond_fopt) {
	VaildChecker* checker = new DelVaildChecker();

	EXPECT_TRUE(checker->checkVaild("DEL,-p,-l, ,name,MPOSXU"));
	ASSERT_FALSE(checker->checkVaild("DEL,-p,-f, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkVaild("DEL,-p,-f, ,name, "));
	ASSERT_FALSE(checker->checkVaild("DEL,-p,-f, ,name,KOEKDLELMVKEIOP"));
	ASSERT_FALSE(checker->checkVaild("DEL,-p,-f, ,name,KOEELM KE"));
}

TEST(DelVaildChecker, checkSrchCond_lopt) {
	VaildChecker* checker = new DelVaildChecker();

	ASSERT_FALSE(checker->checkVaild("DEL,-p,-l, ,CL,CL2"));
	ASSERT_FALSE(checker->checkVaild("DEL, ,-l, ,name,"));
	ASSERT_FALSE(checker->checkVaild("DEL,-p,-l, ,name,KOEKDLELMVKEIOP"));
	ASSERT_FALSE(checker->checkVaild("DEL, ,-l, ,name,KOEELM KE"));
	ASSERT_FALSE(checker->checkVaild("DEL,-p,-l, ,phoneNum,563"));
	ASSERT_FALSE(checker->checkVaild("DEL,-p,-l, ,phoneNum,FEGR"));
}

TEST(DelVaildChecker, checkSrchCond_mopt) {
	VaildChecker* checker = new DelVaildChecker();

	ASSERT_FALSE(checker->checkVaild("DEL,-p,-m, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkVaild("DEL, ,-m, ,phoneNum,fsetgre"));
	EXPECT_TRUE(checker->checkVaild("DEL, ,-m, ,phoneNum,7260"));
	ASSERT_FALSE(checker->checkVaild("DEL, ,-m, ,phoneNum,72-60"));
	ASSERT_FALSE(checker->checkVaild("DEL, ,-m, ,birthday,2002"));
	ASSERT_FALSE(checker->checkVaild("DEL, ,-m, ,birthday,13"));
}

TEST(DelVaildChecker, checkSrchCond_yopt) {
	VaildChecker* checker = new DelVaildChecker();

	ASSERT_FALSE(checker->checkVaild("DEL,-p,-y, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkVaild("DEL, ,-y, ,birthday,203"));
	ASSERT_FALSE(checker->checkVaild("DEL, ,-y, ,birthday,2303"));
}

TEST(DelVaildChecker, checkSrchCond_dopt) {
	VaildChecker* checker = new DelVaildChecker();

	ASSERT_FALSE(checker->checkVaild("DEL,-p,-d, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkVaild("DEL, ,-d, ,birthday,203"));
	ASSERT_FALSE(checker->checkVaild("DEL, ,-d, ,birthday,0"));
}


TEST(SchVaildChecker, CheckCmdOpt) {
	VaildChecker* checker = new SchVaildChecker();

	EXPECT_TRUE(checker->checkVaild("SCH,-p,-l, ,name,MPOSXU"));
	EXPECT_FALSE(checker->checkVaild("MOD,-p,-l, ,name,MPOSXU"));
	EXPECT_FALSE(checker->checkVaild("SCH,-p,-l, ,name,MPOSXU,CL2"));
	ASSERT_FALSE(checker->checkVaild("SCH, ,-q, ,employeeNum,18115040"));
	EXPECT_FALSE(checker->checkVaild("SCH, , ,-f ,name,MPOSXU"));
}

TEST(SchVaildChecker, checkSrchCond_fopt) {
	VaildChecker* checker = new SchVaildChecker();

	EXPECT_TRUE(checker->checkVaild("SCH,-p,-l, ,name,MPOSXU"));
	ASSERT_FALSE(checker->checkVaild("SCH,-p,-f, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkVaild("SCH,-p,-f, ,name, "));
	ASSERT_FALSE(checker->checkVaild("SCH,-p,-f, ,name,KOEKDLELMVKEIOP"));
	ASSERT_FALSE(checker->checkVaild("SCH,-p,-f, ,name,KOEELM KE"));
}

TEST(SchVaildChecker, checkSrchCond_lopt) {
	VaildChecker* checker = new SchVaildChecker();

	ASSERT_FALSE(checker->checkVaild("SCH,-p,-l, ,CL,CL2"));
	ASSERT_FALSE(checker->checkVaild("SCH, ,-l, ,name,"));
	ASSERT_FALSE(checker->checkVaild("SCH,-p,-l, ,name,KOEKDLELMVKEIOP"));
	ASSERT_FALSE(checker->checkVaild("SCH, ,-l, ,name,KOEELM KE"));
	ASSERT_FALSE(checker->checkVaild("SCH,-p,-l, ,phoneNum,563"));
	ASSERT_FALSE(checker->checkVaild("SCH,-p,-l, ,phoneNum,FEGR"));
}

TEST(SchVaildChecker, checkSrchCond_mopt) {
	VaildChecker* checker = new SchVaildChecker();

	ASSERT_FALSE(checker->checkVaild("SCH,-p,-m, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkVaild("SCH, ,-m, ,phoneNum,fsetgre"));
	EXPECT_TRUE(checker->checkVaild("SCH, ,-m, ,phoneNum,7260"));
	ASSERT_FALSE(checker->checkVaild("SCH, ,-m, ,phoneNum,72-60"));
	ASSERT_FALSE(checker->checkVaild("SCH, ,-m, ,birthday,2002"));
	ASSERT_FALSE(checker->checkVaild("SCH, ,-m, ,birthday,13"));
}

TEST(SchVaildChecker, checkSrchCond_yopt) {
	VaildChecker* checker = new SchVaildChecker();

	ASSERT_FALSE(checker->checkVaild("SCH,-p,-y, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkVaild("SCH, ,-y, ,birthday,203"));
	ASSERT_FALSE(checker->checkVaild("SCH, ,-y, ,birthday,2303"));
}

TEST(SchVaildChecker, checkSrchCond_dopt) {
	VaildChecker* checker = new SchVaildChecker();

	ASSERT_FALSE(checker->checkVaild("SCH,-p,-d, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkVaild("SCH, ,-d, ,birthday,203"));
	ASSERT_FALSE(checker->checkVaild("SCH, ,-d, ,birthday,0"));
}

TEST(ModVaildChecker, CheckCmdOpt) {
	VaildChecker* checker = new ModVaildChecker();

	ASSERT_TRUE(checker->checkVaild("MOD,-p, , ,name,FB NTAWR,birthday,20050520"));
	EXPECT_FALSE(checker->checkVaild("DEL,-p,-l, ,name,MPOSXU,birthday,20050520"));
	EXPECT_FALSE(checker->checkVaild("MOD,-p,-l, ,name,MPOSXU,cl,CL3"));
	ASSERT_FALSE(checker->checkVaild("MOD, ,-q, ,employeeNum,18115040"));
	EXPECT_FALSE(checker->checkVaild("MOD, , ,-f ,name,MPOSXU"));
}

TEST(ModVaildChecker, checkSrchCond_fopt) {
	VaildChecker* checker = new ModVaildChecker();

	EXPECT_TRUE(checker->checkVaild("MOD,-p,-l, ,name,MPOSXU,birthday,20050520"));
	ASSERT_FALSE(checker->checkVaild("MOD,-p,-f, ,employeeNum,cl,CL3"));
	ASSERT_FALSE(checker->checkVaild("MOD,-p,-f, ,name, ,birthday,20050520"));
	ASSERT_FALSE(checker->checkVaild("MOD,-p,-f, ,name,KOEKDLELMVKEIOP,birthday,20050520"));
	ASSERT_FALSE(checker->checkVaild("MOD,-p,-f, ,name,KOEELM KE,cl,CL3"));
}

TEST(ModVaildChecker, checkSrchCond_lopt) {
	VaildChecker* checker = new ModVaildChecker();

	ASSERT_FALSE(checker->checkVaild("MOD,-p,-l, ,CL,CL2,cl,CL3"));
	ASSERT_FALSE(checker->checkVaild("MOD, ,-l, ,name,,birthday,20050520"));
	ASSERT_FALSE(checker->checkVaild("MOD,-p,-l, ,name,KOEKDLELMVKEIOP,cl,CL3"));
	ASSERT_FALSE(checker->checkVaild("MOD, ,-l, ,name,KOEELM KE,birthday,20050520"));
	ASSERT_FALSE(checker->checkVaild("MOD,-p,-l, ,phoneNum,563,birthday,20050520"));
	ASSERT_FALSE(checker->checkVaild("MOD,-p,-l, ,phoneNum,FEGR,cl,CL3"));
}

TEST(ModVaildChecker, checkSrchCond_mopt) {
	VaildChecker* checker = new ModVaildChecker();

	ASSERT_FALSE(checker->checkVaild("MOD,-p,-m, ,employeeNum,18115040,cl,CL3"));
	ASSERT_FALSE(checker->checkVaild("MOD, ,-m, ,phoneNum,fsetgre,birthday,19910808"));
	EXPECT_TRUE(checker->checkVaild("MOD, ,-m, ,phoneNum,7260,birthday,19910808"));
	ASSERT_FALSE(checker->checkVaild("MOD, ,-m, ,phoneNum,72-60,cl,CL3"));
	ASSERT_FALSE(checker->checkVaild("MOD, ,-m, ,birthday,2002,birthday,19910808"));
	ASSERT_FALSE(checker->checkVaild("MOD, ,-m, ,birthday,13,birthday,19910808"));
}

TEST(ModVaildChecker, checkSrchCond_yopt) {
	VaildChecker* checker = new ModVaildChecker();

	ASSERT_FALSE(checker->checkVaild("MOD,-p,-y, ,employeeNum,18115040,birthday,19910808"));
	ASSERT_FALSE(checker->checkVaild("MOD, ,-y, ,birthday,203,cl,CL3"));
	ASSERT_FALSE(checker->checkVaild("MOD, ,-y, ,birthday,2303,birthday,19910808"));
}

TEST(ModVaildChecker, checkSrchCond_dopt) {
	VaildChecker* checker = new ModVaildChecker();

	ASSERT_FALSE(checker->checkVaild("MOD,-p,-d, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkVaild("MOD, ,-d, ,birthday,203,cl,CL3"));
	ASSERT_FALSE(checker->checkVaild("MOD, ,-d, ,birthday,0,birthday,19910808"));
}

TEST(ModVaildChecker, checkSrchCond_modInfo) {
	VaildChecker* checker = new ModVaildChecker();

	ASSERT_FALSE(checker->checkVaild("MOD, ,-d, ,birthday,5,cl,CL5"));
	ASSERT_FALSE(checker->checkVaild("MOD, ,-d, ,birthday,0,birthday,199108008"));
	ASSERT_FALSE(checker->checkVaild("MOD, ,-d, ,birthday,0,employee,07414900"));
	ASSERT_FALSE(checker->checkVaild("MOD, ,-d, ,birthday,0,CERI,EEXT"));
}