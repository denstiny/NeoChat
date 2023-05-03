#pragma once
#include <string>
#include <unordered_map>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/unistd.h>
#include <iostream>
#include <regex>
#include <Json/json.hpp>

#define SEX_MALE "male"
#define SEX_FEMALE "female"
#define SEX_NEUTRAL "neutral"
enum class Sex {
  male, // 男性
  female, // 女性
  neutral, // 中性
};
const static std::unordered_map<Sex, std::string> SexValue {
  {Sex::male, SEX_MALE},
  {Sex::female, SEX_FEMALE},
  {Sex::neutral, SEX_NEUTRAL},
};

#define MESSAGE_LOGIN "login"
#define MESSAGE_REGISTERED "registered"
#define MESSAGE_TEXT "text"
#define MESSAGE_VOICE "voice"
#define MESSAGE_CALL "call"
#define MESSAGE_VIDEOCALL "videocall"
#define MESSAGE_ADDFREND "addfrend"
#define MESSAGE_USERINFO "userinfo"
#define MESSAGE_CHANGEINFO "changeinfo"

enum class MessageType {
  login, // 登陆
  addfrend, // 添加好友
  registered, // 注册
  text, // 文本
  voice, // 语音
  call, // 电话
  videocall, // 视频电话
  userinfo, // 用户信息
  changeinfo, // 修改用户信息
};

const static std::unordered_map<std::string, MessageType> MessageTypeValue {
  {MESSAGE_LOGIN, MessageType::login},
  {MESSAGE_REGISTERED, MessageType::registered},
  {MESSAGE_TEXT, MessageType::text},
  {MESSAGE_VOICE, MessageType::voice},
  {MESSAGE_CALL, MessageType::call},
  {MESSAGE_VIDEOCALL, MessageType::videocall},
  {MESSAGE_ADDFREND, MessageType::addfrend},
  {MESSAGE_USERINFO, MessageType::userinfo},
  {MESSAGE_CHANGEINFO, MessageType::changeinfo}
};

using Map = std::unordered_map<std::string, std::string>;
Map parseMessageRequestHeaders (std::string header);
void SendMessage (std::string message, int sock);
void ShowMessageHeader (Map header);
void ShowMessageBody (nlohmann::json json);

class Message final {
  public:
    void parseMessage (std::string response);
    void showMessage();
    const std::string getMessageId();
    const std::string getMessageLength();
    const std::string getMessageTotalLength();
    const nlohmann::json getBody();
    const std::string getHeaderVaue (std::string key);
  private:
    Map header;
    nlohmann::json body;
};
