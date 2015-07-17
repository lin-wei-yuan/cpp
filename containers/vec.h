#include <cstddef>
#include <stdexcept>

namespace containers {

/*!
     \brief Vector implementation
     \author boddicheg
     \version 0.0.1
     \warning This class is designed for educational purposes only

      In some terminology a vector can be described as a dynamic C-style array,
      it offers fast and efficient access to individual elements in any order
      and saves the user from worrying about memory and size allocation.
      Subscripting ( [] ) access is also provided as with C-style arrays.
 */
template<typename value_type>
class vec
{
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;

private:
  value_type* m_arr;
  size_t m_size;
  size_t m_capacity;

public:
  /*!
   * Creates a vector with default constructed elements.
   * \param[in] size The number of elements to initially create.
   * \param[in] element An element to copy.
   */
  vec(size_t size, value_type element) {
    m_arr = new int[size];
    for (size_t i = 0; i < size; ++i) {
      m_arr[i] = element;
    }
    m_size = size;
    m_capacity = size;
  }
  // Default constructor creates no elements.
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

  vec(const vec<value_type>& other) {
    size_t size = (other.size() < other.capacity()) ? other.capacity() : other.size();
    m_arr = new int[size];
    m_size = other.size();
    m_capacity = other.capacity();
    for (size_t i = 0; i < other.size(); ++i) {
      // @TODO: fix
      m_arr[i] = other[i];
    }
    // @TODO: init iterators
  }

  ~vec() {
    delete[] m_arr;
  }

  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; }

  value_type& operator[](int index) noexcept {
    return m_arr[index];
  }

  value_type& operator[](int index) const noexcept {
    return m_arr[index];
  }

  value_type& at(int index) {
    if (index >= m_size) {
      // @TODO: fix memory leak
      throw std::out_of_range("vec::_M_range_check");
    }
    return m_arr[index];
  }
};
} // namespace containers
