#ifndef TEQUILAPI_ICONNECTION_HPP_
# define TEQUILAPI_ICONNECTION_HPP_

# include <queue>
# include "http/Message.hpp"
# include "IMainModule.hpp"

namespace teq
{
  class IConnection : public IMainModule
  {
  public:
    virtual ~IConnection() noexcept {}
    virtual void setInput(std::queue<http::Message> &queue) = 0;
    virtual void setOutput(std::queue<http::Message> &queue) = 0;
  };
}

#endif // !TEQUILAPI_ICONNECTION_HPP_