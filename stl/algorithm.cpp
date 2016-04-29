#include <algorithm>
#include <vector> // coz we need fast access by element's index
#include <iterator>
#include <random>

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

  vector<int> v = { 1, 2, 3, 4, 55, 6, 7, 55, 9, 7, 55, 9, 34, 344 };
  vector<int> subv = { 7, 55, 9 };
  cout << "Distance to first match: " << distance(v.begin(), find(v.begin(), v.end(), 55)) << endl;
  cout << "Distance to first match by predicate: " << distance(v.begin(), find_if(v.begin(), v.end(), [] (int e) { return e % 7 == 0; })) << endl;
  cout << "Distance to first unmatch by predicate: " << distance(v.begin(), find_if_not(v.begin(), v.end(), [] (int e) { return e < 100; })) << endl;
  cout << "Distance to last subsequence match: " << distance(v.begin(), find_end(v.begin(), v.end(), subv.begin(), subv.end())) << endl;

  string incoming = "There are some {{templates}} ! that neet > to be replaced to ?";
  string filter =  "<>&?";

  cout << "Distance to first filter match: " << distance(incoming.begin(),
       find_first_of(incoming.begin(), incoming.end(),
                     filter.begin(), filter.end()
                    )
                                                        ) << endl;
  // O(n * m) => n = incoming.size(), m = condition.size()
  string condition = "{{templates}}";
  cout << "First substring match: " << distance(incoming.begin(),
       search(incoming.begin(), incoming.end(),
              condition.begin(), condition.end()
             )
                                               ) << endl;

}

// Modyfying sequence opeartions
void challenge2() {
  vector<int> from = sequence(SEC_TYPE::SORT);
  vector<int> to;
  copy(from.begin(), from.end(), back_inserter(to));
  print<decltype(to)>(to);
  copy_if(from.begin(), from.end(), back_inserter(to), [] (int e) { return e % 2 == 0; });
  // Output to std::cout
  copy(to.begin(), to.end(), ostream_iterator<int>(cout, " "));
  cout << endl;

  transform(to.begin(), to.end(), to.begin(), [] (int e) { return e * 2; });
  print<decltype(to)>(to);

  vector<int> v1(10);
  // Generate 10 random values
  generate(v1.begin(), v1.end(), rand);
  print<decltype(v1)>(v1);
  std::string input = "Text with some";
  input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
  std::cout << input << endl;

  input = "Text\t\t\n with some\t\t\n";
  input.erase(std::remove_if(input.begin(), input.end(), [](char x) { return std::isspace(x); }), input.end());
  std::cout << input << endl;

  vector<int> v2 = sequence(SEC_TYPE::SORT);
  auto p = make_pair(8, 108);
  replace(v2.begin(), v2.end(), p.first, p.second);
  print<decltype(v2)>(v2);

  replace_if(v2.begin(), v2.end(), [](int e) { return e % 2 == 0; }, -1);
  print<decltype(v2)>(v2);

  vector<int> v3 = sequence(SEC_TYPE::SORT);
  vector<int> v4 = sequence(SEC_TYPE::BACKSORT);
  // O(n)
  swap_ranges(v3.begin(), v3.end(), v4.begin());
  print<decltype(v3)>(v3);
  print<decltype(v4)>(v4);
  // O(n)
  reverse(v3.begin(), v3.end());
  print<decltype(v3)>(v3);
  // Create generator
  random_device rd;
  mt19937 generator(rd());
  // O(n)
  shuffle(v3.begin(), v3.end(), generator);
  print<decltype(v3)>(v3);

  // Try to use unique for non-sorted containers
  vector<int> vzz = sequence(SEC_TYPE::SORT);
  replace_if(vzz.begin(), vzz.end(), [](int e) { return e % 2 == 0; }, -1);

  vector<int> result(vzz.begin(), unique(vzz.begin(), vzz.end()));
  print<decltype(result)>(result);
  // O(N·log(N))
  sort(vzz.begin(), vzz.end());
  print<decltype(vzz)>(vzz);

  vector<int> result2(vzz.begin(), unique(vzz.begin(), vzz.end()));
  print<decltype(result2)>(result2);
}

// Sorting operations
void challenge3() {
  vector<int> v1 = sequence(SEC_TYPE::SORT);
  vector<int> v2 = sequence(SEC_TYPE::BACKSORT);
  // O(n)
  cout << "Is sequence sorted : " << boolalpha << is_sorted(v1.begin(), v1.end()) << endl;
  cout << "Is sequence sorted : " << boolalpha << is_sorted(v2.begin(), v2.end()) << endl;
}

void challenge4() {
  vector<int> v1 = sequence(SEC_TYPE::SORT);
  print<decltype(v1)>(v1);

  auto lb = lower_bound(v1.begin(), v1.end(), 8);
  auto ub = upper_bound(v1.begin(), v1.end(), 18);
  cout << "Lower and upper bounds: " << *(lb) << " and " << *(ub) << ", distance: " << distance(lb, ub) << endl;
  copy(lb, ub, ostream_iterator<int>(cout, " "));
}

int main() {
  // challenge1();
  // challenge2();
  // challenge3();
  challenge4();
  return 0;
}
