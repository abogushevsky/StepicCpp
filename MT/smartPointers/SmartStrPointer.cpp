#include <iostream>

class SmartStrPointer {
private:
    std::string *pointer;
    
public:
    SmartStrPointer(std::string *p): pointer(p) {};
    operator std::string*() { return pointer; }
    std::string *operator->() { return pointer; }
};
