#include <algorithm>
#include <vector> // coz we need fast access by element's index

#include "./utils.h"

using namespace std;

const int m_sequenceSize = 20;

enum class SEC_TYPE {
  RANDOM, SORT, BACKSORT
};

vector<int> sequence(SEC_TYPE type) {
  vector<int> result;
  for (int i = 0; i < m_sequenceSize; ++i) {
    switch (type) {
    case SEC_TYPE::RANDOM :
      result.push_back(rand() % m_sequenceSize + 1);
      break;

    case SEC_TYPE::SORT :
      result.push_back(i);
      break;

    case SEC_TYPE::BACKSORT :
      result.push_back(m_sequenceSize - i);
      break;
    default :
      result.push_back(rand() % m_sequenceSize + 1);
    }
  }
  return result;
}

// Non-modifying sequence operations
void challenge1() {
  auto seq = sequence(SEC_TYPE::RANDOM);
  print<decltype(seq)>(seq);
}

int main() {
  challenge1();
  return 0;
}
