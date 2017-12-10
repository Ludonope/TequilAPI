#include <iostream>
#include "ACore.hpp"

class Core : public teq::ACore
{
public:
  virtual void run()
  {
    for (auto logger : m_loggers)
    {
      logger->log(teq::LogType::Info, "IT WORKS");
    }
  }
};

int main()
{
  Core core;
  srand(time(NULL));

  for (int i = 0; i < 10; ++i)
  {
    core.load("./zia_logger.so");
  }
  core.run();
}