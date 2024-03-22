
#ifndef __SDL_MONITOR_H__
#define __SDL_MONITOR_H__

#include <list>
#include <memory>
#include <chrono>
#include <thread>

#include <OESDL_Module.h>

template <class T>
class SDLMonitor
{
private:

	std::list<std::shared_ptr<T>> container;
	SDL_mutex* access_p;
	SDL_semaphore* freeCount_sem_p;
	SDL_semaphore* elementsCount_sem_p;

	Uint32 contSize;

	int WAITING_TIME_COUNT = 4;
	std::chrono::milliseconds WAIT_FOR_MILLS = std::chrono::milliseconds(100);
public:

	SDLMonitor(Uint32 monitorSize = 1) : contSize(monitorSize)
	{
		access_p = SDL_CreateMutex();
		freeCount_sem_p = SDL_CreateSemaphore(contSize);
		elementsCount_sem_p = SDL_CreateSemaphore(0);

		
	}

	void push(std::shared_ptr<T> item)
	{

		SDL_SemWait(freeCount_sem_p);

		SDL_LockMutex(access_p);

		container.push_back(item);

		SDL_SemPost(elementsCount_sem_p);

		SDL_UnlockMutex(access_p);



	}

	std::shared_ptr<T> pop(bool needToWait = true)
	{

		int waitResult = 0;

		waitResult = SDL_SemTryWait(elementsCount_sem_p);


		if (waitResult != 0)
		{
			if (needToWait == false)
			{
				return nullptr;
			}
			else
			{
				SDL_SemWait(elementsCount_sem_p);
			}

		}


		SDL_LockMutex(access_p);

		std::shared_ptr<T> ret = nullptr;

		if (container.size() != 0)
		{
			ret = container.front();
			container.pop_front();
			SDL_SemPost(freeCount_sem_p);
		}
		else
		{
			SDL_SemPost(elementsCount_sem_p);
		}


		SDL_UnlockMutex(access_p);

		return ret;

	}

	std::weak_ptr<T> readFront()
	{
		int tryLock = 0;
		tryLock = SDL_TryLockMutex(access_p);

		if (tryLock != 0)
		{
			return std::weak_ptr<T>();
		}
		
		std::weak_ptr<T> ret = std::weak_ptr<T>();

		if (container.size() != 0)
		{
			ret = container.front();
		}

		SDL_UnlockMutex(access_p);

		return ret;
	}

	void clear()
	{

		SDL_LockMutex(access_p);

		while (SDL_SemTryWait(elementsCount_sem_p) == 0)
		{
			SDL_SemPost(freeCount_sem_p);
			container.pop_front();

		}

		while (SDL_SemValue(freeCount_sem_p) > contSize)
		{
			SDL_SemWait(freeCount_sem_p);
		}

		//int free = SDL_SemValue(freeCount_sem_p);
		//int elem = SDL_SemValue(elementsCount_sem_p);

		SDL_UnlockMutex(access_p);


	}


	~SDLMonitor(){}

};



#endif // !__SDL_MONITOR_H__


