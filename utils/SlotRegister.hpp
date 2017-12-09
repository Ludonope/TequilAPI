#ifndef TEQUILAPI_SLOTREGISTER_HPP_
# define TEQUILAPI_SLOTREGISTER_HPP_

# include <vector>
# include <array>
# include <algorithm>
# include <exception>
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

    T &add(IModule const *parent, T const &value, Priority priority = Priority::Normal)
    {
      // Check if this item is not already in the list
      if (std::find(m_data.begin(), m_data.end(), value) != m_data.end())
      {
        throw std::invalid_argument("This element is already in this slot register");
      }

      // Get the priority real value as an int
      int priorityValue = static_cast<int>(priority);

      assert(priorityValue >= 0 && priorityValue <= 4);

      // Get the position of the item (from the end)
      // based on it's priority
      int index = 0;

      for (int i = 0; i < priorityValue; ++i)
      {
        index += m_count[i];
      }

      // Insert it at {index} from the end
      m_data.insert(m_data.begin() + (m_data.size() - index), value);
      m_parents.insert(m_parents.begin() + index, parent);
      m_count[priorityValue] += 1;

      return m_data[index];
    }

    void remove(T const &value)
    {
      auto elem = std::find(m_data.rbegin(), m_data.rend(), value);

      // Check if this item is in the list
      if (elem == m_data.rend())
      {
        throw std::invalid_argument("This element is not in this slot register");
      }

      int elemIndex = elem - m_data.rbegin();
      int elemPriority = 0;

      for (int sum = 0; elemPriority < 5; ++elemPriority)
      {
        sum += m_count[elemPriority];
        if (sum > elemIndex)
        {
          break;
        }
      }

      m_data.erase(m_data.begin() + elemIndex);
      m_parents.erase(m_parents.begin() + elemIndex);
      m_count[elemPriority] -= 1;
    }

    void clear(IModule const *module)
    {
      for (size_t i = 0; i < m_parents.size();)
      {
        if (m_parents[i] == module)
        {
          m_data.erase(m_data.begin() + i);
          m_parents.erase(m_parents.begin() + i);
        }
        else
        {
          ++i;
        }
      }
    }
  protected:
    std::vector<T> m_data;

  private:
    std::vector<IModule const *> m_parents;
    std::array<std::size_t, 5> m_count;
  };
}

#endif // !TEQUILAPI_SLOTREGISTER_HPP_