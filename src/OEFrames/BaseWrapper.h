#ifndef __BASE_WRAPPER_H__
#define __BASE_WRAPPER_H__

#include <memory>

#include "BaseWindowObj.h"
#include "OEWindow.h"


class BaseWrapper : public BaseWindowObj
{
public:

	BaseWrapper() : BaseWindowObj() { _window = nullptr; }
	~BaseWrapper() { _window = nullptr; }

	


public:

	void setWindow(OEWindow* win) { _window = win; };
	virtual void insertTo(std::shared_ptr<BaseWindowObj> destinationObj) { throw FunctionNotRealised(); return; }

	virtual std::shared_ptr<BaseWindowObj> build(){ throw FunctionNotRealised(); return nullptr; }
	//virtual void insertObj(std::shared_ptr<BaseWindowObj> windowObject) { throw FunctionNotRealised(); return; }

public:

	void repaint() {}
	void update() {}

protected:

	virtual void _applyProperties() { throw FunctionNotRealised(); return; };

	OEWindow* _window;


};



#endif // !__BASE_WRAPPER_H__
