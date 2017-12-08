#ifndef TEQUILAPI_SLOTREGISTER_HPP_
# define TEQUILAPI_SLOTREGISTER_HPP_

# include <vector>
# include <array>
# include "Priority.hpp"

namespace teq
{
  template <typename T>
  class SlotRegister
  {
  public:
    SlotRegister() = default;
    SlotRegister(SlotRegister const &that) = default;
    SlotRegister(SlotRegister &&that) = default;
    virtual ~SlotRegister() noexcept = default;

    SlotRegister &operator=(SlotRegister const &that) = default;
    SlotRegister &operator=(SlotRegister &&that) = default;

    T &add(T const &value, Priority priority = Priority::Normal);
    void remove(T const &value);
  protected:
    std::vector<T> m_data;

  private:
    std::array<std::size_t, 5> m_count;
  };
}

#endif // !TEQUILAPI_SLOTREGISTER_HPP_