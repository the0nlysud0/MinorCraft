#pragma once
#include <iostream>
#include <sstream>
#include <deque>
#include <unordered_map>
#include "mb_fileIO.h"



struct MessageInfo {
  int lineIndex;
  int repeatCount = 1;
};

enum class LoggingMode
{
  VERBOSE,
  WARNING,
  ERROR,
  FILE,
};
using std::cout;
using std::cerr;

enum class LogType{
  INFO,
  WARNING,
  ERROR,
};


class mb_logger
{
private:
  std::deque<std::string> m_Messages;
  std::unordered_map<std::string ,MessageInfo> m_RepMap;
  double m_ProgramStart;
  double m_CurrentTime;
  double m_ProgramEnd;
  LoggingMode m_Mode = LoggingMode::VERBOSE;
  std::ofstream m_LogFile;
  std::chrono::system_clock::time_point now;
  time_t time;
  std::ostringstream oss;
  
public:
  mb_logger();
  template <typename... Args>
  void log(LogType type ,Args&&... args);
  void update();
  ~mb_logger();
};


// ? HERE ARE THE TEMPLATED FUNCTIONS
template <typename... Args>
inline void mb_logger::log(LogType type, Args &&...args)
{
  std::ostringstream stream;
  switch (type)
  {
  case LogType::INFO:
    if(m_Mode > LoggingMode::VERBOSE) return;
    cout << "\033[1;32m";
    stream << "[INFO] ";
    break;
  case LogType::WARNING:
    if(m_Mode > LoggingMode::WARNING) return;
    std::cout << "\033[1;33m";
    stream << "[WARNING] ";
    break;
  case LogType::ERROR:
    if(m_Mode > LoggingMode::ERROR) return;
    cout << "\033[1;31m";
    stream << "[ERROR] ";
    break;
  default:
    break;
  }

  ((stream << args), ...);
  std::string CurrentMessage = stream.str();
  auto it = m_RepMap.find(CurrentMessage);
  if (it != m_RepMap.end())
  {
      int count = ++(it->second.repeatCount);
      int linesUp = it->second.lineIndex + 1;
      cout << "\033[" << linesUp << "A"; // move up
      cout << "\r\033[K" << CurrentMessage /*<< " (x" << count << ")"*/ << '\n'<< "\033[0m";
      cout << "\033[" << linesUp << "B" << std::flush; // move back down
      return;
  }
  std::cout << CurrentMessage << "\033[0m" << '\n';
  m_Messages.push_back(CurrentMessage);
  m_RepMap[CurrentMessage].repeatCount = 1;
  m_RepMap[CurrentMessage].lineIndex = static_cast<int>(m_Messages.size());
  if (m_Messages.size() > 100) m_Messages.pop_front();
  m_LogFile << CurrentMessage << '\n';
}
