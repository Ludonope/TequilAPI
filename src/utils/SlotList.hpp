#ifndef TEQUILAPI_SLOTLIST_HPP_
# define TEQUILAPI_SLOTLIST_HPP_

# include "SlotRegister.hpp"

namespace teq
{
  template <typename T>
  class SlotList final : public SlotRegister<T>
  {
  public:
    using SlotRegister<T>::m_data;
    
    SlotList() = default;
    SlotList(SlotList const &that) = default;
    SlotList(SlotList &&that) = default;
    virtual ~SlotList() noexcept = default;

    SlotList &operator=(SlotList const &that) = default;
    SlotList &operator=(SlotList &&that) = default;

    using size_type = typename std::vector<T>::size_type;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    size_type size() const noexcept
    {
      return m_data.size();
    }

    bool empty() const noexcept
    {
      return m_data.size() == 0;
    }

    T const &operator[](size_type index) const
    {
      return m_data[index];
    }

    T &operator[](size_type index)
    {
      return m_data[index];
    }

    iterator begin() noexcept
    {
      return m_data.begin();
    }

    iterator end() noexcept
    {
      return m_data.end();
    }

    const_iterator begin() const noexcept
    {
      return m_data.begin();
    }

    const_iterator end() const noexcept
    {
      return m_data.end();
    }
  };
}

#endif // !TEQUILAPI_SLOTLIST_HPP_