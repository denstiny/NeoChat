#include "./response.hpp"
#include "Json/json.hpp"


Response::Response()  {}

Response::Response (map json_data)  {
  this->m_data = json_data;
}

/**
   @brief 将 data转换成字符串包装成http相应头
   @return
*/
std::string Response::toString() {
  std::string res;
  std::string data = mapToJsonString (m_data);
  res += "Content-Length: " + std::to_string (data.size());
  res += "\r\n\r\n";
  res += data;
  return res;
}

/**
   @brief map 转换成json 字符串
   @param json_data
   @return
*/
std::string Response::mapToJsonString (map json_data) {
  return nlohmann::json (json_data).dump();
  //TODO: json支持任意类型
}

std::string Response::ErrorResponse() {
  return RESULT_ERROR_MESSAGE;
}

std::string Res::I_str (std::string str) {
  return '\"' + str + '\"';
}
