#ifndef TEQUILAPI_IMODULE_HPP_
# define TEQUILAPI_IMODULE_HPP_

# include <string>
# include "json.hpp"

namespace teq
{
  class ACore;

  class IModule
  {
  public:
    virtual ~IModule() noexcept {}
    virtual std::string const &name() const = 0;
    virtual std::string const &description() const = 0;
    virtual void init(ACore &core, nlohmann::json const &config) = 0;
  };
}

#endif // !TEQUILAPI_IMODULE_HPP_