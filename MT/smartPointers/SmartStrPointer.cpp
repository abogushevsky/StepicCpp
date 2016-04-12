#include <iostream>

class SmartStrPointer {
private:
  std::string *pointer;
  void ensurePtr() {
    if (!pointer) {
      pointer = new std::string();
    }
  }
    
public:
  SmartStrPointer(std::string *p): pointer(p) {};
  ~SmartStrPointer() {
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
  SmartStrPointer ssp(new std::string("test"));
  SmartStrPointer nsp(NULL);
  std::cout << "Smart ptr: "<< *ssp << std::endl << "NULL ptr: " << *nsp  << std::endl;
  return 0;
}
