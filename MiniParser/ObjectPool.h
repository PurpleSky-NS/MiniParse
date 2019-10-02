#pragma once

#include <vector>
#include <list>

template <class T>
class ObjectPool
{
public:

	/*对象池基础容量，默认用该容量作为allocationSize*/
	inline ObjectPool(unsigned capacity);//建议使用
	/*对象池基础容量以及若是基础容量使用完，在构建新对象的数量*/
	inline ObjectPool(unsigned capacity, unsigned allocationSize);//建议使用
	inline ObjectPool(ObjectPool&& objectPool);
	inline ~ObjectPool();
	ObjectPool() = delete;
	ObjectPool(const ObjectPool&) = delete;

	/*获取一个对象*/
	inline T* GetObject();

	/*释放一个对象*/
	inline void FreeObject(T* obj);

	/*获取一个对象并记录*/
	inline T* GetRecordObject();

	/*释放所有记录的对象*/
	inline void FreeRecordObject();

	/*根据设置的allocationSize，再构造一定数目对象*/
	inline void AllocObjects();
	/*再构造一定数目对象*/
	inline void AllocObjects(unsigned capacity);

	/*设置每次再构造对象数量*/
	inline void SetAllocationSize(unsigned allocationSize);

	/*获取每次再构造对象数量*/
	inline unsigned GetAllocationSize()const;

	/*清空所有对象*/
	inline void ClearObjects();

	/*获取对象数量*/
	inline unsigned Size()const;

private:

	std::vector<T*> m_arrayStoragePool;
	std::list<T*> m_objectPool;
	std::vector<T*> m_recordObjects;
	unsigned m_size;
	unsigned m_allocationSize;
};

template<class T>
ObjectPool<T>::ObjectPool(unsigned capacity) :
	ObjectPool(capacity, capacity)
{}

template<class T>
ObjectPool<T>::ObjectPool(unsigned capacity, unsigned allocationSize)
{
	m_size = capacity;
	SetAllocationSize(allocationSize);
	AllocObjects(capacity);
}

template<class T>
ObjectPool<T>::ObjectPool(ObjectPool&& objectPool)
{
	m_arrayStoragePool = std::move(objectPool.m_arrayStoragePool);
	m_objectPool = std::move(objectPool.m_objectPool);
	m_size = objectPool.m_size;
	objectPool.m_size = 0;
	m_allocationSize = objectPool.m_allocationSize;
}

template<class T>
ObjectPool<T>::~ObjectPool()
{
	for (auto i : m_arrayStoragePool)
		delete[] i;
}

template<class T>
T* ObjectPool<T>::GetObject()
{
	if (m_objectPool.empty())
		AllocObjects();
	auto obj = m_objectPool.back();
	m_objectPool.pop_back();
	return obj;
}

template<class T>
void ObjectPool<T>::FreeObject(T* obj)
{
	m_objectPool.push_back(obj);
}

template<class T>
T* ObjectPool<T>::GetRecordObject()
{
	T* obj = GetObject();
	m_recordObjects.push_back(obj);
	return obj;
}

template<class T>
void ObjectPool<T>::FreeRecordObject()
{
	for (auto i : m_recordObjects)
		FreeObject(i);
	m_recordObjects.clear();
}

template<class T>
void ObjectPool<T>::AllocObjects()
{
	AllocObjects(m_allocationSize);
}

template<class T>
void ObjectPool<T>::AllocObjects(unsigned capacity)
{
	if (capacity == 0)
		return;
	T* newObjects = new T[sizeof(T) * capacity];
	m_arrayStoragePool.push_back(newObjects);
	//切分对象
	for (unsigned i = 0; i < capacity; ++i)
		m_objectPool.push_back(&newObjects[i]);
	m_size += capacity;
}

template<class T>
void ObjectPool<T>::SetAllocationSize(unsigned allocationSize)
{
	m_allocationSize = (allocationSize == 0 ? 1 : allocationSize);
}

template<class T>
unsigned ObjectPool<T>::GetAllocationSize() const
{
	return m_allocationSize;
}

template<class T>
void ObjectPool<T>::ClearObjects()
{
	for (auto i : m_arrayStoragePool)
		delete[] i;
	m_arrayStoragePool.clear();
	m_objectPool.clear();
	m_size = 0;
}

template<class T>
unsigned ObjectPool<T>::Size() const
{
	return m_size;
}
