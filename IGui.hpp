#ifndef TEQUILAPI_IGUI_HPP_
# define TEQUILAPI_IGUI_HPP_

namespace teq
{
  class ACore;

  class IGui
  {
    public:
      virtual void run(ACore *) = 0;
  };
}

#endif // !TEQUILAPI_IGUI_HPP_
