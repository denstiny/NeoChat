#include "ReConf.hpp"
#include <cstring>
#define KEYLEN 50
const static int VALUELEN = BUFSIZ - KEYLEN;

ReConf::ReConf (std::string path) {
  Load (path);
}

/**
   @brief load conf file
   @param path
*/
bool ReConf::Load (std::string path) {
  char buf[BUFSIZ], key[KEYLEN], value[VALUELEN];
  std::fstream f (path);
  if (!f.is_open()) {
    return false;
  }
  while (!f.eof()) {
    f.getline (buf, BUFSIZ);
    sscanf (buf, "%s %s", key, value);
    if (strlen (key) != 0 and strlen (value) != 0) {
      AddData (key, value);
    }
  }
  return true;
}

/* add data to m_map */
void ReConf::AddData (std::string key, std::string value) {
  m_map.insert (std::map<std::string, std::string>::value_type (key, value));
}

const std::map<std::string, std::string>& ReConf::Parse() {
  return this->m_map;
}

const std::string ReConf::GetString (std::string key) {
  if (m_map.count (key) > 0) {
    return m_map.at (key);
  }
  return "";
}

const int ReConf::GetInt (std::string key) {
  if (m_map.count (key) > 0) {
    return std::stoi (m_map.at (key));
  }
  return -1;
}

const char* ReConf::GetChar (std::string key) {
  if (m_map.count (key) > 0) {
    return m_map.at (key).c_str();
  }
  return nullptr;
}
