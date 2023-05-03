#include "./log.hpp"

#ifdef NDEBUG
void colorcout (const char* color, std::string message) {
  std::cout << color << message << RESET << std::endl;
}
#else
void colorcout (const char* color, std::string message) {}
#endif
