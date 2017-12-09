#ifndef TEQUILAPI_ICONFIGLOADER_HPP_
# define TEQUILAPI_ICONFIGLOADER_HPP_

# include <string>
# include "json.hpp"
# include "IMainModule.hpp"

namespace teq
{
  class IConfigLoader : public IMainModule
  {
  public:
    virtual ~IConfigLoader() noexcept {}
    virtual void load(std::string const &path, nlohmann::json &config) = 0;
  };
}

#endif // !TEQUILAPI_ICONFIGLOADER_HPP_