#ifndef TEQUILAPI_ILOGGER_HPP_
# define TEQUILAPI_ILOGGER_HPP_

# include <string>
# include "IModule.hpp"
# include "LogType.hpp"

namespace teq
{
  class ILogger : public IModule
  {
  public:
    virtual ~ILogger() noexcept {}
    virtual void log(LogType type, std::string const &message) = 0;
  };
}

#endif // !TEQUILAPI_ILOGGER_HPP_