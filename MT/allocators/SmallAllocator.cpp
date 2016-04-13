#include <stdlib.h>
#include <iostream>
#include <vector>

#define SZ 1048576

class SmallAllocator {
private:
        char Memory[SZ];
	int offset = 0;
	char *cp; //current offset pointer
public:
        void *Alloc(unsigned int Size) {
		offset += sizeof(size_t);		
		if (offset >= SZ) return NULL;
		size_t *sz = (size_t *) Memory + offset;
		*sz = Size;
		std::cout << "Allocating size: " << *sz << std::endl;		
		
		if (offset >= SZ) return NULL;
		void *res = Memory + offset;
		offset += Size;
		return res;
	};
        void *ReAlloc(void *Pointer, unsigned int Size) {};
        void Free(void *Pointer) {};
};


int main(int argc, char **argv) {
	SmallAllocator sa;
	int *i = (int *) sa.Alloc(sizeof(int));
	std::cout << "After Alloc" << std::endl;
	*i = 16;
	std::cout << "Value at allocated area: " << *i << std::endl;
}
