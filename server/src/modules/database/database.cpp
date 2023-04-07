#include "database.hpp"

DataSchema::DataSchema (ReConf& conf): resules (nullptr) {
  Connect (conf);
}

DataSchema::~DataSchema() {
  mysql_close (&conn);
}

/**
   @brief connect mysql server database
   @param ip
   @param port
   @param db
*/
void DataSchema::Connect (ReConf& conf)  {
  /* init mysql */
  init_mysql();
  /* load conf */
  char user[100];
  char password[100];
  char database_name[100];
  char mysql_host[100];
  int port;
  
  strncpy (user, conf.GetChar ("DATABASEUSER"), sizeof (user));
  strncpy (database_name, conf.GetChar ("DATABASENAME"), sizeof (database_name));
  strncpy (mysql_host, conf.GetChar ("MYSQL_HOST"), sizeof (mysql_host));
  strncpy (password, conf.GetChar ("DATABASEPASSWORD"), sizeof (password));
  port = conf.GetInt ("DATABASEPORT");
  
  /* connect database */
  if (!mysql_real_connect (&conn, mysql_host, user, password, database_name, port,
                           NULL, 0)) {
    std::cerr << RED << "Connect to database failed" << RESET << std::endl;
    exit (-1);
  }
  std::cout << GREEN << "Connect to databse Successfully" << RESET << std::endl;
}

/**
   @brief init mysql connection
*/
void DataSchema::init_mysql()  {
  if (mysql_library_init (0, NULL, NULL) != 0) {
    exit (1);
  }
  if (mysql_init (&conn) == NULL) {
    exit (1);
  }
  if (mysql_options (&conn, MYSQL_SET_CHARSET_NAME, "utf8") != 0) {
    exit (1);
  }
}

MYSQL_RES* DataSchema::Query (std::string  queryString)  {
  /* free mysql result heap memory */
  if (resules != nullptr) {
    mysql_free_result (resules);
    resules = nullptr;
  }
  if (mysql_query (&conn, queryString.c_str())) {
    std::cerr << RED << "Error: query failed \"" << queryString << "\"" << RESET <<
              std::endl;
    return nullptr;
  }
  
  resules = mysql_store_result (&conn);
  return resules;
}

int DataSchema::CountQuery (MYSQL_RES* res)  {
  return mysql_num_rows (res);
}
