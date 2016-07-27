#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
using namespace std;

#define THREAD_POOL_SIZE 200
#define ELEMENTS 100000000

/* Basic stack node */
template<class T>
struct node {
  T data;
  node* next;
  node(const T& data) : data(data), next(nullptr) {}
  ~node() {}
};

/* Classic stack */
template<class T>
class stack
{
  node<T>* head;
  node<T>* tail;
  int m_size;
  std::mutex m_mutex;

public:
  stack()
    : head(nullptr)
    , tail(nullptr)
    , m_size(0)
  {}

  ~stack() {
    while(head != nullptr) {
      tail = head->next;
      delete head;
      head = tail;
    }
  }

  void push(T value) {
  std::lock_guard<std::mutex> guard(m_mutex);
  node<T>* tmp = new node<T>(value);
    if(tail == 0) {
      tail = tmp;
    } else {
      tmp->next = tail;
      tail = tmp;
    }
    m_size++;
  }

  void print() const {
    if (tail == nullptr) {
      cout << "Nothing" << endl;
    } else {
      for(node<T>* ptr = tail; ptr != nullptr; ptr = ptr->next) {
        cout << ptr->data << " ";
      }
      cout << '\n';
    }
  }

  int size() const {
    return m_size;
  }

};

/* Lock-free stack */
template<class T>
class stack_lock_free
{
  std::atomic<node<T>*> head;
  std::atomic<node<T>*> tail;
  int m_size;

public:
  stack_lock_free()
    : m_size(0)
  {}
  ~stack_lock_free() {
    node<T>* tmp = head.load(std::memory_order_relaxed);
    for (int i = 0; i < m_size; ++i) {
      node<T>* for_delete = tmp;
      tmp = tmp->next;
      delete for_delete;
    }
  }

  void push(T value) {
    node<T>* tmp = new node<T>(value);
    tmp->next = head.load(std::memory_order_relaxed);
    while(!std::atomic_compare_exchange_weak_explicit(
          &head,            // pointer to the atomic object to test and modify
          &tmp->next,         // pointer to the value expected to be found in the atomic object
          tmp,            // the value to store in the atomic object if it is as expected
          std::memory_order_release,  // the memory synchronization ordering for the read-modify-write operation if the comparison succeeds
          std::memory_order_relaxed));// the memory synchronization ordering for the load operation if the comparison fails
    m_size++;
  }

  void print() const {
    node<T>* tmp = head.load(std::memory_order_relaxed);
    for (int i = 0; i < m_size; ++i) {
      cout << tmp->data << " ";
      tmp = tmp->next;
    }
    /*
      Segmentation fault

      while(tmp != nullptr) {
      cout << tmp->data << " ";
      tmp = tmp->next;
      }
    */
  }

  int size() const {
    return m_size;
  }
};

/* Testing classic stack */
void push_portion(stack<int>& s1, int count) {
  for (int i = 0; i < count; ++i) {
    int value = 1 + rand() % 100;
    s1.push(value);
  }
}

void test_classic() {
  stack<int> s1;
  double start_time = clock();
  std::vector<std::thread> pool;
  for (int i = 0; i < THREAD_POOL_SIZE; ++i) {
    pool.push_back(std::thread(push_portion, std::ref(s1), ELEMENTS / THREAD_POOL_SIZE));
  }
  for (auto &thread: pool) {
    thread.join();
  }
  double end_time = clock();
  cout << "Classic stack(push): " << (end_time - start_time) / CLOCKS_PER_SEC << " sec" << endl;
}

/* Testing lock-free stack */
void push_portion_lock_free(stack_lock_free<int>& s1, int count) {
  for (int i = 0; i < count; ++i) {
    int value = 1 + rand() % 100;
    s1.push(value);
  }
}

void test_lock_free() {
  stack_lock_free<int> s1;
  double start_time = clock();
  std::vector<std::thread> pool;
  for (int i = 0; i < THREAD_POOL_SIZE; ++i) {
    pool.push_back(std::thread(push_portion_lock_free, std::ref(s1), ELEMENTS / THREAD_POOL_SIZE));
  }
  for (auto &thread: pool) {
    thread.join();
  }
  double end_time = clock();
  cout << "Lock free stack(push): " << (end_time - start_time) / CLOCKS_PER_SEC << " sec" << endl;
}

int main() {
  test_classic();
  test_lock_free();
  return 0;
}
