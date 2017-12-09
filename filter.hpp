#ifndef TEQUILAPI_FILTER_HPP_
# define TEQUILAPI_FILTER_HPP_

# include <functional>
# include "utils/SlotRegister.hpp"
# include "utils/SlotList.hpp"

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

    namespace {
      template <Type T>
      struct Corresponding
      {
        static_assert(false, "This value is not a filter::Type");
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
    }

    template <Type T>
    using Register<T> = SlotRegister<Corresponding<T>::Type>;

    template <Type T>
    using List<T> = SlotList<Corresponding<T>::Type>;
  }
}

#endif // !TEQUILAPI_FILTER_HPP_