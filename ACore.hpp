#ifndef TEQUILAPI_ACORE_HPP_
# define TEQUILAPI_ACORE_HPP_

# include <vector>
# include <memory>
# include "modules/IConfigLoader.hpp"
# include "modules/IConnection.hpp"
# include "Filter.hpp"
# include "utils/SlotList.hpp"
# include "json.hpp"
# include "modules/IHandler.hpp"
# include "modules/ILogger.hpp"

namespace teq
{
  class ACore
  {
  public:
    virtual void set(IConfigLoader *module);
    virtual void set(IConnection *module);
    virtual void unset(IConfigLoader *module);
    virtual void unset(IConnection *module);

    template <filter::Type T>
    filter::Register<T> &get<T>()
    {
      static_assert(false, "This value is not a filter::Type");
    }

    template <>
    filter::Register<filter::Type::InputData> &get()
    {
      return m_inputFilters;
    }

    template <>
    filter::Register<filter::Type::Request> &get()
    {
      return m_requestFilters;
    }

    template <>
    filter::Register<filter::Type::Response> &get()
    {
      return m_responseFilters;
    }

    template <>
    filter::Register<filter::Type::OutputData> &get()
    {
      return m_outputFilters;
    }

  protected:
    // List of every loaded modules
    std::vector<std::unique_ptr<IModule>> m_modules;

    // Main modules
    IConfigLoader *m_configLoader;
    IConnection *m_connection;

    // Filter lists
    filter::List<filter::Type::InputData> m_inputFilters;
    filter::List<filter::Type::Request> m_requestFilters;
    filter::List<filter::Type::Response> m_responseFilters;
    filter::List<filter::Type::OutputData> m_outputFilters;

    SlotList<IHandler *> m_handlers;
    SlotList<ILogger *> m_loggers;

    nlohmann::json m_config;
  };
}

#endif // !TEQUILAPI_ACORE_HPP_
