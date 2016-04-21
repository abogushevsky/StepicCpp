#include <stdlib.h>
#include <iostream>

#define SZ 1048576

class SmallAllocator {
private:
	char Memory[SZ];
	int offset = 0;
	char *cp; //current offset pointer

	int getSize(void *pointer) const {
		int sz = *((int *) pointer - 1); //get the allocated size value
		std::cout << "Object size is: " << sz << std::endl;
		return sz;
	};

	char *getAllocObjStart(void *pointer, int sz) {
		return ((char *) pointer) - (sz + sizeof(int) + 1);
	}

public:
	void *Alloc(unsigned int Size) {
		if (offset + sizeof(int) + 1 + Size >= SZ) return NULL;
		*(Memory + offset) = '1'; //set mark of occupied block
		int *sz = (int *) (Memory + (offset + 1)); //1 is occupied mark block
		*sz = Size;
		std::cout << "Allocating size: " << *sz << std::endl;

		offset += sizeof(int) + 1; //header offset added
		void *res = Memory + offset;
		offset += Size;
		return res;
	};

	void *ReAlloc(void *Pointer, unsigned int Size) {
		int sz = getSize(Pointer);
		if (offset + sizeof(int) + 1 + sz >= SZ) return NULL;
		char *start = getAllocObjStart(Pointer, sz);
		//TODO: Move header, size & data to the current offset position		
		//TODO: Free current allocated area
		char *end = start + sz;
		char *target = Memory + offset;
		while (start != end) {
			*target = *start;
			target++;
			start++;
			offset++;
		}
		return (void *)(target - sz - sizeof(int) - 1); //temp
	};

	void Free(void *Pointer) {
		int sz = getSize(Pointer);
		char *ptr = getAllocObjStart(Pointer, sz); //sum of sz and header (size value + occupied mark)
		while (ptr != ((char *) Pointer + sz)) {
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
