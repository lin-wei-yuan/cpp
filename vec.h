#include <cstddef>
#include <stdexcept>

namespace containers {
/* Vector implementation */
template<typename U>
class vec
{
  U* m_arr;
  size_t m_size;
  size_t m_capacity;
public:
  // typedef U*
  vec(size_t size, U element) {
    m_arr = new int[size];
    for (size_t i = 0; i < size; ++i) {
      m_arr[i] = element;
    }
    m_size = size;
    m_capacity = size;
  }

  vec() {
    m_arr = new int[0];
    m_size = 0;
    m_capacity = 0;
  }

  vec(size_t size) {
    m_arr = new int[size];
    for (size_t i = 0; i < size; ++i) {
      m_arr[i] = 0;
    }
    m_size = size;
    m_capacity = size;
  }

  vec(const vec<U>& other) {
    size_t size = (other.size() < other.capacity()) ? other.capacity() : other.size();
    m_arr = new int[size];
    m_size = other.size();
    m_capacity = other.capacity();
    for (size_t i = 0; i < other.size(); ++i) {
      m_arr[i] = other.at(i);
    }
    // @TODO: init iterators
  }

  ~vec() {
    delete[] m_arr;
  }

  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; }

  U& operator[](int index) noexcept {
    return m_arr[index];
  }

  U& at(int index) {
    if (index >= m_size) {
      // @TODO: fix memory leak
      throw std::out_of_range("vec::_M_range_check");
    }
    return m_arr[index];
  }
};
} // namespace containers
