#ifndef TEQUILAPI_HTTP_IBASE_HPP_
# define TEQUILAPI_HTTP_IBASE_HPP_

# include <utility>
# include <cstdint>
# include <string>
# include <map>

namespace teq
{
  class IBase
  {
  public:
    virtual ~IBase() noexcept {}
    virtual std::pair<std::int32_t, std::int32_t> version() const = 0;
    virtual void version(std::int32_t major = 1, std::int32_t minor = 1) = 0;
    virtual std::string const &body() const = 0;
    virtual void body(std::string const &body) = 0;
    virtual std::string &operator[](std::string const &param) = 0;
    virtual std::string const &at(std::string const &param) const = 0;
    virtual std::string &at(std::string const &param) = 0;
    virtual void clearParams() = 0;
    virtual std::string toString() = 0;

    using size_type = std::map<std::string, std::string>::size_type;
    using iterator = std::map<std::string, std::string>::iterator;
    using const_iterator = std::map<std::string, std::string>::const_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    virtual size_type paramCount() const noexcept = 0;
    virtual iterator begin() noexcept = 0;
    virtual iterator end() noexcept = 0;
    virtual const_iterator begin() const noexcept = 0;
    virtual const_iterator end() const noexcept = 0;
  };
}

#endif // !TEQUILAPI_HTTP_IBASE_HPP_