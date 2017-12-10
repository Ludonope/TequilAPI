#include <iostream>
#include "ACore.hpp"
#include "utils/GenModule.hpp"

namespace teq
{
  void ACore::setConfigLoader(IConfigLoader *module)
  {
    if (m_configLoader)
    {
      this->unsetConfigLoader(m_configLoader);
    }
    m_configLoader = module;
  }

  void ACore::setConnection(IConnection *module)
  {
    if (m_connection)
    {
      this->unsetConnection(m_connection);
    }
    m_connection = module;
    m_connection->enable();
  }

  void ACore::unsetConfigLoader(IConfigLoader *module)
  {
    if (m_configLoader == module)
    {
      m_configLoader = nullptr;
    }
  }

  void ACore::unsetConnection(IConnection *module)
  {
    if (m_connection == module)
    {
      m_connection->enable();
      m_connection = nullptr;
    }
  }

  IModule *ACore::load(std::string const &path)
  {
    auto mod = std::make_unique<GenModule>(path);
    auto getter = mod->getFunction<IModule *(void)>("getModule");
    auto module = std::unique_ptr<IModule>(getter());

    m_modules.emplace_back(std::move(mod), std::move(module));

    IModule *ptr = m_modules.back().second.get();

    ptr->init(*this, m_config);

    return ptr;
  }

  void ACore::unload(IModule *module)
  {
    if (m_configLoader == module)
    {
      this->unsetConfigLoader(m_configLoader);
    }

    if (m_connection == module)
    {
      this->unsetConnection(m_connection);
    }

    m_inputFilters.clear(module);
    m_requestFilters.clear(module);
    m_responseFilters.clear(module);
    m_outputFilters.clear(module);

    m_handlers.clear(module);
    m_loggers.clear(module);

    for (auto it = m_modules.begin(); it != m_modules.end();)
    {
      if (it->second.get() == module)
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

  void ACore::log(LogType type, std::string const &message)
  {
    for (auto logger : m_loggers)
    {
      logger->log(type, message);
    }
  }
}