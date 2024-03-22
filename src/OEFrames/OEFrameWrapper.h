#ifndef __OEFRAME_WRAPPER_H__
#define __OEFRAME_WRAPPER_H__

#include <memory>

#include "SDLColors.h"
#include "BaseWindowObj.h"
#include "BaseWrapper.h"
#include "OEFrame.h"
#include "OEWindow.h"


class OEFrameWrapper : public BaseWrapper
{
public:

	OEFrameWrapper();
	~OEFrameWrapper();

	//properties
	// 
	struct FrameProperties{
		std::string _pathToTexture;
		SDL_Point _onScreenPos = { 0,0 };
		int _width = 0;
		int _height = 0;
		SDL_Color _bgColor = SDLColors::TRANSPARENT;
		SDL_Color _fgColor = SDLColors::TRANSPARENT;
	} ;

private:

	std::shared_ptr<OEFrame> _frame;

public:

	std::shared_ptr<OEFrame> getFrame() { return _frame; }
	virtual void setFrame(std::shared_ptr<OEFrame> newFrame);

	void insertTo(std::shared_ptr<BaseWindowObj>);

	std::shared_ptr<BaseWindowObj> build();
	void add(std::shared_ptr<BaseWindowObj> windowObject) override;
	
public:

	void setBounds(int x, int y, int width, int height);
	void setLocation(int x, int y);
	void setBackground(Color color);
	void setForeground(Color color);

public:

	void repaint();
	void update();

protected:

	FrameProperties _frameProperties;

	void _setFrame(std::shared_ptr<OEFrame> frame) { _frame = frame; }
	void _applyProperties();


	

};



#endif // !__OEFRAME_WRAPPER_H__
