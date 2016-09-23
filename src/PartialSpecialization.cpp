#include <iostream>

enum class Choice {
  a,
  b
};

template <typename T, Choice choice>
class Foo;

template <typename T>
class Foo<T, Choice::a> {
public:
  static bool F() { return true; }
};

template <typename T>
class Foo<T, Choice::b> {
public:
  static bool F() { return false; }    
};

int main() {
  std::cout << Foo<int, Choice::a>::F() << " " << Foo<float, Choice::b>::F()
            << "\n";
  return 0;
}
