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

  std::cout << "Loading" << std::endl;
  core.load("./TestModule.so");
  std::cout << "Run" << std::endl;
  core.run();
  std::cout << "Finish" << std::endl;
}