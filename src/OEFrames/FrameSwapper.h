
#ifndef __FRAME_SWAPPER_H__
#define __FRAME_SWAPPER_H__

#include <exception>
#include <memory>

#include "OEFrameWrapper.h"
#include "OELabelWrapper.h"



class FrameSwapper
{
public:

	/*struct AllProperties
	{
		AllProperties(OEFrameWrapper::FrameProperties fProp = 0)

		OEFrameWrapper::FrameProperties frameProperties;
		OELabelWrapper::LabelProperties labelProperties;

	};*/

	FrameSwapper()
	{
		
	}
	~FrameSwapper()
	{
		
		_frameOne.reset();
		_frameTwo.reset();
	}

public:

	std::weak_ptr<OEFrame> getCurrentFrame() 
	{
		std::weak_ptr<OEFrame> currFrame;

		switch (_frameNum)
		{
		case 0:
		{
			currFrame = _frameOne;
			break;
		}
		case 1:
		{
			currFrame = _frameTwo;
			break;
		}
		default:
			break;
		}

		if (currFrame.expired())
		{
			throw BaseWindowObj::BaseWinObjErr("FRAME_EXPIRED");
		}

		return currFrame;
	}

	void setFirstFrame(std::shared_ptr<OEFrame> newFrame) { _frameOne = newFrame; }
	void setSecondFrame(std::shared_ptr<OEFrame> newFrame) { _frameTwo = newFrame; }

	void swap()
	{

		if (_frameNum == 0)
		{
			_frameNum = 1;
		}
		else
		{
			_frameNum = 0;
		}
	}

	void swapToFirst()
	{
		_frameNum = 0;
	}
	void swapToSecond()
	{
		_frameNum = 1;
	}

	/*void setFrameOneProperties(AllProperties newProperties);
	void setFrameTwoProperties(AllProperties newProperties);
	AllProperties getFrameOneProperties() {};*/

	std::weak_ptr<OEFrame> getOne() { return _frameOne; }
	std::weak_ptr<OEFrame> getTwo() { return _frameTwo; }

private:

	short int _frameNum = 0;

	//std::weak_ptr<OEFrame> _currentFrame;

	//AllProperties _frameOneProp;
	std::shared_ptr<OEFrame> _frameOne;

	//AllProperties _frameTwoProp;
	std::shared_ptr<OEFrame> _frameTwo;


};



#endif // !__FRAME_SWAPPER_H__

