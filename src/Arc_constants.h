
#ifndef __ARC_CONSTANTS_H__
#define __ARC_CONSTANTS_H__


namespace ArcContctants
{

    //ѕараметры м€ча в пиксел€х
    static constexpr int BALL_SIZE = 20;
    static constexpr int BALL_X_POS = BALL_SIZE * 2;
    static constexpr int BALL_Y_POS = 500;

    //ѕараметры разрушаемых блоков в пиксел€х
    static const int DESTROYABLE_BOX_XSIZE = 40 * 2;
    static const int DESTROYABLE_BOX_YSIZE = 60;

    //ѕараметры платформы игрока в пиксел€х
    static const int PLATFORM_HORIZONTAL_SIZE = 160;
    static const int PLATFORM_VERTICAL_SIZE = 80;

    static constexpr int MESSAGE_FRAME_XSIZE = 350;
    static constexpr int MESSAGE_FRAME_YSIZE = 200;

    static const int WIN_WIDTH = 1200;
    static const int WIN_HEIGHT = 820;


}




#endif // !__ARC_CONSTANTS_H__



