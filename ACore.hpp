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
    virtual ~ACore() noexcept {}
    virtual void set(IConfigLoader *module);
    virtual void set(IConnection *module);
    virtual void unset(IConfigLoader *module);
    virtual void unset(IConnection *module);

    template <filter::Type T>
    filter::Register<T> &get()
    {
      //static_assert(false, "This value is not a filter::Type");
    }

    virtual void run() = 0;
    virtual IModule *load(std::string const &path);
    virtual void unload(IModule *module);

    virtual SlotRegister<IHandler *> &handlers();
    virtual SlotRegister<ILogger *> &loggers();

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

  template <>
  inline filter::Register<filter::Type::InputData> &ACore::get<filter::Type::InputData>()
  {
    return m_inputFilters;
  }

  template <>
  inline filter::Register<filter::Type::Request> &ACore::get<filter::Type::Request>()
  {
    return m_requestFilters;
  }

  template <>
  inline filter::Register<filter::Type::Response> &ACore::get<filter::Type::Response>()
  {
    return m_responseFilters;
  }

  template <>
  inline filter::Register<filter::Type::OutputData> &ACore::get<filter::Type::OutputData>()
  {
    return m_outputFilters;
  }
}

#endif // !TEQUILAPI_ACORE_HPP_
