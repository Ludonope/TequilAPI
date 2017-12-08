#ifndef TEQUILAPI_HTTP_URI_HPP_
# define TEQUILAPI_HTTP_URI_HPP_

# include <string>
# include <map>

namespace teq
{
  namespace http
  {
    class Uri final
    {
    public:
      Uri() = default;
      Uri(Uri const &that) = default;
      Uri(Uri &&that) = default;
      Uri(std::string const &path);
      Uri(std::string const &path, std::initializer_list<std::pair<std::string, std::string>> params);
      Uri(std::initializer_list<std::pair<std::string, std::string>> params);
      ~Uri() noexcept = default;

      Uri &operator=(Uri const &that) = default;
      Uri &operator=(Uri &&that) = default;

      std::string const &path() const;
      void path(std::string const &path);

      std::string &operator[](std::string const &param);
      std::string const &at(std::string const &param) const;
      std::string &at(std::string const &param);

      bool hasParam(std::string const &param) const;

      std::string toString() const;

    private:
      std::string m_path;
      std::map<std::string, std::string> m_params;
    };
  }
}

std::ostream &operator<<(std::ostream &os, teq::http::Uri const &uri);

#endif // !TEQUILAPI_HTTP_URI_HPP_