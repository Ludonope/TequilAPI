#ifndef TEQUILAPI_SLOTLIST_HPP_
# define TEQUILAPI_SLOTLIST_HPP_

# include "SlotRegister.hpp"

namespace teq
{
  template <typename T>
  class SlotList final : public SlotRegister<T>
  {
  public:
    SlotList() = default;
    SlotList(SlotList const &that) = default;
    SlotList(SlotList &&that) = default;
    virtual ~SlotList() noexcept = default;

    SlotList &operator=(SlotList const &that) = default;
    SlotList &operator=(SlotList &&that) = default;

    using size_type = decltype(m_data)::size_type;
    using iterator = decltype(m_data)::iterator;
    using const_iterator = decltype(m_data)::const_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    size_type size() const noexcept;
    bool empty() const noexcept;
    T const &operator[](size_type index) const;
    T &operator[](size_type index);
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
  };
}

#endif // !TEQUILAPI_SLOTLIST_HPP_