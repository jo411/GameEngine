#pragma once
#include "SmartPointer.h"
#include "RefCounter.h"
template <typename T>class WeakPointer
{
	
public:
	//make Strongpointers a friend class
	template < class Y > friend class StrongPointer;
private:
	T* pointer;
	RefCounter* references;

public: 
	WeakPointer() :pointer(nullptr), references(nullptr)
	{
	}

	T* getRawPointer() const
	{
		return pointer;
	}
	RefCounter* getRawReferences() const
	{
		return references;
	}
	WeakPointer(const WeakPointer<T>& wp) : pointer(wp.pointer), references(wp.references)
	{
		AddWeakReference();
	}

	WeakPointer(const SmartPointer<T>& sp) : pointer(sp.pointer), references(sp.references)
	{
		AddWeakReference();
	}

	~WeakPointer()
	{
		ReleaseAndDeleteIfNeeded();
	}

	WeakPointer<T>& operator =(const WeakPointer<T>& wp)
	{
		if (this != &wp)
		{
			ReleaseAndDeleteIfNeeded();
			pointer = wp.pointer;
			references = wp.references;
			AddWeakReference();
		}
		return *this;
	}

	//returns true if this weak pointer points to a living object
	bool IsAlive()
	{
		if (references == nullptr)
		{
			return false;
		}
		else
		{
			if (references->getSmartCount() == 0)
			{
				return false;
			}
		}
		return true;
	}

	SmartPointer<T> Aquire()
	{
		if (references == nullptr)
		{
			return SmartPointer<T>(nullptr);
		}
		else
		{
			SmartPointer<T> sp;

			if (references->getSmartCount() == 0)
			{
				return sp;
			}
			sp.ReleaseAndDeleteIfNeeded();

			sp.references = references;
			sp.pointer = pointer;
			references->AddSmartRef();

			return sp;
		}
	}

private: 
	void AddWeakReference()
	{
		if (references != nullptr)
		{
			references->AddWeakRef();
		}
	}

	void ReleaseAndDeleteIfNeeded()
	{
		if (references != nullptr)
		{
			if (references->ReleaseWeak() == 0 && references->getSmartCount()==0)
			{
				delete references;
			}

		}
	}

};

