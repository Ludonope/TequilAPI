#ifndef TEQUILAPI_IFILTER_HPP_
# define TEQUILAPI_IFILTER_HPP_

# include "IModule.hpp"

namespace teq
{
  class IFilter : public IModule
  {
  public:
    virtual ~IFilter() noexcept {}
  };
}

#endif // !TEQUILAPI_IFILTER_HPP_