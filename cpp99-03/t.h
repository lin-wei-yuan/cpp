#ifndef T_H
#define T_H

#include <iostream>
#include <stdexcept>

class T
{
public:
  T() : m_index(0) {
    std::cout << "Default T::ctor called. m_index = "<< m_index << std::endl;
  }

  T(int _m_index) : m_index(_m_index) {
    std::cout << "T::Ctor with params called. m_index = " << m_index << std::endl;
  }

  T(const T& that) : m_index(that.getIndex()) {
    std::cout<< "Copy T::ctor called. Source = " << that.getIndex() << std::endl;
  }

  ~T() {
    std::cout << "~T::dtor called. m_index = " << m_index << std::endl;
  }

protected:
  int m_index;
public:
  friend std::ostream& operator << (std::ostream& out,  const T& that) {
    out << that.getIndex();
    return out;
  }

  int getIndex() const { return m_index; }
  void setIndex(int _m_index) { m_index = _m_index; }
};


#endif // T_H
