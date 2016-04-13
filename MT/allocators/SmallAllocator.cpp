#include <stdlib.h>
#include <iostream>

#define SZ 1048576

class SmallAllocator {
private:
        char Memory[SZ];
	int offset = 0;
	char *cp; //current offset pointer
public:
        void *Alloc(unsigned int Size) {
		if (offset + sizeof(size_t) + 1 >= SZ) return NULL;
		*(Memory + offset) = 1; //set mark of occupied block
		size_t *sz = (size_t *) Memory + offset + 1; //1 is occupied mark block
		*sz = Size;
		std::cout << "Allocating size: " << *sz << std::endl;		
		
		offset += sizeof(size_t) + 1; //header offset added
		if (offset + Size >= SZ) return NULL;
		void *res = Memory + offset;
		offset += Size;
		return res;
	};
        void *ReAlloc(void *Pointer, unsigned int Size) {};
        void Free(void *Pointer) {
		size_t *sz = (size_t *) Pointer - sizeof(size_t);
		std::cout << "Object size is: " << *sz << std::endl;
	};
};


int main(int argc, char **argv) {
	SmallAllocator sa;
	int *i = (int *) sa.Alloc(sizeof(int));
	std::cout << "After Alloc" << std::endl;
	*i = 10012;
	std::cout << "Value at allocated area: " << *i << std::endl;
	sa.Free(i);
}
