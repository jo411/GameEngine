#pragma once
#include "RefCounter.h"
template <typename T> class SmartPointer
{
public:
	explicit SmartPointer(T* i_data) : pointer(i_data), references(0)
	{
		references = new RefCounter();
		references->AddRef();
	}

	SmartPointer() : pointer(0), references(0)
	{
		references = new RefCounter();
		references->AddRef();
	}

	~SmartPointer()
	{
		ReleaseAndDeleteIfNeeded();
	}

	SmartPointer(const SmartPointer<T>& sp) : pointer(sp.pointer), references(sp.references)
	{
		references->AddRef();
	}

	SmartPointer<T>& operator=(const SmartPointer<T>& sp)
	{
		if (this != &sp)
		{
			ReleaseAndDeleteIfNeeded();

			pointer = sp.pointer;
			references = sp.references;
			references->AddRef();
		}
		return *this;
	}
	
	T& operator* ()
	{
		return *pointer;
	}
	
	T* operator->()
	{
		return pointer;
	}

	//Comparison operators
	template < class T, class U >
	friend bool operator==(const SmartPointer<T>& lhs, const SmartPointer<U>& rhs)
	{
		return lhs.pointer == rhs.pointer;
	}

	template< class T, class U >
	friend bool operator!=(const SmartPointer<T>& lhs, const SmartPointer<U>& rhs)
	{
		return !(lhs.pointer == rhs.pointer);
	}

	template< class T, class U >
	friend bool operator<(const SmartPointer<T>& lhs, const SmartPointer<U>& rhs)
	{
		return lhs.pointer < rhs.pointer;
	}
	template< class T, class U >
	friend bool operator>(const SmartPointer<T>& lhs, const SmartPointer<U>& rhs)
	{
		return lhs.pointer > rhs.pointer;
	}
	template< class T, class U >
	friend bool operator<=(const SmartPointer<T>& lhs, const SmartPointer<U>& rhs)
	{
		return lhs.pointer < rhs.pointer | lhs.pointer == rhs.pointer;
	}
	template< class T, class U >
	friend bool operator>=(const SmartPointer<T>& lhs, const SmartPointer<U>& rhs)
	{
		return lhs.pointer > rhs.pointer | lhs.pointer == rhs.pointer;
	}

private:
	T* pointer;
	RefCounter* references;
	
	void ReleaseAndDeleteIfNeeded()
	{
		if (references->Release() == 0)
		{
			delete pointer;
			delete references;
		}
	}


};

