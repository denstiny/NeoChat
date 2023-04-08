#include "Message/MessageProcessor.hpp"
#include <gtest/gtest.h>

class Tst_ParseHead: public testing::Test
{

};

TEST_F(Tst_ParseHead, ParseTest) {
  std::string str = "status: post\r\n";
  Map a =  parseMessageRequestHeaders (str);
  std::cout << a.at ("status") << std::endl;
}
