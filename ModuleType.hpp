#ifndef TEQUILAPI_MODULETYPE_HPP_
# define TEQUILAPI_MODULETYPE_HPP_

namespace teq
{
  enum class ModuleType
  {
    Route,
    Executor,
    Connection,
    Logger,
    Dispatcher,
    LogModifier,
    RequestModifier,
    ResponseModifier
  };
}

#endif // !TEQUILAPI_MODULETYPE_HPP_