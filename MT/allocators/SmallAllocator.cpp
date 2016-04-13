#include <stdlib.h>
#include <iostream>

class SmallAllocator {
private:
        char Memory[1048576];
	char *cp; //current offset pointer

public:
        void *Alloc(unsigned int Size) {
		cp += sizeof(size_t);
		size_t *sz = (size_t *) cp;
		*sz = Size;
		std::cout << "Allocating size: " << *sz << std::endl;		
		char *result = ++cp;
		cp += Size - 1;
		return result;
	};
        void *ReAlloc(void *Pointer, unsigned int Size) {};
        void Free(void *Pointer) {};
};


int main(int argc, char **argv) {
	SmallAllocator sa;
	int *i = (int *) sa.Alloc(sizeof(int));
	std::cout << "After Alloc";
	std::cout << "Value at allocated area: " << *i << std::endl;
}
