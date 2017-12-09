#if defined(_WIN32)
#include <Windows.h>
#include <cstdbool>
#endif

#if defined(__linux__) || (__APPLE__)
#define MODULE_API
#else
#define MODULE_API __declspec(dllexport)
#endif

#include <memory>
#include <iostream>
#include "TestModule.hpp"
#include "ACore.hpp"

extern "C" {
  MODULE_API teq::IModule *getModule()
  {
    return new TestModule();
  }

#if defined(_WIN32)
  BOOLEAN WINAPI DllMain(HINSTANCE hDllHandle, DWORD nReason, LPVOID Reserved)
  {
    return (true);
  }
#endif
}

std::string const &TestModule::name() const
{
  return m_name;
}

std::string const &TestModule::description() const
{
  return m_desc;
}

void TestModule::init(teq::ACore &core, nlohmann::json const &)
{
  core.loggers().add(this, this);
}

void TestModule::log(teq::LogType type, std::string const &message)
{
  std::cout << static_cast<int>(type) << ": " << message << std::endl;
}