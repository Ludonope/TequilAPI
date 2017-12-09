#include <iostream>
#include <sstream>
#include "GenModule.hpp"

namespace teq
{
  GenModule::GenModule(std::string const &filename)
      : m_filename(filename), m_modPtr(nullptr)
  {
    this->load(filename);
  }

  GenModule::GenModule(GenModule const &that) :
      m_filename(that.m_filename), m_modPtr(nullptr)
  {
    this->load(m_filename);
  }

  GenModule::GenModule(GenModule &&that) :
      m_filename(that.m_filename), m_modPtr(that.m_modPtr)
  {
    that.m_modPtr = nullptr;
  }

  GenModule::~GenModule() noexcept
  {
    this->unload();
  }

  GenModule &GenModule::operator=(GenModule const &that)
  {
    if (this != &that)
      {
      	m_filename = that.m_filename;
        this->unload();
        this->load(m_filename);
      }
    return *this;
  }

  GenModule &GenModule::operator=(GenModule &&that)
  {
    if (this != &that)
      {
      	m_filename = that.m_filename;
	      m_modPtr = that.m_modPtr;
	      that.m_modPtr = nullptr;
      }
    return *this;
  }


  void GenModule::load(std::string const &filename)
  {
    m_filename = filename;
#if defined(__linux__) || (__APPLE__)
    m_modPtr = dlopen(m_filename.c_str(), RTLD_NOW | RTLD_GLOBAL);
    if (!m_modPtr)
      {
      	throw std::runtime_error("Cannot load '" + m_filename +
	                               "' ! Error : " + dlerror());
      }
#elif defined(_WIN32)
    m_modPtr = LoadLibraryA(m_filename.c_str());
    if (!m_modPtr)
      {
        std::stringstream ss;

        ss << "Cannot load '" << m_filename
          << "' ! Error : " << GetLastError();
        throw std::runtime_error(ss.str());
      }
#endif
  }

  void GenModule::unload()
  {
    if (m_modPtr)
      {
#if defined(__linux__) || (__APPLE__)
      	dlclose(m_modPtr);
#elif defined(_WIN32)
      	FreeLibrary(m_modPtr);
#endif
      	m_modPtr = nullptr;
      }    
  }
}
