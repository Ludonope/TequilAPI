#ifndef TEQUILAPI_FILTER_HPP_
# define TEQUILAPI_FILTER_HPP_

# include <function>

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
      template <typename T>
      struct Corresponding
      {
        static_assert(false, "This value is not a filter::Type");
      };

      template <typename T>
      struct Corresponding<Type::InputData>
      {
        using Type = std::function<void(std::string &)>;
      };

      template <typename T>
      struct Corresponding<Type::Request>
      {
        using Type = std::function<void(http::IRequest &)>;
      };

      template <typename T>
      struct Corresponding<Type::Response>
      {
        using Type = std::function<void(http::IResponse &)>;
      };

      template <typename T>
      struct Corresponding<Type::OutputData>
      {
        using Type = std::function<void(std::string &)>;
      };
    }

    template <Type T>
    using Register = SlotRegister<Corresponding<T>::Type>;

    template <Type T>
    using List = SlotList<Corresponding<T>::Type>;
  }
}

#endif // !TEQUILAPI_FILTER_HPP_