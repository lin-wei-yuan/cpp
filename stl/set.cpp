template<typename T>
struct greater_than
{
  bool operator() (const T& l, const T& r) const {
    return l > r;
  }
};

/* Set */
void challenge() {
  int numbers[] = { 1, 3, 2, 4, 5, 5, 4, 3, 2, 1 };
  set<int>  s1(numbers, numbers + 10);
  print<set<int> >(s1);

  cout << s1.size() << endl;
  // O(logn)
  cout << s1.count(2) << endl;
  // O(logn)
  set<int>::iterator search = s1.find(3);
  if (search != s1.end()) {
    cout << (*search) << endl;
  } else {
    cout << "not found!" << endl;
  }
  // insert overloads
  std::pair<set<int>::iterator, bool> result = s1.insert(6);
  // std::pair<it, bool>
  cout << (*result.first) << ", " << result.second << ", " << std::distance(s1.begin(), result.first) << endl;
  print<set<int> >(s1);
  // O(1) if before of after result.first, else O(logn)
  set<int>::iterator it = s1.insert(result.first, 8);
  cout << (*it) << endl;
  // STL comparer
  set<int, std::greater<int> > s2 (numbers, numbers + 10);
  print<set<int, std::greater<int> > >(s2);
  // Custom comparer
  set<int, greater_than<int> > s3 (numbers, numbers + 10);
  print<set<int, greater_than<int> > >(s3);
}


int main() {
  challenge();
  return 0;
}
