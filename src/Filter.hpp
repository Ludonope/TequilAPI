#ifndef TEQUILAPI_FILTER_HPP_
# define TEQUILAPI_FILTER_HPP_

# include <functional>
# include "utils/SlotRegister.hpp"
# include "utils/SlotList.hpp"
# include "http/IRequest.hpp"
# include "http/IResponse.hpp"

namespace teq
{
  namespace filter
  {
    enum class Type
    {
      InputData,
      Request,
      Response,
      OutputData
    };

    template <Type T>
    struct Corresponding
    {
    };

    template <>
    struct Corresponding<Type::InputData>
    {
      using Type = std::function<void(std::string &)>;
    };

    template <>
    struct Corresponding<Type::Request>
    {
      using Type = std::function<void(http::IRequest &)>;
    };

    template <>
    struct Corresponding<Type::Response>
    {
      using Type = std::function<void(http::IResponse &)>;
    };

    template <>
    struct Corresponding<Type::OutputData>
    {
      using Type = std::function<void(std::string &)>;
    };

    template <Type T>
    using Register = SlotRegister<typename Corresponding<T>::Type>;

    template <Type T>
    using List = SlotList<typename Corresponding<T>::Type>;
  }
}

#endif // !TEQUILAPI_FILTER_HPP_