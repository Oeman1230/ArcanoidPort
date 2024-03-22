#include "OELabelWrapper.h"


OELabelWrapper::OELabelWrapper()
{

}


OELabelWrapper::~OELabelWrapper()
{
	_labelProperties._labelFont = nullptr;
	_labelProperties._labelText.clear();
}

void OELabelWrapper::setFont(std::string fondDest)
{
	_labelProperties._fontPath = fondDest;
}

void OELabelWrapper::setText(std::string newText)
{
	_labelProperties._labelText = newText;
}

void OELabelWrapper::setFontSize(int fontSize)
{
	_labelProperties._fontSize = fontSize;
}

void OELabelWrapper::setTextColor(Color color)
{
	_labelProperties._textColor = color;
}

void OELabelWrapper::_applyProperties()
{
	std::shared_ptr<OELabel> tempLabel = std::dynamic_pointer_cast<OELabel>(getFrame());

	if (tempLabel == nullptr)
	{
		throw BaseWinObjErr("NO_LABEL");
		return;
	}

	
	
	tempLabel->setVisible(this->isVisible);
	tempLabel->setBounds(_frameProperties._onScreenPos.x, _frameProperties._onScreenPos.y, _frameProperties._width, _frameProperties._height);
	tempLabel->setFontSize(_labelProperties._fontSize);
	tempLabel->setBackground(_frameProperties._bgColor);
	tempLabel->setTextColor(_labelProperties._textColor);

	tempLabel->setFont(_labelProperties._fontPath);
	tempLabel->setText(_labelProperties._labelText);


}

void OELabelWrapper::setFrame(std::shared_ptr<OEFrame> newFrame)
{
	if (newFrame == nullptr)
	{
		throw BaseWinObjErr("NO_FRAME");
	}

	_setFrame(newFrame);
	_applyProperties();


}

std::shared_ptr<BaseWindowObj> OELabelWrapper::build()
{
	if (_window == nullptr)
	{
		throw BaseWinObjErr("NO_WINDOW");
	}


	std::shared_ptr<OEFrame> tempFrame = getFrame();

	if (tempFrame != nullptr)
	{
		_applyProperties();
		return std::dynamic_pointer_cast<BaseWindowObj>(tempFrame);
	}

	std::shared_ptr<OELabel> tempLabel = std::make_shared<OELabel>(_window);
	_setFrame(std::dynamic_pointer_cast<OEFrame>(tempLabel));


	_applyProperties();


	return std::dynamic_pointer_cast<BaseWindowObj>(tempLabel);

}
