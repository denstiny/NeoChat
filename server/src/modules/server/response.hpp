#pragma once
#include <string>
#include <map>

const std::string RESULT_ERROR_MESSAGE =
  "{}";

namespace Res {
std::string I_str (std::string str);
};
class Response {
  private:
    using  map = std::map<std::string, std::string>;
    map m_data;
  public:
    Response();
    std::string ErrorResponse();
    Response (map json_data);
    std::string toString();
  private:
    std::string mapToJsonString (map json_data);
};
