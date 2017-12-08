#ifndef TEQUILAPI_HTTP_URI_HPP_
# define TEQUILAPI_HTTP_URI_HPP_

# include <string>
# include <map>

namespace teq
{
  namespace http
  {
    class Uri final : public std::map<std::string, std::string>
    {
    public:
      Uri();
      Uri(Uri const &that);
      Uri(Uri &&that);
      Uri(std::string const &path);
      Uri(std::string const &path, std::initializer_list<std::pair<std::string, std::string>> params);
      Uri(std::initializer_list<std::pair<std::string, std::string>> params);
      ~Uri() noexcept;

      Uri &operator=(Uri const &that);
      Uri &operator=(Uri &&that);

      std::string const &path() const;
      void path(std::string const &path);

      bool hasParam(std::string const &param) const;

      std::string toString() const;

    private:
      std::string m_path;
      std::map<std::string, std::string> &m_params;
    };
  }
}

std::ostream &operator<<(std::ostream &os, teq::http::Uri const &uri);

#endif // !TEQUILAPI_HTTP_URI_HPP_