#pragma once
#include "ReConf/ReConf.hpp"
#include "colorcout/colorcout.hpp"
#include <cstring>
#include <iostream>
#include <cassert>
#include <mysql.h>

class DataSchema {
  public:
    DataSchema() {};
    DataSchema (ReConf& conf);
    // connect mysql
    void Connect (ReConf& conf);
    // query mysql
    MYSQL_RES* Query (std::string queryString);
    int CountQuery (MYSQL_RES*);
    ~DataSchema();
  private:
    void init_mysql();
    MYSQL conn;
    MYSQL_RES* resules;
};
