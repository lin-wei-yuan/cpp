#include <cstddef>
#include <stdexcept>
#include <cstdio>

#define _DEBUG

#if __cplusplus >= 201103L
  #define __NOEXCEPT noexcept
  #define __NULLPTR nullptr
#else
  #define __NOEXCEPT throw()
  #define __NULLPTR NULL
#endif

namespace containers {
/*!
 * @brief  Vector implementation
 * @author  boddicheg
 * @version  0.0.1
 * @warning  This class is designed for educational purposes only
 *
 * In some terminology a vector can be described as a dynamic C-style array,
 * it offers fast and efficient access to individual elements in any order
 * and saves the user from worrying about memory and size allocation.
 * Subscripting ( [] ) access is also provided as with C-style arrays.
 */
template<typename value_type>
class vec
{
public:
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;

private:
  value_type* m_arr;
  size_t m_size;
  size_t m_capacity;
  iterator m_begin;
  iterator m_end;
  /*!
   * @brief  Init iterators
   */
  void _iterators() {
    if (m_size > 0) {
      m_begin = m_arr;
      m_end = m_arr + m_size; // get element after last
    }
  }
  /*!
   * @brief Allocate memory
   * @param _n Elements in array
   */
  void _range_allocate(size_t _n) {
    size_t allocated = _n * sizeof(value_type);
    m_arr = static_cast<value_type*>(operator new[] (allocated));
  }
  /*!
   * @brief  Init element
   */
  void _node_initialize(const value_type& elem) {
    new (m_arr + m_size++) value_type(elem);
    m_capacity++;
  }
  /*!
   * @brief Free all data int @vec
   */
  void _destruct() {
    for (size_t i = 0; i < m_size; ++i) {
      m_arr[i].~value_type();
    }
    operator delete[] (m_arr);
  }
public:
  /*!
   * @brief  Default constructor creates no elements.
   */
  vec()
  : m_size(0)
  , m_capacity(0)
  , m_begin(__NULLPTR)
  , m_end(__NULLPTR)
  {
    _range_allocate(0);
  }
  /*!
   * @brief  Creates a vector with default constructed elements.
   * @param size  The number of elements to initially create.
   */
  vec(size_t size)
  : m_size(0)
  , m_capacity(0)
  , m_begin(__NULLPTR)
  , m_end(__NULLPTR)
  {
    _range_allocate(size);
    for (size_t i = 0; i < size; ++i) {
      _node_initialize(value_type());
    }
    _iterators();
  }
  /*!
   * @brief  Creates a vector with default constructed elements.
   * @param size  The number of elements to initially create.
   * @param element  An element to copy.
   */
  vec(size_t size, const value_type& element)
    : m_size(0)
    , m_capacity(0)
    , m_begin(__NULLPTR)
    , m_end(__NULLPTR)
  {
    _range_allocate(size);
    for (size_t i = 0; i < size; ++i) {
      _node_initialize(element);
    }
    _iterators();
  }

  /*!
   * @brief  Vector copy constructor.
   * @param other  A vector of identical elemen
   */
  vec(const vec<value_type>& other)
    : m_size(0)
    , m_capacity(0)
    , m_begin(__NULLPTR)
    , m_end(__NULLPTR)
   {
    _range_allocate(other.size());
    for (size_t i = 0; i < other.size(); ++i) {
      _node_initialize(other.at(i));
    }
    _iterators();
  }

  /*!
   * @brief  Builds a vec from a range.
   * @param _begin  An input iterator.
   * @param _end  An input iterator.
   */
  vec(const_iterator _begin, const_iterator _end)
    : m_size(0)
    , m_capacity(0)
    , m_begin(__NULLPTR)
    , m_end(__NULLPTR)
  {
    size_t dist = std::distance(_begin, _end);
    _range_allocate(dist);
    for (const_iterator it = _begin; it != _end; ++it) {
      _node_initialize(*it);
    }
    _iterators();
  }

  /*!
   * @brief  Dtor
   *
   * The dtor only erases the elements, and note that if the elements themselves
   * are pointers, the pointed-to memory is not touched in any way.
   * Managing the pointer is the user's responsibility.
   */
  ~vec() __NOEXCEPT {
    _destruct();
  }

