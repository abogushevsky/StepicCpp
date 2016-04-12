#include <iostream>

class StringPointer {
private:
  std::string *pointer;
  bool isNullPtr = false;
  void ensurePtr() {
    if (!pointer) {
      isNullPtr = true;
      std::cout << "Creating empty str..." << std::endl;
      pointer = new std::string();
    }
  }
    
public:
  StringPointer(std::string *p): pointer(p) {};
  ~StringPointer() {
    std::cout << "destructor" << std::endl;
    if (isNullPtr && pointer) {
      delete(pointer);
    }
    std::cout << "after destructor" << std::endl;
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
