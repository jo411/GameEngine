#pragma once
#include "MyMalloc.h"
class BitArray
{
public:
	static BitArray* Create(size_t numBits);
	BitArray(size_t numBits);
	~BitArray();

	void ClearAll();
	void SetAll();

	bool IsBitSet(size_t index) const;
	bool IsBitClear(size_t index) const;

	void SetBit(size_t index);
	void ClearBit(size_t index);

	bool GetFirstClearBit(size_t& index) const;
	bool GetFirstSetBit(size_t & index) const;

	bool operator[](size_t index)const;	
private:	
	size_t bitCount;
	size_t allignedWordCount;
	inline size_t WordSizeInBits() const { return (sizeof(size_t) * 8); }
	size_t* bits;//array of bits that this bit array tracks

	//a bit array should be tied to a single memory manager. We dont want to allow copying. If this class had more uses in the engine these should be defined. 
	BitArray(const BitArray&) = delete;
	BitArray& operator =(const BitArray&) = delete;

	bool isValid(size_t index) const;
	inline size_t getWordIndex(size_t bitIndex) const { return bitIndex / WordSizeInBits(); }
};

