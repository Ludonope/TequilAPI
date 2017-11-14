#ifndef TEQUILAPI_CORE_HPP_
# define TEQUILAPI_CORE_HPP_

# include <string>
# include <vector>
# include <memory>
# include "IConfig.hpp"

namespace teq
{
  class AModule;
  class IGui;

  class ACore
  {
    public:
      virtual void loadModule(std::string const &module) = 0;
      virtual void unloadModule(std::string const &module) = 0;

      IConfig const &getConfig() const;
      IConfig &getConfig();

      virtual void loadGUI(std::string const &gui) = 0;
      virtual void unloadGUI() = 0;

      virtual std::vector<std::unique_ptr<AModule>> const &getAllModules() const = 0;
      virtual std::vector<std::unique_ptr<AModule>> &getAllModules() = 0;

      virtual std::vector<AModule const *> getInputModulesOf(std::string const &name) = 0;

    protected:
      std::vector<std::unique_ptr<AModule>> m_modules;
      std::unique_ptr<IConfig> m_config;
      std::unique_ptr<IGui> m_gui;
  };
}

#endif // !TEQUILAPI_CORE_HPP_
