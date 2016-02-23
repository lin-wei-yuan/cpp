#include <algorithm>
#include <vector> // coz we need fast access by element's index

#include "./utils.h"

using namespace std;

const int m_sequenceSize = 20;

enum class SEC_TYPE {
  RANDOM, SORT, BACKSORT
};

vector<int> sequence(SEC_TYPE type) {
  vector<int> result(m_sequenceSize);
    switch (type) {
    case SEC_TYPE::RANDOM :
      for (int i = 0; i < m_sequenceSize; ++i) {
          result.at(i) = rand() % m_sequenceSize + 1;
      }
      break;

    case SEC_TYPE::SORT :
      std::iota(result.begin(), result.end(), 1);
      break;

    case SEC_TYPE::BACKSORT :
      std::iota(result.rbegin(), result.rend(), 1);
      break;
    default :
      std::iota(result.begin(), result.end(), 1);
    }
  return result;
}

// Non-modifying sequence operations
void challenge1() {
  auto seq = sequence(SEC_TYPE::RANDOM);
  print<decltype(seq)>(seq);
  // O(n) => n == last - first
  cout << boolalpha << "At least one is even: " << any_of(seq.begin(), seq.end(), [](int e) { return e % 2 == 0;}) << endl;
  // O(n) => n == last - first
  cout << boolalpha << "None of elements is == 0: " << none_of(seq.begin(), seq.end(), [](int e) { return e == 0;}) << endl;
  // O(n) => n == last - first
  cout << boolalpha << "All of elements is > 0: " << all_of(seq.begin(), seq.end(), [](int e) { return e > 0;}) << endl;
  // O(n) => n == last - first
  for_each(seq.begin(), seq.end(), []( int& e) { e *= 2; });
  print<decltype(seq)>(seq);

  cout << "Count of 7: " << count(seq.begin(), seq.end(), 7) << endl;
  cout << "Count of elements that divisible by 7: " << count_if(seq.begin(), seq.end(), [](int e) { return e % 7 == 0; }) << endl;

  auto seq1 = sequence(SEC_TYPE::SORT);
  decltype(seq1) merged;
  merge(seq1.begin(), seq1.end(), seq1.rbegin(), seq1.rend(), back_inserter(merged));
  print<decltype(merged)>(merged);
  merged.insert(merged.begin() + merged.size() / 2, -1);
  print<decltype(merged)>(vector<int>(merged.begin(), mismatch(merged.begin(), merged.end(), merged.rbegin()).first));

  cout << "Is vector palindrome: " << boolalpha << equal(merged.begin(), merged.begin() + merged.size() / 2, merged.rbegin()) << endl;
}

int main() {
  challenge1();
  return 0;
}
