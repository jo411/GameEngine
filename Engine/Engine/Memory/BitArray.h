#pragma once
#include "MyMalloc.h"
class BitArray
{
public:
	static BitArray* Create(size_t numBits);

	~BitArray();

	void ClearAll();
	void SetAll();

	BitArray& operator =(const BitArray&);	

	bool IsBitSet(size_t index) const;
	bool IsBitClear(size_t index) const;

	void SetBit(size_t index);
	void ClearBit(size_t index);

	bool GetFirstClearBit(size_t& index) const;
	bool GetFirstSetBit(size_t & index) const;

	bool operator[](size_t index)const;	

private:	
	BitArray(size_t numBits);//by making the constructor private we only can create bitarrays from the static factory method. 
	BitArray(const BitArray& bitarr) = delete;//Since all object creation is handled through the static factory we don't want to allow access to the copy constructor

	size_t bitCount;
	inline size_t getBitCount()const { return bitCount; }

	size_t allignedWordCount;
	inline size_t WordSizeInBits() const { return (sizeof(size_t) * 8); }

	size_t* bits;//array of bits that this bit array tracks	

	bool isValidIndex(size_t index) const;
	inline size_t getWordIndex(size_t bitIndex) const { return bitIndex / WordSizeInBits(); }
};

