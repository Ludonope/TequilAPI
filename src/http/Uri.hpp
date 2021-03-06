#ifndef TEQUILAPI_HTTP_URI_HPP_
# define TEQUILAPI_HTTP_URI_HPP_

# include <string>
# include <vector>
# include <map>

namespace teq
{
  namespace http
  {
    class Uri final : public std::map<std::string, std::vector<std::string>>
    {
    public:
      Uri();
      Uri(Uri const &that);
      Uri(Uri &&that);
      Uri(std::string const &path);
      virtual ~Uri() noexcept = default;

      Uri &operator=(Uri const &that);
      Uri &operator=(Uri &&that);

      std::string const &path() const;
      void setPath(std::string const &path);

      bool hasParam(std::string const &param) const;

      std::string toString() const;

    private:
      using params_t = std::map<std::string, std::vector<std::string>>;
      std::string m_path;
      params_t &m_params;
    };
  }
}

std::ostream &operator<<(std::ostream &os, teq::http::Uri const &uri);

#endif // !TEQUILAPI_HTTP_URI_HPP_