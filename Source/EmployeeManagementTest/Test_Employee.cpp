#include "pch.h"
#include "../EmployeeManagement/Employee.h"


TEST(EmployeeInfo, GetInfo) {
	Employee worker{"22134345", "KIM SOOMIN", "CL2", "010-1234-5678", "20000625", "PRO"};

	EXPECT_EQ(worker.getEmployeeNum(), "22134345");
	EXPECT_EQ(worker.getName(), "KIM SOOMIN");
	EXPECT_EQ(worker.getCL(), "CL2");
	EXPECT_EQ(worker.getPhoneNum(), "010-1234-5678");
	EXPECT_EQ(worker.getBirthday(), "20000625");
	EXPECT_EQ(worker.getCerti(), "PRO");

	worker.setEmployeeNum("19256489");
	worker.setName("OH HANJIN");
	worker.setCL("CL3");
	worker.setPhoneNum("010-9876-5432");
	worker.setBirthday("19970130");
	worker.setCerti("EXT");

	EXPECT_EQ(worker.getEmployeeNum(), "19256489");
	EXPECT_EQ(worker.getName(), "OH HANJIN");
	EXPECT_EQ(worker.getCL(), "CL3");
	EXPECT_EQ(worker.getPhoneNum(), "010-9876-5432");
	EXPECT_EQ(worker.getBirthday(), "19970130");
	EXPECT_EQ(worker.getCerti(), "EXT");
}