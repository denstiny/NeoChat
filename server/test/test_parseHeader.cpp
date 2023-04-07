#include "Message/MessageProcessor.hpp"

int main (int argc, char* argv[]) {
  std::string str = "status: post\r\n";
  Map a =  parseMessageRequestHeaders (str);
  std::cout << a.at ("status") << std::endl;
  return 0;
}
