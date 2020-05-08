#pragma once
class BitArray;

class FixedSizeAllocator
{
public:
	void Initialize(size_t i_alignment, size_t i_blockCount, BitArray* i_bitArray);
	void Destroy();
	void* alloc();
	void free(void *ptr);
	bool contains(void* ptr) const;	
private:

	size_t m_alignment; 
	size_t m_blockCount;
	BitArray* m_bitArray;
	void* m_heap;
	size_t heapSize;

	typedef unsigned char GuardBand;

	GuardBand guardPattern = 0xCC;

	inline size_t blocksize() const { return m_alignment + 2 * sizeof(GuardBand); }
	inline void* payloadPointer(char* bp) const { return bp + sizeof(GuardBand); }
	inline GuardBand* firstGuard(void* bp) const { return reinterpret_cast<GuardBand*>(reinterpret_cast<char*>(bp) - sizeof(GuardBand)); }
	inline GuardBand* lastGuard(void* bp) const { return reinterpret_cast<GuardBand*>(reinterpret_cast<char*>(bp) + m_alignment); }
	
};

