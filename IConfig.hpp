#ifndef TEQUILAPI_CONFIG_HPP_
# define TEQUILAPI_CONFIG_HPP_

# include <string>
# include "IJsonObject.hpp"

namespace teq
{
  class IConfig
  {
    public:
      virtual void loadConfig(std::string const &filename = "zia_config.json") = 0;
      virtual void loadModuleConfig(std::string const &module) = 0;
      virtual void unloadModuleConfig(std::string const &module) = 0;

      virtual IJSONObject const &json() const = 0;
      virtual IJSONObject &json() = 0;
  };
}

#endif // !TEQUILAPI_CONFIG_HPP_