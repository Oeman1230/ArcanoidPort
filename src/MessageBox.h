
#ifndef __MESSAGE_BOX_H__
#define __MESSAGE_BOX_H__

#include <memory>
#include <functional>


#include <OEFrame.h>
#include <OELabel.h>
#include <OEButton.h>


#include "Arc_constants.h"



class MessageBox
{
public:

	MessageBox(IWindowActions* window) : _win(window)
	{
		
		messageFrame = std::make_shared<OEFrame>(window);

		messageFrame->setBounds(ArcContctants::WIN_WIDTH / 2, ArcContctants::WIN_HEIGHT / 2,
			ArcContctants::MESSAGE_FRAME_XSIZE, ArcContctants::MESSAGE_FRAME_YSIZE);
		messageFrame->setBackground(SDLColors::WHITE);
		messageFrame->setVisible(true);
		messageFrame->setBorder(SDLColors::GRAY, 10);
		messageFrame->setBorderActive(true);


		restartButton = std::make_shared<OEButton>(_win);

		SDL_Rect buttonRect = { 20, ArcContctants::MESSAGE_FRAME_YSIZE - 100, 100, 50 };
		int fontSize = 100;
		restartButton->setBounds(buttonRect.x, buttonRect.y, buttonRect.w, buttonRect.h);

		auto unpressedTextureWrap = OELabelWrapper();
		unpressedTextureWrap.setBackground(SDLColors::PINK);
		unpressedTextureWrap.setBounds(buttonRect.x, buttonRect.y, buttonRect.w, buttonRect.h);
		unpressedTextureWrap.setFontSize(fontSize);
		unpressedTextureWrap.setTextColor(SDLColors::BLACK);
		unpressedTextureWrap.setVisible(true);
		unpressedTextureWrap.setText("UnpressedTexture");
		unpressedTextureWrap.setWindow((OEWindow*)_win);
		unpressedTextureWrap.build();

		auto pressedTextureWrap = OELabelWrapper();
		pressedTextureWrap.setBackground(SDLColors::YELLOW);
		pressedTextureWrap.setBounds(buttonRect.x, buttonRect.y, buttonRect.w, buttonRect.h);
		pressedTextureWrap.setFontSize(fontSize);
		pressedTextureWrap.setTextColor(SDLColors::BLACK);
		pressedTextureWrap.setVisible(true);
		pressedTextureWrap.setText("PressedTexture");
		pressedTextureWrap.setWindow((OEWindow*)_win);
		pressedTextureWrap.build();

		restartButton->setUnpressedButtonTexture(unpressedTextureWrap.getFrame());
		restartButton->setPressedButtonTexture(pressedTextureWrap.getFrame());


		//oewin.add(button);


	}

private:

	IWindowActions* _win;

	std::shared_ptr<OEFrame> messageFrame;



	std::shared_ptr<OELabel> textLabel;
	std::shared_ptr<OEButton> restartButton;
	std::shared_ptr<OEButton> closeGameButton;

private:

	BaseWindowObj::BaseReaction restartAction;
	void* restartCaller;



public:

	

public:

	void callToClose()
	{
		restartAction(restartCaller, 0);
	}

public:

	static void restartButtonAction(void* caller, void* arg)
	{
		MessageBox* box = (MessageBox*)caller;

		box->closeMessage();
		box->callToClose();

	}

	static void closeGameButtonAction(void* caller, void* arg)
	{
		MessageBox* box = (MessageBox*)caller;

		throw std::exception("CLOSE_PROGRAM_DONT_REALISED");

		box->closeMessage();
	}

	//void initMessageFrame(int xsize, int ysize)
	//{
	//	messageFrame = std::make_shared<OEFrame>();

	//	messageFrame->setBounds(GameWindow::WIN_WIDTH / 2, GameWindow::WIN_HEIGHT / 2,
	//		xsize, ysize);

	//	messageFrame->setVisible(false);

	//	//messageFrame->setLayout(null);

	//	textLabel = std::make_shared<OELabel>();

	//	messageFrame->add(textLabel);
	//	restartButton.setBounds(20, ysize - 100, 100, 50);
	//	restartButton.setText("Begin");

	//	restartButton.setVisible(true);

	//	
	//	//restartButton.addActionListener(action);

	//	restartButton.addActionListener(restartButtonAction, this);

	//	closeGameButton = OEButton();
	//	
	//	//messageFrame->add(closeGameButton);

	//	closeGameButton.setBounds(200, ysize - 100, 100, 50);
	//	closeGameButton.setText("Close");
	//	closeGameButton.setVisible(true);
	//	//closeGameButton.setActionListener(action);

	//}

	void riseMessage(std::string mess)
	{
		textLabel->setText(mess);
		messageFrame->setVisible(true);

	}

	void closeMessage()
	{
		messageFrame->setVisible(false);
	}



};



#endif // !__MESSAGE_BOX_H__


