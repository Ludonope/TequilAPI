#include "ACore.hpp"

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
    m_connection->start();
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
      m_connection->stop();
      m_connection = nullptr;
    }
  }
}