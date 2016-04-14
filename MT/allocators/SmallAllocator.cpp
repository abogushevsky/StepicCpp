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
		if (offset + sizeof(int) + 1 >= SZ) return NULL;
		*(Memory + offset) = '1'; //set mark of occupied block

		int *sz = (int *) (Memory + (offset + 1)); //1 is occupied mark block
		*sz = Size;
		std::cout << "Allocating size: " << *sz << std::endl;		
		
		offset += sizeof(int) + 1; //header offset added
		if (offset + Size >= SZ) return NULL;
		void *res = Memory + offset;
		offset += Size;
		return res;
	};

        void *ReAlloc(void *Pointer, unsigned int Size) {};

        void Free(void *Pointer) {
		int sz = *((int *) Pointer - 1); //get the allocated size value
		std::cout << "Object size is: " << sz << std::endl;
		sz += sizeof(int) + 1; //sum with header (size value + occupied mark)
		char *ptr = ((char *) Pointer) - sz;
		while(ptr != Pointer) {
			*ptr = '\0';
			ptr++;
		}
	};
};


int main(int argc, char **argv) {
	SmallAllocator sa;
	int *i = (int *) sa.Alloc(sizeof(int));
	std::cout << "After Alloc" << std::endl;
	*i = 4200012;
	std::cout << "Value at allocated area: " << *i << std::endl;
	sa.Free(i);
}
