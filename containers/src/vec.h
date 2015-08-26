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
     @brief Vector implementation
     @author boddicheg
     @version 0.0.1
     @warning This class is designed for educational purposes only

      In some terminology a vector can be described as a dynamic C-style array,
      it offers fast and efficient access to individual elements in any order
      and saves the user from worrying about memory and size allocation.
      Subscripting ( [] ) access is also provided as with C-style arrays.
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
   * @brief init iterators
   */
  void _iterators() {
    if (m_size > 0) {
      m_begin = m_arr;
      m_end = m_arr + m_size; // get element after last
    }
  }

public:
  /*!
   * @brief Default constructor creates no elements.
   */
  vec()
  : m_size(0)
  , m_capacity(0)
  , m_begin(__NULLPTR)
  , m_end(__NULLPTR)
  {
    m_arr = new value_type[m_size];
  }

  /*!
   * @brief Creates a vector with default constructed elements.
   * @param[in] size The number of elements to initially create.
   */
  vec(size_t size)
  : m_size(size)
  , m_capacity(size)
  , m_begin(__NULLPTR)
  , m_end(__NULLPTR)
  {
    m_arr = new value_type[size];
    for (size_t i = 0; i < size; ++i) {
      // @TODO: fix this
      m_arr[i] = value_type();
    }
    _iterators();
  }

public:
  /*!
   * @brief Creates a vector with default constructed elements.
   * @param[in] size The number of elements to initially create.
   * @param[in] element An element to copy.
   */
  vec(size_t size, const value_type& element)
#if __cplusplus >= 201103L
    : vec(size)
#else
    : m_size(size)
    , m_capacity(size)
    , m_begin(__NULLPTR)
    , m_end(__NULLPTR)
#endif
  {
    m_arr = new value_type[size];
    for (size_t i = 0; i < size; ++i) {
      m_arr[i] = element;
    }
    _iterators();
  }

  /*!
   * @brief Vector copy constructor.
   * @param[in] other A vector of identical elemen
   */
  vec(const vec<value_type>& other)
#if __cplusplus >= 201103L
    : vec()
#else
    : m_size(0)
    , m_capacity(0)
    , m_begin(__NULLPTR)
    , m_end(__NULLPTR)
#endif
   {
    size_t size = (other.size() < other.capacity()) ? other.capacity() : other.size();
    m_arr = new value_type[size];
    m_size = other.size();
    m_capacity = other.capacity();
    for (size_t i = 0; i < other.size(); ++i) {
      m_arr[i] = other.at(i);
    }
    _iterators();
  }

  /*!
   * @brief Builds a vec from a range.
   * @param[in] _begin An input iterator.
   * @param[in] _end An input iterator.
   */
  vec(const_iterator _begin, const_iterator _end)
#if __cplusplus >= 201103L
    : vec()
#else
    : m_size(0)
    , m_capacity(0)
    , m_begin(__NULLPTR)
    , m_end(__NULLPTR)
#endif
  {
    size_t dist = std::distance(_begin, _end);
    m_arr = new value_type[dist];
    for (const_iterator it = _begin; it != _end; ++it) {
      m_arr[m_size++] = *it;
    }
    m_size = dist;
    m_capacity = dist;
    _iterators();
  }

  /*!
   * @brief Dtor
   *
   * The dtor only erases the elements, and note that if the elements themselves
   * are pointers, the pointed-to memory is not touched in any way.
   * Managing the pointer is the user's responsibility.
   */
  ~vec() __NOEXCEPT {
    #ifdef _DEBUG
      printf("vec::~vec called \n");
    #endif
    // @TODO: fix
    delete[] m_arr;
  }

  /*!
   * @brief Returns size of vector
   */
  size_t size() const __NOEXCEPT { return m_size; }

  /*!
   * @brief Returns current capacity
   */
  size_t capacity() const __NOEXCEPT { return m_capacity; }

  /*!
   * @brief Returns true if size of vector > 0, overwise false
   */
  bool empty() const __NOEXCEPT { return m_size == 0; }

  /*!
   *  @brief Returns a read/write iterator that points to the first
   *  element in the vec. Iteration is done in ordinary
   *  element order.
   */
  iterator begin() __NOEXCEPT { return m_begin; }

  /*!
   *  @brief Returns a read/write iterator that points to the one past
   *  the last element in the vec. Iteration is done in ordinary
   *  element order.
   */
  iterator end() __NOEXCEPT { return m_end; }

  /*!
   *  @brief Returns a read-only iterator that points to the first
   *  element in the vec. Iteration is done in ordinary
   *  element order.
   */
  const_iterator begin() const __NOEXCEPT { return m_begin; }

  /*!
   *  @brief Returns a read-only iterator that points to the one past
   *  the last element in the vec. Iteration is done in ordinary
   *  element order.
   */
  const_iterator end() const __NOEXCEPT { return m_end;}

  /*!
   * @brief Subscript access to the data contained in the vector.
   *        No index check
   * @param  index Index in vector
   * @return       Element
   */
  reference operator[](int index) __NOEXCEPT {
    return m_arr[index];
  }

  /*!
   * @brief Read access to the data contained in vector
   *        No index check
   * @param  index Index in vector
   * @return       Element
   */
  const_reference operator[](int index) const __NOEXCEPT {
    return m_arr[index];
  }

  /*!
   * @brief Full access to element in vector
   *        Generate out_of_range id index >= size
   * @param  index Index in vector
   * @return       Element
   */
  reference at(int index) {
    if (index >= m_size) {
      throw std::out_of_range("vec::_M_range_check");
    }
    return m_arr[index];
  }

  /*!
   * @brief Only read access to element in vector
   *        Generate out_of_range id index >= size
   * @param  index Index in vector
   * @return       Element
   */
  const_reference at(int index) const {
    if (index >= m_size) {
      throw std::out_of_range("vec::_M_range_check");
    }
    return m_arr[index];
  }
  /**
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
    // @TODO: ...
  }
};
} // namespace containers
