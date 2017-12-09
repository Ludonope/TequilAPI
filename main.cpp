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

  core.load("./TestModule.so");
  core.run();
}