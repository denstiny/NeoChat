#include "database/database.hpp"
#include "ReConf/ReConf.hpp"

int main (int argc, char* argv[]) {
  ReConf conf (CONFIGPATH);
  DataSchema bd (conf);
  if (!bd.Query ("INSERT INTO m_base.`User` (user_account,user_password,user_name,user_phone,sex,birthday,address) VALUES ('101','asd','李维','10086','neutral','2001-01-02','中国北京'); ")) {
    std::cerr << "插入数据失败" << std::endl;
  }
  
  auto a = bd.Query ("select * from m_base.User");
  MYSQL_ROW row;
  while ((row = mysql_fetch_row (a))) {
    std::cerr << row[0] << " ";
    std::cerr << row[1] << " ";
    std::cerr << row[2] << " ";
    std::cerr << row[3] << " ";
    std::cerr << row[4] << " ";
    std::cerr << row[5] << " ";
    std::cerr << row[6] << " ";
    std::cerr << row[7] << " " << std::endl;
  }
  return 0;
}
