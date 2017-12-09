#include <iostream>
#include "ACore.hpp"
#include "utils/GenModule.hpp"

namespace teq
{
  void ACore::set(IConfigLoader *module)
  {
    if (m_configLoader)
    {
      this->unset(m_configLoader);
    }
    m_configLoader = module;
  }

  void ACore::set(IConnection *module)
  {
    if (m_connection)
    {
      this->unset(m_connection);
    }
    m_connection = module;
    m_connection->enable();
  }

  void ACore::unset(IConfigLoader *module)
  {
    if (m_configLoader == module)
    {
      m_configLoader = nullptr;
    }
  }

  void ACore::unset(IConnection *module)
  {
    if (m_connection == module)
    {
      m_connection->enable();
      m_connection = nullptr;
    }
  }

  IModule *ACore::load(std::string const &path)
  {
    std::cout << "Debug #1" << std::endl;
    GenModule mod(path);
    std::cout << "Debug #2" << std::endl;
    auto getter = mod.getFunction<IModule *(void)>("getModule");
    std::cout << "Debug #3" << getter << std::endl;

    m_modules.emplace_back(getter());
    std::cout << "Debug #4" << std::endl;

    return m_modules.back().get();
  }

  void ACore::unload(IModule *module)
  {
    if (m_configLoader == module)
    {
      this->unset(m_configLoader);
    }

    if (m_connection == module)
    {
      this->unset(m_connection);
    }

    m_inputFilters.clear(module);
    m_requestFilters.clear(module);
    m_responseFilters.clear(module);
    m_outputFilters.clear(module);

    m_handlers.clear(module);
    m_loggers.clear(module);

    for (auto it = m_modules.begin(); it != m_modules.end();)
    {
      if (it->get() == module)
      {
        m_modules.erase(it);
      }
      else
      {
        ++it;
      }
    }
  }

  SlotRegister<IHandler *> &ACore::handlers()
  { 
    return m_handlers;
  }

  SlotRegister<ILogger *> &ACore::loggers()
  {
    return m_loggers;
  }
}