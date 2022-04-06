#include "pch.h"
#include "../EmployeeManagement/ValidityChecker.h"
#include "../EmployeeManagement/ValidityChecker.cpp"
#include "MockValidityChecker.h"

class ValidCheckerTest : public ::testing::Test
{
public:
	ValidCheckerTest() {}
	~ValidCheckerTest() {}

	vector<string> strList;
	ValidChecker* checker;

protected:
	virtual void SetUp() override
	{
		checker = new ValidChecker();
	}

	virtual void TearDown() override { }
};

TEST_F(ValidCheckerTest, Parsing1) {
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

TEST_F(ValidCheckerTest, Parsing2) {
	strList = checker->parseString("ADD, , , ,02117175,SBILHUT LDEXRI,CL4,010-2814-1699,19950704,ADV", ",");

	EXPECT_STREQ(strList[0].c_str(), "ADD") << strList[0].c_str() << " == ADD 이 아니다";
	EXPECT_STREQ(strList[1].c_str(), " ") << strList[1].c_str() << " == " " 이 아니다";
	EXPECT_STREQ(strList[2].c_str(), " ") << strList[2].c_str() << " == " " 이 아니다";

	EXPECT_STRNE(strList[3].c_str(), "") << strList[3].c_str() << " != "" 이 아니다";
	EXPECT_STRNE(strList[4].c_str(), " ") << strList[4].c_str() << " != " " 이 아니다";

	ASSERT_STREQ(strList[4].c_str(), "02117175") << strList[4].c_str() << " == 02117175 이 아니다";
	ASSERT_STRNE(strList[5].c_str(), " ") << strList[5].c_str() << " != " " 이 아니다";
	ASSERT_STRNE(strList[5].c_str(), "") << strList[5].c_str() << " != "" 이 아니다";

	ASSERT_STRCASEEQ(strList[6].c_str(), "CL4") << strList[6].c_str() << " == CL4 이 아니다";
	ASSERT_STRCASENE(strList[6].c_str(), " ") << strList[6].c_str() << " != " " 이 아니다";

	EXPECT_STRCASEEQ(strList[6].c_str(), "cl4") << strList[6].c_str() << " == cl4 이 아니다";
	EXPECT_STRCASEEQ(strList[0].c_str(), "add") << strList[0].c_str() << " == add 이 아니다";
	EXPECT_STRCASENE(strList[6].c_str(), " ") << strList[6].c_str() << " != " " 이 아니다";

	EXPECT_STREQ(strList[7].c_str(), "010-2814-1699") << strList[7].c_str() << " == 010-2814-1699 이 아니다";
	EXPECT_STREQ(strList[8].c_str(), "19950704") << strList[8].c_str() << " == 19950704 이 아니다";
	ASSERT_STRCASEEQ(strList[9].c_str(), "adv") << strList[9].c_str() << "!== ADV 이 아니다";
}

TEST(AddValidChecker, CheckCmdOpt) {
	ValidChecker* checker = new AddValidChecker();

	EXPECT_FALSE(checker->checkValid("ADD, , , ,08117441,BMU MPOSXU,CL3,010-2703-3153"));
	EXPECT_FALSE(checker->checkValid("SCH, , , ,19129568,SRERLALH HMEF,CL2,010-3091-9521,19640910,PRO"));
	ASSERT_FALSE(checker->checkValid("ADD,, , ,14130827,RPO JK,CL4,010-3231-1698,20090201,ADV"));
	EXPECT_FALSE(checker->checkValid("ADD, ,fes , ,14130827,RPO JK,CL4,010-3231-1698,20090201,ADV"));
	EXPECT_FALSE(checker->checkValid("ADD, , ,OPOP,03113260,HH LTUPF,CL2,010-5798-5383,19791018,PRO"));
}

TEST(AddValidChecker, CheckEmployeeNum) {
	ValidChecker* checker = new AddValidChecker();

	ASSERT_TRUE(checker->checkValid("ADD, , , ,19129568,SRERLALH HMEF,CL2,010-3091-9521,19640910,PRO"));
	ASSERT_FALSE(checker->checkValid("ADD, , , ,115040,TTETHU HBO,CL3,010-4581-2050,20080718,ADV"));
	EXPECT_FALSE(checker->checkValid("ADD, , , ,68129568,BILHUT LDEXRI,CL4,010-2814-1699,19950704,ADV"));
	EXPECT_FALSE(checker->checkValid("ADD, , , ,22129568,QKAHCEX LTODDO,CL4,010-2627-8566,19640130,PRO"));
}

TEST(AddValidChecker, CheckEmployeeName) {
	ValidChecker* checker = new AddValidChecker();

	EXPECT_FALSE(checker->checkValid("ADD, , , ,19129568,SRERLALHHMEF,CL2,010-3091-9521,19640910,PRO"));
	EXPECT_FALSE(checker->checkValid("ADD, , , ,19129568, SRERLALH HMEF,CL2,010-3091-9521,19640910,PRO"));
	EXPECT_FALSE(checker->checkValid("ADD, , , ,19129568,SRERLALHHMEF ,CL2,010-3091-9521,19640910,PRO"));
	ASSERT_FALSE(checker->checkValid("ADD, , , ,19129568,SRERLALH HMEFFEU,CL2,010-3091-9521,19640910,PRO"));
	ASSERT_TRUE(checker->checkValid("ADD, , , ,19129568,S H,CL2,010-3091-9521,19640910,PRO"));
}

TEST(AddValidChecker, CheckCL) {
	ValidChecker* checker = new AddValidChecker();

	EXPECT_FALSE(checker->checkValid("ADD, , , ,19129568,SRERLALH HMEF,CL5,010-3091-9521,19640910,PRO"));
	ASSERT_FALSE(checker->checkValid("ADD, , , ,19129568,SRERLALH HMEF, ,010-3091-9521,19640910,PRO"));
}

TEST(AddValidChecker, CheckPhoneNum) {
	ValidChecker* checker = new AddValidChecker();

	EXPECT_EQ(checker->checkValid("ADD, , , ,19129568,S H,CL2,01030919521,19640910,PRO"), false);
	EXPECT_EQ(checker->checkValid("ADD, , , ,19129568,S H,CL2,011-3091-9521,19640910,PRO"), false);
	EXPECT_FALSE(checker->checkValid("ADD, , , ,19129568,S H,CL2,010-3091-921,19640910,PRO"));
	EXPECT_FALSE(checker->checkValid("ADD, , , ,19129568,S H,CL2,010-391-9521,19640910,PRO"));
	ASSERT_FALSE(checker->checkValid("ADD, , , ,19129568,S H,CL2,0103091-9521,19640910,PRO"));
	EXPECT_FALSE(checker->checkValid("ADD, , , ,19129568,S H,CL2,010-30919521,19640910,PRO"));
	EXPECT_FALSE(checker->checkValid("ADD, , , ,19129568,S H,CL2,010-3091-95231,19640910,PRO"));
}

TEST(AddValidChecker, CheckBirthday) {
	ValidChecker* checker = new AddValidChecker();

	EXPECT_FALSE(checker->checkValid("ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,18791018,PRO"));
	ASSERT_FALSE(checker->checkValid("ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,19791518,PRO"));
	EXPECT_FALSE(checker->checkValid("ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,19790018,PRO"));
	ASSERT_FALSE(checker->checkValid("ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,19791000,PRO"));
	EXPECT_FALSE(checker->checkValid("ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,19791032,PRO"));
	EXPECT_FALSE(checker->checkValid("ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,20231018,PRO"));
	ASSERT_FALSE(checker->checkValid("ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,19791318,PRO"));
}

TEST(AddValidChecker, CheckCertiGrade) {
	ValidChecker* checker = new AddValidChecker();

	EXPECT_FALSE(checker->checkValid("ADD, , , ,19129568,S H,CL2,010-3091-9521,19640910,NO"));
	EXPECT_EQ(checker->checkValid("ADD, , , ,19129568,S H,CL2,010-3091-9521,19640910, "), false);
}

TEST(DelValidChecker, CheckCmdOpt) {
	ValidChecker* checker = new DelValidChecker();

	EXPECT_TRUE(checker->checkValid("DEL,-p,-l, ,name,MPOSXU"));
	EXPECT_FALSE(checker->checkValid("MOD,-p,-l, ,name,MPOSXU"));
	EXPECT_FALSE(checker->checkValid("DEL,-p,-l, ,name,MPOSXU,CL2"));
	ASSERT_FALSE(checker->checkValid("DEL, ,-q, ,employeeNum,18115040"));
	EXPECT_FALSE(checker->checkValid("DEL, , ,-f ,name,MPOSXU"));
}

TEST(DelValidChecker, checkSrchCond_fopt) {
	ValidChecker* checker = new DelValidChecker();

	EXPECT_TRUE(checker->checkValid("DEL,-p,-l, ,name,MPOSXU"));
	ASSERT_FALSE(checker->checkValid("DEL,-p,-f, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkValid("DEL,-p,-f, ,name, "));
	ASSERT_FALSE(checker->checkValid("DEL,-p,-f, ,name,KOEKDLELMVKEIOP"));
	ASSERT_FALSE(checker->checkValid("DEL,-p,-f, ,name,KOEELM KE"));
}

TEST(DelValidChecker, checkSrchCond_lopt) {
	ValidChecker* checker = new DelValidChecker();

	ASSERT_FALSE(checker->checkValid("DEL,-p,-l, ,CL,CL2"));
	ASSERT_FALSE(checker->checkValid("DEL, ,-l, ,name,"));
	ASSERT_FALSE(checker->checkValid("DEL,-p,-l, ,name,KOEKDLELMVKEIOP"));
	ASSERT_FALSE(checker->checkValid("DEL, ,-l, ,name,KOEELM KE"));
	ASSERT_FALSE(checker->checkValid("DEL,-p,-l, ,phoneNum,563"));
	ASSERT_FALSE(checker->checkValid("DEL,-p,-l, ,phoneNum,FEGR"));
}

TEST(DelValidChecker, checkSrchCond_mopt) {
	ValidChecker* checker = new DelValidChecker();

	ASSERT_FALSE(checker->checkValid("DEL,-p,-m, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkValid("DEL, ,-m, ,phoneNum,fsetgre"));
	EXPECT_TRUE(checker->checkValid("DEL, ,-m, ,phoneNum,7260"));
	ASSERT_FALSE(checker->checkValid("DEL, ,-m, ,phoneNum,72-60"));
	ASSERT_FALSE(checker->checkValid("DEL, ,-m, ,birthday,2002"));
	ASSERT_FALSE(checker->checkValid("DEL, ,-m, ,birthday,13"));
}

TEST(DelValidChecker, checkSrchCond_yopt) {
	ValidChecker* checker = new DelValidChecker();

	ASSERT_FALSE(checker->checkValid("DEL,-p,-y, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkValid("DEL, ,-y, ,birthday,203"));
	ASSERT_FALSE(checker->checkValid("DEL, ,-y, ,birthday,2303"));
}

TEST(DelValidChecker, checkSrchCond_dopt) {
	ValidChecker* checker = new DelValidChecker();

	ASSERT_FALSE(checker->checkValid("DEL,-p,-d, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkValid("DEL, ,-d, ,birthday,203"));
	ASSERT_FALSE(checker->checkValid("DEL, ,-d, ,birthday,0"));
}


TEST(SchValidChecker, CheckCmdOpt) {
	ValidChecker* checker = new SchValidChecker();

	EXPECT_TRUE(checker->checkValid("SCH,-p,-l, ,name,MPOSXU"));
	EXPECT_FALSE(checker->checkValid("MOD,-p,-l, ,name,MPOSXU"));
	EXPECT_FALSE(checker->checkValid("SCH,-p,-l, ,name,MPOSXU,CL2"));
	ASSERT_FALSE(checker->checkValid("SCH, ,-q, ,employeeNum,18115040"));
	EXPECT_FALSE(checker->checkValid("SCH, , ,-f ,name,MPOSXU"));
}

TEST(SchValidChecker, checkSrchCond_fopt) {
	ValidChecker* checker = new SchValidChecker();

	EXPECT_TRUE(checker->checkValid("SCH,-p,-l, ,name,MPOSXU"));
	ASSERT_FALSE(checker->checkValid("SCH,-p,-f, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkValid("SCH,-p,-f, ,name, "));
	ASSERT_FALSE(checker->checkValid("SCH,-p,-f, ,name,KOEKDLELMVKEIOP"));
	ASSERT_FALSE(checker->checkValid("SCH,-p,-f, ,name,KOEELM KE"));
}

TEST(SchValidChecker, checkSrchCond_lopt) {
	ValidChecker* checker = new SchValidChecker();

	ASSERT_FALSE(checker->checkValid("SCH,-p,-l, ,CL,CL2"));
	ASSERT_FALSE(checker->checkValid("SCH, ,-l, ,name,"));
	ASSERT_FALSE(checker->checkValid("SCH,-p,-l, ,name,KOEKDLELMVKEIOP"));
	ASSERT_FALSE(checker->checkValid("SCH, ,-l, ,name,KOEELM KE"));
	ASSERT_FALSE(checker->checkValid("SCH,-p,-l, ,phoneNum,563"));
	ASSERT_FALSE(checker->checkValid("SCH,-p,-l, ,phoneNum,FEGR"));
}

TEST(SchValidChecker, checkSrchCond_mopt) {
	ValidChecker* checker = new SchValidChecker();

	ASSERT_FALSE(checker->checkValid("SCH,-p,-m, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkValid("SCH, ,-m, ,phoneNum,fsetgre"));
	EXPECT_TRUE(checker->checkValid("SCH, ,-m, ,phoneNum,7260"));
	ASSERT_FALSE(checker->checkValid("SCH, ,-m, ,phoneNum,72-60"));
	ASSERT_FALSE(checker->checkValid("SCH, ,-m, ,birthday,2002"));
	ASSERT_FALSE(checker->checkValid("SCH, ,-m, ,birthday,13"));
}

TEST(SchValidChecker, checkSrchCond_yopt) {
	ValidChecker* checker = new SchValidChecker();

	ASSERT_FALSE(checker->checkValid("SCH,-p,-y, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkValid("SCH, ,-y, ,birthday,203"));
	ASSERT_FALSE(checker->checkValid("SCH, ,-y, ,birthday,2303"));
}

TEST(SchValidChecker, checkSrchCond_dopt) {
	ValidChecker* checker = new SchValidChecker();

	ASSERT_FALSE(checker->checkValid("SCH,-p,-d, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkValid("SCH, ,-d, ,birthday,203"));
	ASSERT_FALSE(checker->checkValid("SCH, ,-d, ,birthday,0"));
}

TEST(ModValidChecker, CheckCmdOpt) {
	ValidChecker* checker = new ModValidChecker();

	ASSERT_TRUE(checker->checkValid("MOD,-p, , ,name,FB NTAWR,birthday,20050520"));
	EXPECT_FALSE(checker->checkValid("DEL,-p,-l, ,name,MPOSXU,birthday,20050520"));
	EXPECT_TRUE(checker->checkValid("MOD,-p,-l, ,name,MPOSXU,cl,CL3"));
	ASSERT_FALSE(checker->checkValid("MOD, ,-q, ,employeeNum,18115040"));
	EXPECT_FALSE(checker->checkValid("MOD, , ,-f ,name,MPOSXU"));
}

TEST(ModValidChecker, checkSrchCond_fopt) {
	ValidChecker* checker = new ModValidChecker();

	EXPECT_TRUE(checker->checkValid("MOD,-p,-l, ,name,MPOSXU,birthday,20050520"));
	ASSERT_FALSE(checker->checkValid("MOD,-p,-f, ,employeeNum,cl,CL3"));
	ASSERT_FALSE(checker->checkValid("MOD,-p,-f, ,name, ,birthday,20050520"));
	ASSERT_FALSE(checker->checkValid("MOD,-p,-f, ,name,KOEKDLELMVKEIOP,birthday,20050520"));
	ASSERT_FALSE(checker->checkValid("MOD,-p,-f, ,name,KOEELM KE,cl,CL3"));
}

TEST(ModValidChecker, checkSrchCond_lopt) {
	ValidChecker* checker = new ModValidChecker();

	ASSERT_FALSE(checker->checkValid("MOD,-p,-l, ,CL,CL2,cl,CL3"));
	ASSERT_FALSE(checker->checkValid("MOD, ,-l, ,name,,birthday,20050520"));
	ASSERT_FALSE(checker->checkValid("MOD,-p,-l, ,name,KOEKDLELMVKEIOP,cl,CL3"));
	ASSERT_FALSE(checker->checkValid("MOD, ,-l, ,name,KOEELM KE,birthday,20050520"));
	ASSERT_FALSE(checker->checkValid("MOD,-p,-l, ,phoneNum,563,birthday,20050520"));
	ASSERT_FALSE(checker->checkValid("MOD,-p,-l, ,phoneNum,FEGR,cl,CL3"));
}

TEST(ModValidChecker, checkSrchCond_mopt) {
	ValidChecker* checker = new ModValidChecker();

	ASSERT_FALSE(checker->checkValid("MOD,-p,-m, ,employeeNum,18115040,cl,CL3"));
	ASSERT_FALSE(checker->checkValid("MOD, ,-m, ,phoneNum,fsetgre,birthday,19910808"));
	EXPECT_TRUE(checker->checkValid("MOD, ,-m, ,phoneNum,7260,birthday,19910808"));
	ASSERT_FALSE(checker->checkValid("MOD, ,-m, ,phoneNum,72-60,cl,CL3"));
	ASSERT_FALSE(checker->checkValid("MOD, ,-m, ,birthday,2002,birthday,19910808"));
	ASSERT_FALSE(checker->checkValid("MOD, ,-m, ,birthday,13,birthday,19910808"));
}

TEST(ModValidChecker, checkSrchCond_yopt) {
	ValidChecker* checker = new ModValidChecker();

	ASSERT_FALSE(checker->checkValid("MOD,-p,-y, ,employeeNum,18115040,birthday,19910808"));
	ASSERT_FALSE(checker->checkValid("MOD, ,-y, ,birthday,203,cl,CL3"));
	ASSERT_FALSE(checker->checkValid("MOD, ,-y, ,birthday,2303,birthday,19910808"));
}

TEST(ModValidChecker, checkSrchCond_dopt) {
	ValidChecker* checker = new ModValidChecker();

	ASSERT_FALSE(checker->checkValid("MOD,-p,-d, ,employeeNum,18115040"));
	ASSERT_FALSE(checker->checkValid("MOD, ,-d, ,birthday,203,cl,CL3"));
	ASSERT_FALSE(checker->checkValid("MOD, ,-d, ,birthday,0,birthday,19910808"));
}

TEST(ModValidChecker, checkSrchCond_modInfo) {
	ValidChecker* checker = new ModValidChecker();

	ASSERT_FALSE(checker->checkValid("MOD, ,-d, ,birthday,5,cl,CL5"));
	ASSERT_FALSE(checker->checkValid("MOD, ,-d, ,birthday,0,birthday,199108008"));
	ASSERT_FALSE(checker->checkValid("MOD, ,-d, ,birthday,0,employee,07414900"));
	ASSERT_FALSE(checker->checkValid("MOD, ,-d, ,birthday,0,CERI,EEXT"));
}

TEST(ModValidChecker, checkSrchCond_NoneOpt) {
	ValidChecker* checker = new ModValidChecker();

	ASSERT_FALSE(checker->checkValid("MOD, , , ,employee,18115040, birthday,20020311"));
	ASSERT_FALSE(checker->checkValid("MOD, , , ,birthday,20011318,CL,CL3"));
	ASSERT_FALSE(checker->checkValid("MOD, , , , ,0,birthday,19910808"));
	EXPECT_TRUE(checker->checkValid("MOD, , , ,phoneNum,010-7260-2826,birthday,19910808"));
}

using  ::testing::AtLeast;
using  ::testing::Return;

TEST(CommandValidity, checkValidFunc) {
	MockValidChecker  MockChecker("ADD, , , ,11125777,TKOQKIS HC,CL1,010-6734-2289,19991001,PRO");

	EXPECT_CALL(MockChecker, checkValid(MockChecker.str1)).Times(1).WillOnce(Return(true));
	EXPECT_TRUE(MockChecker.checkValid(MockChecker.str1));
}