#ifndef _SINGLETON_H_
#define  _SINGLETON_H_

#include "iostream"
class Singleton
{
public:
	static Singleton* instance();
protected:
	Singleton();
private:
	static Singleton* _instance;
};


template <typename T>
class TSingleton
{
public:
	template <typename... Args>
	static T* InstanceGet(Args&&... args)
	{
		static T s_objInstance = T(std::forward<Args>(args)...);
		return &s_objInstance;
	}

private:
	TSingleton(void) = default;
	virtual ~TSingleton(void) = default;
	TSingleton(const TSingleton&) = delete;
	TSingleton& operator=(const TSingleton&) = delete;
};
#endif