#include "pch.h"
#include "../EmployeeManagement/VaildChecker.h"


TEST(VaildChecker, AddVaild) {
	VaildChecker* checker = new AddVaildChecker();

	EXPECT_EQ(checker->checkVaild(""), false);
}

TEST(VaildChecker, ModVaild) {
	VaildChecker* checker = new ModVaildChecker();

	EXPECT_EQ(checker->checkVaild(""), false);
}

TEST(VaildChecker, DelVaild) {
	VaildChecker* checker = new DelVaildChecker();

	EXPECT_EQ(checker->checkVaild(""), false);
}

TEST(VaildChecker, SchVaild) {
	VaildChecker* checker = new SchVaildChecker();

	EXPECT_EQ(checker->checkVaild(""), false);
}