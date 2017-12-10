#ifndef TEQUILAPI_IMAINMODULE_HPP_
# define TEQUILAPI_IMAINMODULE_HPP_

# include "IModule.hpp"

namespace teq
{
  class IMainModule : public IModule
  {
  public:
    virtual ~IMainModule() noexcept {}
    virtual void enable() = 0;
    virtual void disable() = 0;
  };
}

#endif // !TEQUILAPI_IMAINMODULE_HPP_