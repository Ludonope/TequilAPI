#ifndef TEQUILAPI_HTTP_IREQUEST_HPP_
# define TEQUILAPI_HTTP_IREQUEST_HPP_

# include "IBase.hpp"
# include "Method.hpp"
# include "Uri.hpp"

namespace teq
{
  namespace http
  {
    class IRequest : public IBase
    {
    public:
      virtual ~IRequest() noexcept {}
      virtual Method method() const = 0;
      virtual void method(Method method) = 0;
      virtual Uri const &uri() const = 0;
      virtual void uri(Uri const &uri) = 0;
    };
  }
}

#endif // !TEQUILAPI_HTTP_IREQUEST_HPP_