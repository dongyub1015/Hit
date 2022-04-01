#include "pch.h"
#include "../EmployeeManagement/Employee.h"


TEST(EmployeeInfo, GetInfo) {
	Employee worker{"22134345", "Kim SooMin", "CL2", "010-1234-5678", "2000-06-25", "PRO"};

	EXPECT_EQ(worker.getEmployeeNum(), "22134345");
	EXPECT_EQ(worker.getName(), "Kim SooMin");
	EXPECT_EQ(worker.getCL(), "CL2");
	EXPECT_EQ(worker.getPhoneNum(), "010-1234-5678");
	EXPECT_EQ(worker.getBirthday(), "2000-06-25");
	EXPECT_EQ(worker.getCerti(), "PRO");

	worker.setEmployeeNum("19256489");
	worker.setName("Oh HanJin");
	worker.setCL("CL3");
	worker.setPhoneNum("010-9876-5432");
	worker.setBirthday("1997-01-30");
	worker.setCerti("EXT");

	EXPECT_EQ(worker.getEmployeeNum(), "19256489");
	EXPECT_EQ(worker.getName(), "Oh HanJin");
	EXPECT_EQ(worker.getCL(), "CL3");
	EXPECT_EQ(worker.getPhoneNum(), "010-9876-5432");
	EXPECT_EQ(worker.getBirthday(), "1997-01-30");
	EXPECT_EQ(worker.getCerti(), "EXT");
}