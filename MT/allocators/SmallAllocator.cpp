class SmallAllocator {
private:
        char Memory[1048576];
public:
        void *Alloc(unsigned int Size) {};
        void *ReAlloc(void *Pointer, unsigned int Size) {};
        void Free(void *Pointer) {};
};
