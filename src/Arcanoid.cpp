#include <thread>

#include "Arcanoid.h"
#include "DestroyableBox.h"

Arcanoid::Arcanoid() //: messageFrame(restartGameCB, this)
{

	initWindow();
	obstacles = std::vector<std::shared_ptr<Hitbox>>();

	initObstacles();
	initPlatform();

	initBall();

	initCallbacks();

}

void Arcanoid::initBall()
{
	

	ball.setBall( Ball(MathVector(GameWindow::BG_WIDTH / 2 + PLATFORM_HORIZONTAL_SIZE/2, GameWindow::BG_HEIGHT - 2 * Arcanoid::BALL_SIZE - 1),
		MathVector(0,0)));

	playground->add(ball.createBall(&win, ballColor, BALL_SIZE));
}

MathVector Arcanoid::_calcRelativePositionInPlayground(int x, int y)
{
	auto sizes = playground->getSizes();

	return MathVector(sizes.x + x, sizes.y + y);

}

void Arcanoid::initPlatform()
{
	platformAcceptablePos.setHitbox(Hitbox("AcceptablePos"));
	platformAcceptablePos.setPos(_calcRelativePositionInPlayground(Arcanoid::ACPOS_X, Arcanoid::ACPOS_Y));
	platformAcceptablePos.setXLength(Arcanoid::ACPOS_XLen);
	platformAcceptablePos.setYLength(Arcanoid::ACPOS_YLen);

	ACC_POS_texture = std::make_shared<OEFrame>(&win);

	auto tempPos = _calcRelativePositionInPlayground(Arcanoid::ACPOS_X, Arcanoid::ACPOS_Y);

	ACC_POS_texture->setBounds(tempPos.X(), tempPos.Y(), GameWindow::BG_WIDTH, Arcanoid::ACPOS_YLen);
	ACC_POS_texture->setBackground(SDLColors::TRANSPARENT);

	ACC_POS_texture->setBorder(ACC_POS_border_color, ACC_POS_border_thickness);
	ACC_POS_texture->setBorderActive(true);

	ACC_POS_texture->setVisible(true);
	playground->add(ACC_POS_texture);


	platform = std::make_shared<PlayerPlatform>(platformAcceptablePos);

	platform->setPos(MathVector(GameWindow::BG_WIDTH / 2,
		GameWindow::BG_HEIGHT - Arcanoid::BALL_SIZE));
	platform->setXLength(PLATFORM_HORIZONTAL_SIZE);
	platform->setYLength(PLATFORM_VERTICAL_SIZE);

	playground->add(platform->createPlatform(&win, PLATFORM_HORIZONTAL_SIZE, BALL_SIZE / 2));

	std::shared_ptr<Hitbox> tempPlatform = std::static_pointer_cast<Hitbox>(platform);

	obstacles.push_back(platform);



}

void Arcanoid::initObstacles()
{
	std::shared_ptr<Hitbox> leftWall = std::make_shared<Hitbox>("leftWall");
	leftWall->setPos(_calcRelativePositionInPlayground(-BALL_SIZE * 2, 0));
	leftWall->setXLength(BALL_SIZE * 2);
	leftWall->setYLength(GameWindow::BG_HEIGHT);

	std::shared_ptr<Hitbox> rightWall = std::make_shared<Hitbox>("rightWall");
	rightWall->setPos(_calcRelativePositionInPlayground(GameWindow::BG_WIDTH, 0));
	rightWall->setXLength(BALL_SIZE * 2);
	rightWall->setYLength(GameWindow::BG_HEIGHT);



	//Создание верхней границы игрового поля
	std::shared_ptr<Hitbox> upWall = std::make_shared<Hitbox>("upWall");
	upWall->setPos(_calcRelativePositionInPlayground(0, -BALL_SIZE * 2));
	upWall->setXLength(GameWindow::BG_WIDTH);
	upWall->setYLength(BALL_SIZE * 2);

	//Создание поля окончания игры
	gameOverBox = std::make_shared<Hitbox>("GameOverBox");
	gameOverBox->setPos(_calcRelativePositionInPlayground(0, GameWindow::BG_HEIGHT));
	gameOverBox->setXLength(GameWindow::BG_WIDTH);
	gameOverBox->setYLength(BALL_SIZE * 2);

	obstacles.push_back(leftWall);
	obstacles.push_back(rightWall);
	obstacles.push_back(upWall);


	DBoxesBuilder Dbuilder = DBoxesBuilder(&win, &obstacles);

	Dbuilder.setXLen(DESTROYABLE_BOX_XSIZE);
	Dbuilder.setYLen(DESTROYABLE_BOX_YSIZE);


	for (int i = 0; i < 10; i++)
	{
		auto recalcPos = _calcRelativePositionInPlayground(i * Dbuilder.XLen, 0);

		std::shared_ptr<OEFrame> tempBox = Dbuilder.createBox(recalcPos.X(), recalcPos.Y());
		playground->add(tempBox);
	}
	for (int i = 0; i < 10; i++)
	{
		auto recalcPos = _calcRelativePositionInPlayground(i * Dbuilder.XLen, Dbuilder.YLen);

		std::shared_ptr<OEFrame> tempBox = Dbuilder.createBox(recalcPos.X(), recalcPos.Y());
		playground->add(tempBox);
	}
	for (int i = 0; i < 10; i++)
	{
		auto recalcPos = _calcRelativePositionInPlayground(i * Dbuilder.XLen, 2 * Dbuilder.YLen);

		std::shared_ptr<OEFrame> tempBox = Dbuilder.createBox(recalcPos.X(), recalcPos.Y());
		playground->add(tempBox);
	}





}

