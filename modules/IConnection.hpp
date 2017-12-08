#ifndef TEQUILAPI_ICONNECTION_HPP_
# define TEQUILAPI_ICONNECTION_HPP_

# include "IModule.hpp"

namespace teq
{
  class IConnection : public IModule
  {
  public:
    virtual ~IConnection() noexcept {}
    // TODO: connection need to fill a queue or something
    virtual void start() = 0;
    virtual void stop() = 0;
  };
}

#endif // !TEQUILAPI_ICONNECTION_HPP_