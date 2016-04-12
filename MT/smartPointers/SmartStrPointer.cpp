#include <iostream>

class StringPointer {
private:
  std::string *pointer;
  void ensurePtr() {
    if (!pointer) {
      pointer = new std::string();
    }
  }
    
public:
  StringPointer(std::string *p): pointer(p) {};
  ~StringPointer() {
    if (pointer) {
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
