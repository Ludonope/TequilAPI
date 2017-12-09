#ifndef TESTMODULE_HPP_
# define TESTMODULE_HPP_

# include "modules/ILogger.hpp"

class TestModule : public teq::ILogger
{
public:
  virtual ~TestModule() noexcept {}
  virtual std::string const &name() const;
  virtual std::string const &description() const;
  virtual void init(teq::ACore &core, nlohmann::json const &config);
  virtual void log(teq::LogType type, std::string const &message);
private:
  std::string m_name;
  std::string m_desc;
};

#endif // !TESTMODULE_HPP_