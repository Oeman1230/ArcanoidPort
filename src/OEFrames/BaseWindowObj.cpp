#include "BaseWindowObj.h"

BaseWindowObj::~BaseWindowObj()
{
	this->clear();
}

void BaseWindowObj::clear()
{
	for (auto& it : _innerWinObjects)
	{
		it->clear();
	}

	_innerWinObjects.clear();

	for (auto& it : _eventListeners)
	{
		it.listener = nullptr;
		it.reaction = nullptr;

	}

	_eventListeners.clear();

}


void BaseWindowObj::add(std::shared_ptr<BaseWindowObj> newObj)
{
	
	_innerWinObjects.push_back(newObj);

}


void BaseWindowObj::removeAll()
{
	for (auto& it : _innerWinObjects)
	{
		it.reset();
	}

	_innerWinObjects.clear();
}

void BaseWindowObj::addEventsListener(BaseReaction reaction, void* caller)
{
	BaseListener newListener;

	newListener.listener = caller;
	newListener.reaction = reaction;

	_eventListeners.push_back(newListener);

}

void BaseWindowObj::notifyEventsListeners(void* newEvent)
{

	for (auto& listenerIt : _eventListeners)
	{
		listenerIt.reaction(listenerIt.listener, newEvent);
	}

	for (auto& innerObjIt : _innerWinObjects)
	{
		innerObjIt->notifyEventsListeners(newEvent);
	}

}

void BaseWindowObj::removeAllEventsListeners()
{
	for (auto& it : _eventListeners)
	{
		it.listener = nullptr;
		it.reaction = nullptr;
	}
	_eventListeners.clear();

}



