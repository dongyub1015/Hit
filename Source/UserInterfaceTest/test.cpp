#include "pch.h"
#include <string>
#include "../EmployeeManagement/InputInterpreter.h"
using namespace std;

TEST(InputInterpreterTest, ReadFileTest) {
    InputInterpreter input("input_20_20_tmp.txt");
    EXPECT_TRUE(input.openFile());
    string tmp;
    //EXPECT_EQ(tmp, input.readFile());
    EXPECT_TRUE(("ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV" == input.readFile()));
}
