#include <stdlib.h>
#include <iostream>

class SmallAllocator {
private:
	#define SZ 1048576
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
	  //TODO: ReAlloc failing 7th test
		void *newAlloc = Alloc(Size);
		if (!newAlloc) return NULL;

		int sz = getSize(Pointer);
		for (int i = 0; i < Size; i++) {
			((char *)newAlloc)[i] = ((char *)Pointer)[i];
		}
		Free(Pointer);
		return newAlloc;
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

	SmallAllocator A1;
	int * A1_P1 = (int *) A1.Alloc(sizeof(int));
	A1_P1 = (int *) A1.ReAlloc(A1_P1, 2 * sizeof(int));
	A1.Free(A1_P1);
	SmallAllocator A2;
	int * A2_P1 = (int *) A2.Alloc(10 * sizeof(int));
	for(unsigned int i = 0; i < 10; i++) A2_P1[i] = i;
	for(unsigned int i = 0; i < 10; i++) if(A2_P1[i] != i) std::cout << "ERROR 1" << std::endl;
	int * A2_P2 = (int *) A2.Alloc(10 * sizeof(int));
	for(unsigned int i = 0; i < 10; i++) A2_P2[i] = -1;
	for(unsigned int i = 0; i < 10; i++) if(A2_P1[i] != i) std::cout << "ERROR 2" << std::endl;
	for(unsigned int i = 0; i < 10; i++) if(A2_P2[i] != -1) std::cout << "ERROR 3" << std::endl;
	A2_P1 = (int *) A2.ReAlloc(A2_P1, 20 * sizeof(int));
	for(unsigned int i = 10; i < 20; i++) A2_P1[i] = i;
	for(unsigned int i = 0; i < 20; i++) if(A2_P1[i] != i) std::cout << "ERROR 4" << std::endl;
	for(unsigned int i = 0; i < 10; i++) if(A2_P2[i] != -1) std::cout << "ERROR 5" << std::endl;
	A2_P1 = (int *) A2.ReAlloc(A2_P1, 5 * sizeof(int));
	for(unsigned int i = 0; i < 5; i++) if(A2_P1[i] != i) std::cout << "ERROR 6" << std::endl;
	for(unsigned int i = 0; i < 10; i++) if(A2_P2[i] != -1) std::cout << "ERROR 7" << std::endl;
	A2.Free(A2_P1);
	A2.Free(A2_P2);
}
