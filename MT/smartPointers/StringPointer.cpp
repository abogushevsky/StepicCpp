#include <iostream>

class StringPointer {
private:
  std::string *pointer;
  bool isNullPtr = false;
  void ensurePtr() {
    if (!pointer) {
      isNullPtr = true;
      pointer = new std::string();
    }
  }
    
public:
  StringPointer(std::string *p): pointer(p) {};
  ~StringPointer() {
    if (isNullPtr && pointer) {
      delete(pointer);
    }
  }
  operator std::string*() { 
    ensurePtr();
    return pointer;
  }
  std::string *operator->() { 
    ensurePtr();
    return pointer; 
  }
};

int main(int argc, char **argv) {
  std::string s1 = "Hello, world!";
  
  StringPointer sp1(&s1);
  StringPointer sp2(NULL);

  std::cout << sp1->length() << std::endl;
  std::cout << *sp1 << std::endl;
  std::cout << sp2->length() << std::endl;
  std::cout << *sp2 << std::endl;
  return 0;
}
