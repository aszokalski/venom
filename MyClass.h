#ifndef MY_CLASS

class MyClass {
public:
  MyClass() {}
  virtual ~MyClass() {}

  int add(int a, int b) { return a + b; };
  int sub(int a, int b) { return a - b; };
};

#endif // !MY_CLASS
