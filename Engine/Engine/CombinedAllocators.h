#pragma once
class CombinedAllocators
{
public: 
	static CombinedAllocators* m_instance;
	void Init(void * i_pHeapMemory, size_t i_sizeHeapMemory);
	void Destroy();
	void* m_alloc(size_t size);
	void m_free(void* ptr);

private:

};

