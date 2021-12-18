#pragma once

#include <memory>
#include <mutex>

template <typename T>
class Singleton
{
public:
	~Singleton() = default;

	Singleton(Singleton<T>&&) = delete;
	Singleton(const Singleton<T>& src) = delete;
	Singleton<T>& operator=(const Singleton<T> rhs) = delete;
	Singleton<T>& operator=(Singleton<T>&&) = delete;

protected:
	Singleton() = default;

public:
	static T& Instance()
	{
		std::call_once(_onceFlag
			, []()
			{
				if(_instance == nullptr)
				    _instance.reset(new T);
			});
		
		return *(_instance.get());
	}

private:
	static std::unique_ptr<T> _instance;
	static std::once_flag _onceFlag;
};

template <typename T>
std::unique_ptr<T> Singleton<T>::_instance;

template <typename T>
std::once_flag Singleton<T>::_onceFlag;