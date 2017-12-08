#ifndef TEQUILAPI_IHANDLER_HPP_
# define TEQUILAPI_IHANDLER_HPP_

# include "IModule.hpp"
# include "http/IRequest.hpp"
# include "http/IResponse.hpp"

namespace teq
{
  class IHandler : public IModule
  {
  public:
    virtual ~IHandler() noexcept {}
    virtual bool handle(http::IRequest &req, http::IResponse &res) = 0;
  };
}

#endif // !TEQUILAPI_IHANDLER_HPP_