#include "Uri.hpp"

namespace teq
{
  namespace http
  {
    Uri::Uri() :
      m_path(""),
      m_params(*this)
    {
    }

    Uri::Uri(Uri const &that) :
      std::map<std::string, std::vector<std::string>>(that),
      m_path(that.m_path),
      m_params(*this)
    {
    }

    Uri::Uri(Uri &&that) :
      std::map<std::string, std::vector<std::string>>(std::move(that)),
      m_path(std::move(that.m_path)),
      m_params(*this)
    {
    }

    Uri::Uri(std::string const &path) :
      m_path(path),
      m_params(*this)
    {
    }

    Uri &Uri::operator=(Uri const &that)
    {
      if (this == &that)
        return *this;
      m_path = that.m_path;
      m_params = that.m_params;
      return *this;
    }

    Uri &Uri::operator=(Uri &&that)
    {
      if (this == &that)
        return *this;
      m_path = std::move(that.m_path);
      m_params = std::move(that.m_params);
      return *this;
    }

    std::string const &Uri::path() const
    {
      return m_path;
    }

    void Uri::setPath(std::string const &path)
    {
      m_path = path;
    }

    bool Uri::hasParam(std::string const &param) const
    {
      return m_params.find(param) != m_params.end();
    }

    std::string Uri::toString() const
    {
      std::string res = m_path;
      bool first = true;

      for (auto const &param : m_params)
      {
        for (auto const &val : param.second)
        {
          if (first)
          {
            res += '?';
            first = false;
          }
          else
          {
            res += '&';
          }

          res += param.first + '=' + val;
        }
      }

      return res;
    }
  }
}

std::ostream &operator<<(std::ostream &os, teq::http::Uri const &uri)
{
  os << uri.toString();
  return os;
}