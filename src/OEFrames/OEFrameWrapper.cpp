#include "OEFrameWrapper.h"

OEFrameWrapper::OEFrameWrapper()
{

}

OEFrameWrapper::~OEFrameWrapper()
{
	_frame.reset();
}


void OEFrameWrapper::insertTo(std::shared_ptr<BaseWindowObj> destinationObj)
{
	if (_frame != nullptr)
	{
		destinationObj->add(_frame);
		return;
	}

	destinationObj->add(build());
	
}

std::shared_ptr<BaseWindowObj> OEFrameWrapper::build()
{
	if (_window == nullptr)
	{
		throw BaseWinObjErr("NO_WINDOW");
	}

	if (_frame != nullptr)
	{
		_applyProperties();
		return std::dynamic_pointer_cast<BaseWindowObj>(_frame);
	}

	std::shared_ptr<OEFrame> tempFrame = std::make_shared<OEFrame>(_window);
	_frame = tempFrame;

	_applyProperties();


	return std::dynamic_pointer_cast<BaseWindowObj>(_frame);

}


void OEFrameWrapper::add(std::shared_ptr<BaseWindowObj> windowObject)
{
	if (_frame != nullptr)
	{
		_frame->add(windowObject);
		return;
	}

	build()->add(windowObject);

}

void OEFrameWrapper::setFrame(std::shared_ptr<OEFrame> newFrame)
{
	if (newFrame == nullptr)
	{
		throw BaseWinObjErr("NO_FRAME");
		return;
	}

	_frame.reset();
	_frame = newFrame;

	_applyProperties();


}

void OEFrameWrapper::_applyProperties()
{
	if (_frame == nullptr)
	{
		throw BaseWinObjErr("NO_FRAME");
		return;

	}

	
	_frame->setBounds(_frameProperties._onScreenPos.x, _frameProperties._onScreenPos.y, _frameProperties._width, _frameProperties._height);
	_frame->setBackground(_frameProperties._bgColor);
	_frame->setForeground(_frameProperties._fgColor);
	_frame->setVisible(this->isVisible);

}

void OEFrameWrapper::setBounds(int x, int y, int width, int height)
{
	_frameProperties._onScreenPos.x = x;
	_frameProperties._onScreenPos.y = y;
	_frameProperties._width = width;
	_frameProperties._height = height;
}
void OEFrameWrapper::setLocation(int x, int y)
{
	_frameProperties._onScreenPos.x = x;
	_frameProperties._onScreenPos.y = y;

}
void OEFrameWrapper::setBackground(Color color)
{
	_frameProperties._bgColor = color;
}
void OEFrameWrapper::setForeground(Color color)
{
	_frameProperties._fgColor = color;
}

void OEFrameWrapper::repaint()
{
	if (_frame == nullptr)
	{
		build();
	}
	_frame->repaint();

}
void OEFrameWrapper::update()
{

}