#pragma once
#include <fstream>
#include <map>

class ReConf {
  public:
    ReConf() = default;
    ReConf (std::string path);
    bool Load (std::string path);
    const std::map<std::string, std::string>& Parse();
    const std::string GetString (std::string key);
    const int GetInt (std::string key);
    const char* GetChar (std::string key);
  private:
    void AddData (std::string, std::string);
    
  private:
    std::map<std::string, std::string>m_map;
};