  /*!
   * @brief  Returns size of vector
   */
  size_t size() const __NOEXCEPT { return m_size; }

  /*!
   * @brief  Returns current capacity
   */
  size_t capacity() const __NOEXCEPT { return m_capacity; }

  /*!
   * @brief  Returns true if size of vector > 0, overwise false
   */
  bool empty() const __NOEXCEPT { return m_size == 0; }

  /*!
   *  @brief  Returns a read/write iterator that points to the first
   *          element in the vec. Iteration is done in ordinary
   *          element order.
   */
  iterator begin() __NOEXCEPT { return m_begin; }

  /*!
   *  @brief  Returns a read/write iterator that points to the one past
   *          the last element in the vec. Iteration is done in ordinary
   *          element order.
   */
  iterator end() __NOEXCEPT { return m_end; }

  /*!
   *  @brief  Returns a read-only iterator that points to the first
   *          element in the vec. Iteration is done in ordinary
   *          element order.
   */
  const_iterator begin() const __NOEXCEPT { return m_begin; }

  /*!
   *  @brief  Returns a read-only iterator that points to the one past
   *          the last element in the vec. Iteration is done in ordinary
   *          element order.
   */
  const_iterator end() const __NOEXCEPT { return m_end;}

  /*!
   * @brief  Subscript access to the data contained in the vector.
   * @param  index Index in vector
   * @return  element
   */
  reference operator[](size_t index) __NOEXCEPT {
    return m_arr[index];
  }

  /*!
   * @brief  Read access to the data contained in vector
   * @param  index Index in vector
   * @return  element
   */
  const_reference operator[](size_t index) const __NOEXCEPT {
    return m_arr[index];
  }

  /*!
   * @brief  Full access to element in vector
   * @param  index Index in vector
   * @throw  std::out_of_range  If index >= m_size.
   * @return  element
   */
  reference at(size_t index) {
    if (index >= m_size) {
      throw std::out_of_range("vec::_M_range_check");
    }
    return m_arr[index];
  }

  /*!
   * @brief  Only read access to element in vector
   * @param  index Index in vector
   * @throw  std::out_of_range  If index >= m_size.
   * @return  element
   */
  const_reference at(size_t index) const {
    if (index >= m_size) {
      throw std::out_of_range("vec::_M_range_check");
    }
    return m_arr[index];
  }
  /*!
   *  @brief  Add data to the end of the %vec.
   *  @param  __x  Data to be added.
   *
   *  This is a typical stack operation.  The function creates an
   *  element at the end of the %vec and assigns the given data
   *  to it.  Due to the nature of a %vec this operation can be
   *  done in constant time if the %vec has preallocated space
   *  available.
   */
  void push_back(const value_type& element) {
    // space full
    if (m_size == m_capacity) {
      (m_capacity == 0) ? reserve(1) : reserve(2 * m_capacity);
    }
    m_arr[m_size++] = element;
  }

#if __cplusplus >= 201103L
  void push_back(value_type&& element) {
    // space full
    if (m_size == m_capacity) {
      (m_capacity == 0) ? reserve(1) : reserve(2 * m_capacity);
    }
    m_arr[m_size++] = std::move(element);
  }
#endif

  /*!
   * @brief  Attempt to preallocate enough memory for specified number of elements.
   * @param  capacity Number of elements required.
   * @throw  std::length_error  If n exceeds %vec max_size().
   *
   *  This function attempts to reserve enough memory for the
   *  %vector to hold the specified number of elements.  If the
   *  number requested is more than max_size(), length_error is
   *  thrown.
   */
  void reserve(size_t capacity) {
    if (m_capacity <= capacity) return;
    if (capacity >= max_size()) throw std::length_error("vec::reserve size > max_size");
    value_type *_arr = new value_type[capacity];
    for (size_t i = 0; i < m_size; ++i) {
      _arr[i] = m_arr[i];
    }
    // Remove all after copying
    delete[] m_arr;
    m_arr = _arr;
    m_capacity = capacity;
  }
  /*!
   * @brief  Returns the size of largest size of %vec
   * @return  Max %vec size
   */
  size_t max_size() const __NOEXCEPT {
    return size_t(-1) / sizeof(value_type);
  }
};
} // namespace containers
