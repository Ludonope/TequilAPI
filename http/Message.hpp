#ifndef TEQUILAPI_MESSAGE_HPP_
# define TEQUILAPI_MESSAGE_HPP_

# include <string>

namespace teq
{
  namespace http
  {
    struct Message
    {
      std::string id;
      std::string content;
    };
  }
}

#endif // !TEQUILAPI_MESSAGE_HPP_