void Arcanoid::initCallbacks()
{

	playground->addEventsListener([&](void* caller, void* arg)
		{
			SDL_Event* e = (SDL_Event*)arg;

			PlayerPlatform* platform = (PlayerPlatform*)caller;

			if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_a)
			{
				platform->getVelocityPtr()->setX(
					-std::abs(ballStartVelosity.X() * 2));
			}

			if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_d)
			{
				platform->getVelocityPtr()->setX(
					std::abs(ballStartVelosity.X() * 2));
			}

			if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_w)
			{
				platform->getVelocityPtr()->setY(
					-std::abs(ballStartVelosity.Y() / 2));
			}

			if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_s)
			{
				platform->getVelocityPtr()->setY(
					std::abs(ballStartVelosity.Y() / 2));
			}

		}, platform.get());

	playground->addEventsListener([&](void* caller, void* arg)
		{
			SDL_Event* e = (SDL_Event*)arg;


			PlayerPlatform* platform = (PlayerPlatform*)caller;

			if (e->type == SDL_KEYUP && (e->key.keysym.sym == SDLK_a || e->key.keysym.sym == SDLK_d))
			{
				platform->getVelocityPtr()->setX(0);
			}

			if (e->type == SDL_KEYUP && (e->key.keysym.sym == SDLK_w || e->key.keysym.sym == SDLK_s))
			{
				platform->getVelocityPtr()->setY(0);
			}

		}, platform.get());

	playground->addEventsListener([&](void* caller, void* arg)
		{
			SDL_Event* e = (SDL_Event*)arg;

			if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_r)
			{
				isGameStarted = false;
				isGameOver = false;
				restartGame();
			}

			if (!isGameStarted == true && e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_SPACE)
			{
				isGameStarted = true;
				ball.setVelocity(ballStartVelosity);
			}

		}, &win);
}

void Arcanoid::keyboardSignalHandler(int keyNum)
{
	
}

void Arcanoid::keyboardKeyReleasedHandler(int keyNum)
{
	if (keyNum == KEYS::A || keyNum == KEYS::D)
	{
		platform->getVelocityPtr()->setX(0);
	}

	if (keyNum == KEYS::W || keyNum == KEYS::S)
	{
		platform->getVelocityPtr()->setY(0);
	}


}

void Arcanoid::initWindow()
{
	//frame = OEFrame("Arcanoid");
	//win = GameWindow();
	playground = win.initBackground();

	//frame.addKeyListener(keyboardSignalHandlerCB, this);

	

	//frame.addKeyListener(keyboardKeyReleasedHandlerCB, this);

	


	

	/*frame.setVisible(true);
	frame.setBounds(win.WIN_ON_SCREEN_POS.x, win.WIN_ON_SCREEN_POS.y,
		win.WIN_WIDTH, win.WIN_HEIGHT);*/
	
	//frame.setLayout(null);
	//frame.setDefaultCloseOperation(EXIT_ON_CLOSE);

}

void Arcanoid::doGameBeginingLoop()
{
	MathVector startBallPos = 
		MathVector(platform->getPos().X() + platform->getXLength()/2,
		platform->getPos().Y() - BALL_SIZE - 1);

	ball.setPosition(startBallPos);

	platform->update();
	ball.update();
	
	win.repaint();

	std::chrono::milliseconds timeSleep(20);
	std::this_thread::sleep_for(timeSleep);

}

void Arcanoid::checkForGameEnd()
{
	bool result = true;

	//auto it = obstacles.begin();

	//while(it != obstacles.end())
	for(auto it : obstacles)
	{
		std::shared_ptr<DestroyableBox> box;

		try
		{
			box = std::dynamic_pointer_cast<DestroyableBox>(it);

			if (box == nullptr)
			{
				continue;
			}

		}
		catch (std::exception e)
		{	
			continue;
		}

		if (box->isBroken())
		{
			continue;
		}

		if (box->isBroken() == false)
		{
			result = false;
			break;
		}
	}

	if (result == true)
	{
		isGameOver = true;
		//messageFrame.riseMessage(winningMessage);
	}
}

void Arcanoid::doGameLoop()
{
	for (auto itBox : obstacles)
	{
		if (itBox != nullptr)
		{
			itBox->ballColisionDetection(ball);
		}
	}

	ball.update();
	platform->update();

	if (gameOverBox->isContains(ball.getPosition()) == true)
	{
		isGameOver = true;
		//messageFrame.riseMessage(loseMessage);
	}

	checkForGameEnd();

	win.repaint();

	std::chrono::milliseconds timeSleep(20);
	std::this_thread::sleep_for(timeSleep);

}

void Arcanoid::restartGame()
{
	isGameStarted = false;
	isGameOver = false;

	obstacles.clear();
	playground->removeAll();
	playground->removeAllEventsListeners();

	initObstacles();
	initPlatform();
	initBall();

	initCallbacks();

	/*frame.repaint();*/

}

void Arcanoid::startGame()
{


	win.repaint();
	
	
	SDL_ShowWindow(win.getWinDescr());

	win.setActive(true);

	//isActive.setValue(true);

	try
	{
		while (win.getActivityStatus() == true)
		{

			SDL_Event e;

			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					win.setActive(false);
					break;
				}

				win.getClickManager()->handleClick(&e);

				win.notifyEventsListeners((void*)(&e));

			}

			if (isGameStarted == false)
			{
				doGameBeginingLoop();
				continue;
			}

			if (isGameOver != true)
			{
				doGameLoop();
				continue;

			}

			//platform->update();
			

			win.repaint();
			std::chrono::milliseconds timeSleep(10);
			std::this_thread::sleep_for(timeSleep);

		}
	}
	catch (...)
	{

	}

	



}