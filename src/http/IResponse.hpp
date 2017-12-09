#ifndef TEQUILAPI_HTTP_IRESPONSE_HPP_
# define TEQUILAPI_HTTP_IRESPONSE_HPP_

# include <string>
# include "IBase.hpp"
# include "StatusCode.hpp"

namespace teq
{
  namespace http
  {
    class IResponse : public IBase
    {
    public:
      virtual ~IResponse() noexcept {}
      virtual StatusCode status() const = 0;
      virtual void status(StatusCode status) = 0;
      virtual std::string const &reason() const = 0;
      virtual void reason(std::string const &reason) = 0;
    };
  }
}

#endif // !TEQUILAPI_HTTP_IRESPONSE_HPP_