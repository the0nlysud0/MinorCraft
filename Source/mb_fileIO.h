#pragma once

#include <fstream>
#include <chrono>
#include <vector>
#include <iomanip>
#include <sstream>

inline bool WriteFileLog(const std::string& file_name , std::string data)
{
  std::ofstream out("assets/Logs/"+file_name);
  if(!out.is_open())
  {
    return false;
  }
  auto now = std::chrono::system_clock::now();
  auto time = std::chrono::system_clock::to_time_t(now);
  out << "===== Log file generated at " << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << " =====\n\n";
  out << data;
  out.close();
  return true;
}

inline bool WriteFileLog(const std::string& file_name , std::vector<std::string> data)
{
  std::ofstream out("assets/Logs/"+file_name);
  if(!out.is_open())
  {
    return false;
  }
  auto now = std::chrono::system_clock::now();
  auto time = std::chrono::system_clock::to_time_t(now);
  out << "===== Log file generated at " << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << " =====\n\n";
  for(auto s:data) out << s;
  out.close();
  return true;
}

inline std::string ReadFile(const std::string& file_path)
{
  std::ifstream in(file_path);
  if(!in.is_open())
  {
    std::cout << "\033[1;31m[ERROR] failed to read file " << file_path << '\n';
    return "";
  }
  std::ostringstream ss;
  ss << in.rdbuf();
  return ss.str();
}
