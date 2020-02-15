#pragma once
#include "RefCounter.h"
template <typename T> class SmartPointer
{

public:
	//make weakpointers a friend class
	template < class Y > friend class WeakPointer;
private:
	T* pointer;
	RefCounter* references;


public:
	explicit SmartPointer(T* i_data) : pointer(i_data), references(0)
	{
		references = new RefCounter();
		references->AddSmartRef();
	}

	SmartPointer() : pointer(nullptr), references(0)
	{
		references = new RefCounter();
		references->AddSmartRef();
	}

	~SmartPointer()
	{
		ReleaseAndDeleteIfNeeded();
	}

	SmartPointer(const SmartPointer<T>& sp) : pointer(sp.pointer), references(sp.references)
	{
		if (references)
		{
			references->AddSmartRef();
		}
		
	}

	SmartPointer(const WeakPointer<T>& wp) : pointer(wp.pointer), references(wp.references)
	{
		if (references)
		{
			if (references->getSmartCount == 0)
			{
				pointer = nullptr;
				references = nullptr;
			}
			else
			{
				references->AddSmartRef();
			}
		}
	}

	SmartPointer(SmartPointer<T>&& sp) : pointer(sp.pointer), references(sp.references)
	{
		sp.pointer = nullptr;
		sp.references = nullptr;
	}

	SmartPointer<T>& operator=(const SmartPointer<T>& sp)
	{
		if (this != &sp)
		{
			ReleaseAndDeleteIfNeeded();

			pointer = sp.pointer;
			references = sp.references;
			references->AddSmartRef();
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
	
	operator bool()
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
	
	void ReleaseAndDeleteIfNeeded()
	{		
		

		if (references && references->ReleaseSmart() == 0)
		{
			if (pointer)
			{
				delete pointer;				
			}	
			if (references->getWeakCount() == 0)
			{
				delete references;
			}
						
		}
	}


};

