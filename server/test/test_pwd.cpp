#include <gtest/gtest.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <variant>
class Tst_Pwd: public testing::Test
{

};
TEST_F(Tst_Pwd, PwdTest)
{
    char *buffer;
    EXPECT_NE(getcwd(NULL, 0), nullptr);
}
