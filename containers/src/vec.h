#include <cstddef>
#include <stdexcept>

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
  // @TODO: For fix memory leak, if exception caused
  class _array {
    _array() { }
    ~_array() { }
  };

public:
  /*!
   * @brief Default constructor creates no elements.
   */
  vec()
  : m_size(0)
  , m_capacity(0)
  , m_begin(nullptr)
  , m_end(nullptr)
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
  , m_begin(nullptr)
  , m_end(nullptr)
  {
    m_arr = new value_type[size];
    for (size_t i = 0; i < size; ++i) {
      m_arr[i] = 0;
    }
    if (size > 0) {
      /* code */
      m_begin = m_arr[0];
    }
  }
  /*!
   * @brief Creates a vector with default constructed elements.
   * @param[in] size The number of elements to initially create.
   * @param[in] element An element to copy.
   */
  vec(size_t size, const value_type& element)
    : m_size(size)
    , m_capacity(size)
  {
    m_arr = new value_type[size];
    for (size_t i = 0; i < size; ++i) {
      m_arr[i] = element;
    }
  }
  /*!
   * @brief Vector copy constructor.
   * @param[in] other A vector of identical elemen
   */
  vec(const vec<value_type>& other) {
    size_t size = (other.size() < other.capacity()) ? other.capacity() : other.size();
    m_arr = new value_type[size];
    m_size = other.size();
    m_capacity = other.capacity();
    for (size_t i = 0; i < other.size(); ++i) {
      m_arr[i] = other.at(i);
    }
    // @TODO: init iterators
  }

  /*!
   * @brief Dtor
   *
   * The dtor only erases the elements, and note that if the elements themselves
   * are pointers, the pointed-to memory is not touched in any way.
   * Managing the pointer is the user's responsibility.
   */
  ~vec() {
    // @TODO: fix
    delete[] m_arr;
  }
  /*!
   * @brief Returns size of vector
   */
  size_t size() const { return m_size; }
  /*!
   * @brief Returns current capacity
   */
  size_t capacity() const { return m_capacity; }
  /*!
   * @brief Returns true if size of vector > 0, overwise false
   */
  bool empty() const { return m_size == 0; }

  iterator begin() { return m_begin; }

  iterator end() { return m_end; }

  const_iterator begin() const { return m_begin; }

  const_iterator end() const { return m_end;}

  /*!
   * @brief Subscript access to the data contained in the vector.
   *        No index check
   * @param  index Index in vector
   * @return       Element
   */
  reference operator[](int index) noexcept {
    return m_arr[index];
  }
  /*!
   * @brief Read access to the data contained in vector
   *        No index check
   * @param  index Index in vector
   * @return       Element
   */
  const_reference operator[](int index) const noexcept {
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
      // @TODO: fix memory leak
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
      // @TODO: fix memory leak
      throw std::out_of_range("vec::_M_range_check");
    }
    return m_arr[index];
  }
};
} // namespace containers
