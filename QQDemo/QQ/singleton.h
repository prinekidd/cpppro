#pragma once

template <typename T>
class singleton
{
private:
	static T* p;      

public:
	static T* instance();   
};

template <typename T>
T* singleton<T>::p = new T();  

template <typename T>
T* singleton<T>::instance()
{
	return p;
}
