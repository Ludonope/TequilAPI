#ifndef TEQUILAPI_AMODULE_HPP_
# define TEQUILAPI_AMODULE_HPP_

# include <string>
# include <vector>
# include "ModuleType.hpp"

namespace teq
{
  class ACore;
  
  class AModule
  {
    public:
      std::string const &getName() const;
      std::string const &getId() const;
      ModuleType getType() const;

      void run(ACore const *);
      void setRun(bool running);

      void setOutput(AModule const *output);
      std::vector<AModule const *> const &getOutputList() const;
      void removeOutput(AModule const *output);
      bool hasOutput(AModule const *) const;

    protected:
  };
}

#endif // !TEQUILAPI_AMODULE_HPP_
