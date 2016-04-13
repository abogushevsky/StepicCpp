#include <stdlib.h>
#include <iostream>

class SmallAllocator {
private:
        char Memory[1048576];
	char *cp; //current offset pointer
public:
        void *Alloc(unsigned int Size) {
		size_t *sz = (size_t*)(cp + sizeof(size_t));
		*sz = Size;
	};
        void *ReAlloc(void *Pointer, unsigned int Size) {};
        void Free(void *Pointer) {};
};


int main(int argc, char **argv) {
	std::cout << "Small Allocator" << std::endl;
}
