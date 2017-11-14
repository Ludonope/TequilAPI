#ifndef TEQUILAPI_IJSONOBJECT_HPP_
# define TEQUILAPI_IJSONOBJECT_HPP_

namespace teq
{
  class IJSONObject
  {
    public:
      virtual IJSONObject const &operator[](std::string const &) const = 0;
  };
}

#endif // !TEQUILAPI_IJSONOBJECT_HPP_