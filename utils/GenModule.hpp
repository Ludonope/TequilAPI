#ifndef TEQUILAPI_GENMODULE_HPP_
# define TEQUILAPI_GENMODULE_HPP_

# if defined(__linux__) || (__APPLE__)
#  include <dlfcn.h>
# elif defined(_WIN32)
#  include <Windows.h>
# endif

# include <string>
# include <functional>

namespace teq
{
// Uniform type declaration
# if defined(__linux__) || (__APPLE__)
    using gen_mod_t = void *;
# elif defined(_WIN32)
    using gen_mod_t = HINSTANCE;
# else
# error "Unsupported dynamic library format"
# endif

  namespace detail
  {
    template <typename R, typename ... Args>
    using fptr_t = R(*)(Args...);

    template <typename T>
    struct impl
    {
      static void getFunction(std::string const &sym, gen_mod_t const modPtr);
    };

    // Allows someone to load a function form a .so or .dll
    template <typename R, typename ... Args>
    struct impl<R(Args...)>
    {
      static fptr_t<R, Args...> getFunction(std::string const &sym, gen_mod_t const modPtr)
      {
        std::cout << "modPtr: " << modPtr << std::endl;
  # if defined(__linux__) || (__APPLE__)
        fptr_t<R, Args...> func =
            reinterpret_cast<fptr_t<R, Args...>>(dlsym(modPtr, sym.c_str()));
  # elif defined(_WIN32)
        fptr_t<R, Args...> func =
            reinterpret_cast<fptr_t<R, Args...>>(GetProcAddress(modPtr, sym.c_str()));
  # endif
        std::cout << "fptr: " << func << std::endl;
        return func;
      }
    };

  }

  class GenModule
  {
  public:
    GenModule() = delete;
    GenModule(std::string const &filename);
    GenModule(GenModule const &that);
    GenModule(GenModule &&that);
    ~GenModule() noexcept;

    GenModule &operator=(GenModule const &);
    GenModule &operator=(GenModule &&);

  public:
    template <typename T>
    auto getFunction(std::string const &sym) const
    {
      return detail::impl<T>::getFunction(sym, m_modPtr);
    }

  private:
    void load(std::string const &filename);
    void unload();

    std::string m_filename;
    gen_mod_t   m_modPtr;
  };
}

#endif // !TEQUILAPI_GENMODULE_HPP_