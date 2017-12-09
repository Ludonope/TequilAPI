#ifndef TEQUILAPI_HTTP_METHOD_HPP_
# define TEQUILAPI_HTTP_METHOD_HPP_

namespace teq
{
  namespace http
  {
    enum class Method
    {
      GET,
      HEAD,
      POST,
      PUT,
      DELETE,
      CONNECT,
      OPTIONS,
      TRACE
    };
  }
}

#endif // !TEQUILAPI_HTTP_METHOD_HPP_