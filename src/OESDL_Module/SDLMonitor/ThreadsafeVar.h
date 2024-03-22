
#ifndef __THREAD_SAFE_VAR_H__
#define __THREAD_SAFE_VAR_H__


#include <thread>
#include <memory>
#include <functional>

#include <OESDL_Module.h>


template <class T>
class ThreadSafeVar
{
private:

	std::shared_ptr<T> _value;

	SDL_mutex* access_p;

public:

	ThreadSafeVar() : _value(nullptr) { access_p = SDL_CreateMutex(); };
	ThreadSafeVar(std::shared_ptr<T> value) : _value(value){ access_p = SDL_CreateMutex(); };
	ThreadSafeVar(const T& value) 
	{
		_value = std::make_shared<T>(value);
		access_p = SDL_CreateMutex();
	}

	~ThreadSafeVar()
	{
		SDL_DestroyMutex(access_p);
		_value.reset();
		_value = nullptr;
	}

public:
	void setValue(std::shared_ptr<T> newValue)
	{

		SDL_LockMutex(access_p);

		_value.reset();
		_value = newValue;

		SDL_UnlockMutex(access_p);

	}

	void setValue(const T& newValue)
	{
		setValue(std::make_shared<T>(newValue));
	}

public:

	T getValue()
	{

		SDL_LockMutex(access_p);

		if (_value == nullptr)
		{
			throw OESDLModErrors::BaseError("noValueContainer");
		}
		if (_value.get() == nullptr)
		{
			throw OESDLModErrors::BaseError("NoValue");
		}


		T ret = *_value.get();

		SDL_UnlockMutex(access_p);

		return ret;
	}

	std::shared_ptr<T> getPtr()
	{

		SDL_LockMutex(access_p);

		std::shared_ptr<T> ret = _value;

		SDL_UnlockMutex(access_p);

		return ret;



	}

public:

	void clear()
	{
		SDL_LockMutex(access_p);

		_value.reset();

		SDL_UnlockMutex(access_p);

	}

	bool isEmpty()
	{

		SDL_LockMutex(access_p);

		bool ret = true;

		if (_value == nullptr)
		{
			ret = false;
		}

		SDL_UnlockMutex(access_p);
		return ret;
	}

public:

	std::shared_ptr<T> doOperation(std::function<T&(const T&)> op)
	{

		SDL_LockMutex(access_p);

		std::shared_ptr<T> ret;

		T temp = *_value->get();

		temp = op(temp);

		*(_value.get()) = temp;

		SDL_UnlockMutex(access_p);

		return ret;
	}

	void doOperation(std::function<void(T*)> op)
	{

		SDL_LockMutex(access_p);

		op(_value.get());

		SDL_UnlockMutex(access_p);

		
	}


};


#endif // !__THREAD_SAFE_VAR_H__


