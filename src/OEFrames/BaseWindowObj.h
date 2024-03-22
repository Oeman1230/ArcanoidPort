
#ifndef __BASE_WINDOW_OBJECT_H__
#define __BASE_WINDOW_OBJECT_H__

#include <exception>
#include <iostream>
#include <memory>
#include <functional>
#include <vector>

//add in project additional includes (include OESDL_Module/.)
#include <OESDL_Module.h>



class BaseWindowObj
{
public:

	BaseWindowObj() : isVisible(false), isActive(true){}
	virtual ~BaseWindowObj();

	virtual void clear();

public:

	typedef SDL_Color Color;
	typedef std::function<void(void*, void*)> BaseReaction;
	typedef std::weak_ptr<BaseWindowObj> weak_ptr;

	struct BaseWinObjErr
	{
		std::string body;

		BaseWinObjErr(std::string errText) : body(errText) {};
	};

	struct FunctionNotRealised : BaseWinObjErr { FunctionNotRealised() : BaseWinObjErr("Function_not_realised") {}; };
	struct OldRealisation : BaseWinObjErr { OldRealisation() : BaseWinObjErr("Old_realisation_use") {}; };

public:

	virtual void setBounds(int x, int y, int width, int height) { throw FunctionNotRealised(); }
	virtual void setLocation(int x, int y) { throw FunctionNotRealised(); }
	virtual void setBorder(Color color, int thickness) { throw FunctionNotRealised(); }
	virtual void setBorderActive(bool status) { throw FunctionNotRealised(); };

	virtual SDL_Rect getSizes() { throw FunctionNotRealised(); }

public:
	 

	virtual void setBackground(Color color) { throw FunctionNotRealised(); }
	virtual void setForeground(Color color) { throw FunctionNotRealised(); }

	virtual void setVisible(bool status) { isVisible = status; }
	virtual void setText(std::string text) { throw FunctionNotRealised(); }

	virtual void setActive(bool status) { isActive = status; }
	

public:

	virtual bool getVisibilityStatus() { return isVisible; }
	virtual bool getActivityStatus() { return isActive; }

public:

	virtual void add(std::shared_ptr<BaseWindowObj> inpObject);
	virtual void removeAll();

	virtual void repaint() { throw FunctionNotRealised(); }
	virtual void update() {}

public:

	virtual void addKeyListener(BaseReaction func, void* caller) { throw FunctionNotRealised(); }

public:
	
	struct BaseListener
	{
		BaseReaction reaction;
		void* listener;
	};

	virtual void removeAllEventsListeners();

	//	void* caller, void* arg
	virtual void addEventsListener(BaseReaction func, void* caller);
	virtual void notifyEventsListeners(void* keyEvent);

protected:

	bool isActive;
	bool isVisible;

protected:

	std::vector<std::shared_ptr<BaseWindowObj>> _innerWinObjects;
	std::vector<BaseListener> _eventListeners;




	/*Reaction keyAction;
	void* keyListener;

	Reaction onEventAction;
	void* actionListener;*/

};



#endif // !__BASE_WINDOW_OBJECT_H__


