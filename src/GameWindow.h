
#ifndef __GAME_WINDOW_H__
#define __GAME_WINDOW_H__

#include <memory>

#include "Arcanoid.h"
#include "OEUtilities/OEVectorMathTemplate.h"

#include <OEFrame.h>
#include <OEWindow.h>



class GameWindow : public OEWindow
{
public:

	GameWindow() : OEWindow()
	{
		this->setWinName("win");
		this->setBounds(WIN_ON_SCREEN_POS.X(), WIN_ON_SCREEN_POS.Y(),
			WIN_WIDTH, WIN_HEIGHT);
	
		this->makeWindow();

		this->setBackground(SDLColors::WHITE);
		


		this->setVisible(true);
		
	}
	~GameWindow() { ; }

public:

	static const int WIN_WIDTH = 1200;
	static const int WIN_HEIGHT = 820;
	
	static const int BG_WIDTH = 800;
	static const int BG_HEIGHT = 700;

	Color backgroundColor = SDLColors::BLACK;

public:

	Vector2D<int> WIN_ON_SCREEN_POS = Vector2D<int>(40, 40);
	Vector2D<int> BG_ON_FRAME_POS = Vector2D<int>(WIN_WIDTH / 6, 10);

private:

	//std::shared_ptr<OEFrame> background;

public:


	/*GameWindow& operator=(GameWindow win)
	{
		*this = win;
		return *this;
	}*/

	
	//std::shared_ptr<OEFrame> getBG() { return background; }
	
	std::shared_ptr<OEFrame> initBackground()
	{


		auto background = std::make_shared<OEFrame>(this);
		
		
		background->setBounds(BG_ON_FRAME_POS.X(), BG_ON_FRAME_POS.Y(),
			BG_WIDTH, BG_HEIGHT);

		background->setBackground(backgroundColor);
		background->setForeground(backgroundColor);

		background->setVisible(true);

		this->add(background);
		return background;


	}



};



#endif // !__GAME_WINDOW_H__



