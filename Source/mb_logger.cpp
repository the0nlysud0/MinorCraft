#include "mb_logger.h"
#include <chrono>


mb_logger::mb_logger()
{
  m_ProgramStart = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
  m_CurrentTime = m_ProgramStart;
  now = std::chrono::system_clock::now();
  time = std::chrono::system_clock::to_time_t(now);
  oss << std::put_time(std::localtime(&time), "%Y-%m-%d_%H-%M-%S");

  std::string timestamp = oss.str();
  std::string filename = "assets/Logs/" + timestamp + ".txt";
  m_LogFile.open("assets/Logs/log.txt");
}

void mb_logger::update()
{
    if (!m_LogFile.is_open())
    {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time), "%Y-%m-%d_%H-%M-%S");

        std::string timestamp = oss.str();
        std::string filename = "assets/Logs/" + timestamp + ".txt";
        m_LogFile.open(filename, std::ios_base::trunc);
    }

    if (!m_LogFile.is_open()) return;

    m_LogFile.seekp(0);
    for (auto& p : m_Messages)
    {
        m_LogFile << p << '\n';
    }
    m_LogFile.flush();
}


mb_logger::~mb_logger()
{
  m_ProgramEnd = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();

}
