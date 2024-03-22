
#ifndef __ARCANOID_H__
#define __ARCANOID_H__



#include "OEUtilities/OEVectorMathTemplate.h"

//#include "OELabel.h"

#include <string>
#include <vector>
#include <memory>

#include "Hitbox.h"
#include "GameWindow.h"
#include "PlayerPlatform.h"
#include "Ball.h"

//#include "MessageBox.h"

//typedef int Hitbox;
//typedef int JLabel;
//typedef int GameWindow;
//typedef int PlayerPlatform;
//typedef int JFrame;
//typedef int Ball;

#include <BaseWindowObj.h>
#include <OEWindow.h>
#include <OEFrame.h>

class Arcanoid
{

public:

	Arcanoid();
    ~Arcanoid() {};

    void initBall();
    void initPlatform();
    void initObstacles();
    void initWindow();
    void doGameBeginingLoop();
    void checkForGameEnd();
    void doGameLoop();
    void restartGame();
    void startGame();

public:

    static void restartGameCB(void* caller, void* arg)
    {
        Arcanoid* arcan = (Arcanoid*)caller;
        arcan->restartGame();
    }

private:

    GameWindow win;
    Ball ball;
    std::vector<std::shared_ptr<Hitbox>> obstacles;
    std::shared_ptr<PlayerPlatform> platform;

    std::shared_ptr<OEFrame> playground;

    //OEFrame frame;

    //MessageBox messageFrame;

    //Поле окончания игры. При попадании мяча в это поле игрок проигрывает
    std::shared_ptr<Hitbox> gameOverBox;


public:


    static constexpr int MESSAGE_FRAME_XSIZE = 350;
    static constexpr int MESSAGE_FRAME_YSIZE = 200;

    const std::string winningMessage = "Поздравляю! Вы победили";
    const std::string loseMessage = "Извините. Вы проиграли. Попробуйте снова!";


public:

    //Параметры мяча в пикселях
    static constexpr int BALL_SIZE = 20 ;
    static constexpr int BALL_X_POS = BALL_SIZE * 2;
    static constexpr int BALL_Y_POS = 500;

    SDL_Color ballColor = SDLColors::WHITE;

    //Параметры разрушаемых блоков в пикселях
    static const int DESTROYABLE_BOX_XSIZE = 40 * 2;
    static const int DESTROYABLE_BOX_YSIZE = 60;

    //Параметры платформы игрока в пикселях
    static const int PLATFORM_HORIZONTAL_SIZE = 160;
    static const int PLATFORM_VERTICAL_SIZE = 80;

private:

    

    //Переменные состояния игры
    bool isGameStarted = false;
    bool isProgramActive = true;
    bool isGameOver = false;

    //Параметры допустимого для перемещения платформы поля
    Hitbox platformAcceptablePos;
    std::shared_ptr<OEFrame> ACC_POS_texture;

    SDL_Color ACC_POS_border_color = SDLColors::ORANGE;
    int ACC_POS_border_thickness = 2;

   

public:

    ///Позиция левого верхнего угла в координатах окна
    static constexpr int ACPOS_X = 0;
    static constexpr int ACPOS_Y = GameWindow::BG_HEIGHT - PLATFORM_VERTICAL_SIZE * 2;

    //Размер по горизонтали
    static constexpr int ACPOS_XLen = GameWindow::BG_WIDTH - PLATFORM_HORIZONTAL_SIZE;

    //Размер по вертикали
    static constexpr int ACPOS_YLen = PLATFORM_VERTICAL_SIZE * 2 - (BALL_SIZE / 2);

    //Вектор стартовой скорости мячика
    MathVector ballStartVelosity = MathVector(10, -10);

public:

    struct KEYS
    {
        static const int A = 65;
        static const int D = 68;
        static const int W = 87;
        static const int S = 83;

        static const int R = 82;
        static const int ESC = 27;
        static const int SPACE = 65;

    };

    
public:
    
    void initCallbacks();

    void keyboardSignalHandler(int keyNum);

    static void keyboardSignalHandlerCB(void* caller, void* arg)
    {
        Arcanoid* thisArc = (Arcanoid*)caller;
        thisArc->keyboardSignalHandler(*(int*)(arg));
    }

    void keyboardKeyReleasedHandler(int keyNum);

    static void keyboardKeyReleasedHandlerCB(void* caller, void* arg)
    {
        Arcanoid* thisArc = (Arcanoid*)caller;
        thisArc->keyboardKeyReleasedHandler(*(int*)(arg));
    }

private:
    MathVector _calcRelativePositionInPlayground(int x, int y);

};



#endif // !__ARCANOID_H_



