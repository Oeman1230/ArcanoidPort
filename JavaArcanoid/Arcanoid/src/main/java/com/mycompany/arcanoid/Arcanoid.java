/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */

package com.mycompany.arcanoid;

import java.util.ArrayList;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import static javax.swing.WindowConstants.EXIT_ON_CLOSE;
/**
 *
 * @author Yury
 */
public class Arcanoid {
    
    private GameWindow win;
    private Ball ball;
    private ArrayList<Hitbox> obstacles;
    private PlayerPlatform platform;
    private JFrame frame;
    
    
    private static final Integer MESSAGE_FRAME_XSIZE = 350;
    private static final Integer MESSAGE_FRAME_YSIZE = 200;
    
    private final String winningMessage = "Поздравляю! Вы победили";
    private final String loseMessage = "Извините. Вы проиграли. Попробоуйте снова!";
    
    /*
        Класс всплывающего окна с сообщением.
        Данный класс содержит тектовое поле и две кнопки перезапуска игры и
        закрытия всех окон
    */
    public class MessageBox
    {
        private JFrame messageFrame;
        
        private JLabel textLabel;
        
        private JButton restartButton;
        private JButton closeGameButton;
        
        private void initMessageFrame()
    {
        //Создание объекта окра сообщений
        messageFrame = new JFrame();
        messageFrame.setBounds(GameWindow.WIN_WIDTH/2, GameWindow.WIN_HEIGHT/2,
                MESSAGE_FRAME_XSIZE, MESSAGE_FRAME_YSIZE);
        messageFrame.setLayout(null);

        //Создание текстового поля
        textLabel = new JLabel();
        messageFrame.add(textLabel);
        textLabel.setBounds(30, 0, MESSAGE_FRAME_XSIZE, 50);
        textLabel.setVisible(true);
        
        //Создание кнопки перезапуска игры
        restartButton = new JButton();
        messageFrame.add(restartButton);
        restartButton.setBounds(20, MESSAGE_FRAME_YSIZE - 100, 100, 50);
        restartButton.setVisible(true);
        restartButton.setText("Заново");
        //Вызов перезапуска игры при  нажатии на кнопку
        restartButton.addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent evt)
                    {
                        closeMessage();
                        restartGame();
                    }
                });
        
        //Создание кнопки закрытия всего приложения
        closeGameButton = new JButton();
        messageFrame.add(closeGameButton);
        closeGameButton.setBounds(200, MESSAGE_FRAME_YSIZE - 100, 100, 50);
        closeGameButton.setVisible(true);
        closeGameButton.setText("Выйти");
        //Выхов завершения работы всего приложения при нажатии на кнопку
        closeGameButton.addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent evt)
                    {
                        closeMessage();
                        isProgramActive = false;
                        
                        messageFrame.dispatchEvent(new WindowEvent(messageFrame, WindowEvent.WINDOW_CLOSING));
                        
                    }
                });
    }
        
        /*
            Вызов окна с сообщением на экран.
            Функция принимает текстовое сообщение - mess 
        */
        public void riseMessage(String mess)
        {
            textLabel.setText(mess);
            messageFrame.setVisible(true);
        }
        
        /*
            Скрывает окно с сообщением на экране.
        */
        public void closeMessage()
        {
            messageFrame.setVisible(false);
            
        }
        
        
        
    }
    
    private MessageBox messageFrame = new MessageBox();

    public Arcanoid()
    {

        initWindow();
        //Массив всех потенциальных препятвий мяча на поле
        obstacles = new ArrayList<>(); 

        initObstacles();
        initPlatform();
        initBall();
        
        messageFrame.initMessageFrame();
        
    }
    
    //Параметры мяча в пикселях
    public static final int BALL_SIZE = 20;
    public static final int BALL_X_POS = BALL_SIZE*2;
    public static final int BALL_Y_POS = 500;
    
    //Параметры разрушаемых блоков в пикселях
    public static final int DESTROYABLE_BOX_XSIZE = 40*2;
    public static final int DESTROYABLE_BOX_YSIZE = 60;
    
    //Параметры платформы игрока в пикселях
    public static final Integer PLATFORM_HORIZONTAL_SIZE = 160;
    public static final Integer PLATFORM_VERTICAL_SIZE = 80;
    
    //Переменные состояния игры
    private boolean isGameStarted = false; 
    private boolean isProgramActive = true;
    private boolean isGameOver = false;
    
    //Параметры допустимого для перемещения платформы поля
    private Hitbox platformAcceptablePos; 
    JLabel ACC_POS_texture;
    
    ///Позиция левого верхнего угла в координатах окна
    private static final Integer ACPOS_X = 0;                                                  
    private static final Integer ACPOS_Y = GameWindow.BG_HEIGHT - PLATFORM_VERTICAL_SIZE*2;   
    
    //Размер по горизонтали
    private static final Integer ACPOS_XLen = GameWindow.BG_WIDTH - PLATFORM_HORIZONTAL_SIZE;
    
    //Размер по вертикали
    private static final Integer ACPOS_YLen = PLATFORM_VERTICAL_SIZE*2 - (BALL_SIZE/2);         
    
    //Вектор стартовой скорости мячика
    private final MathVector ballStartVelosity = new MathVector(10,-10);
    
    /*
        Инициализирует двигающийся мяч
    */
    private void initBall()
    {
        
        ball = new Ball(new MathVector(GameWindow.BG_WIDTH/2, GameWindow.BG_HEIGHT - 2*BALL_SIZE - 1), new MathVector(0,0),
        GameWindow.BG_HEIGHT);
        
        
        win.getBG().add(ball.createBall(Color.WHITE, BALL_SIZE));
    }
    
    /*
        Инициализирует платформу игрока и допустимое для перемещения поле.
        Создаёт объекты платформы и допустимого поля.
    */
    private void initPlatform()
    {
        //Создание объекта поля допустимого расположения платформы игрока
        platformAcceptablePos = new Hitbox("acceptablePos");
        platformAcceptablePos.setPos(new MathVector(ACPOS_X, ACPOS_Y));
        platformAcceptablePos.setXLength(ACPOS_XLen);
        platformAcceptablePos.setYLength(ACPOS_YLen);
        
        //Создание текстуры поля допустимого местоположения платформы
        ACC_POS_texture = new JLabel();
        ACC_POS_texture.setBorder(BorderFactory.createLineBorder(Color.YELLOW, 2));
        ACC_POS_texture.setBounds(ACPOS_X, ACPOS_Y, GameWindow.BG_WIDTH, ACPOS_YLen);
        
        ACC_POS_texture.setVisible(true);
        win.getBG().add(ACC_POS_texture);
        win.repaint();
        
        //Создание объекта платформы игрока
        platform = new PlayerPlatform(platformAcceptablePos);
        
        platform.setPos(new MathVector(GameWindow.BG_WIDTH/2, GameWindow.BG_HEIGHT - BALL_SIZE));
        platform.setXLength(PLATFORM_HORIZONTAL_SIZE);
        platform.setYLength(PLATFORM_VERTICAL_SIZE);

        win.getBG().add(platform.createPlatforn(PLATFORM_HORIZONTAL_SIZE, BALL_SIZE/2));
        
        obstacles.add(platform); //добавление платформы в массив препятствий 
        
    }
    
    //Поле окончания игры. При попадании мяча в это поле игрок проигрывает
    private Hitbox gameOverBox;
    
    
    /*
        Инициализирует все возможные препрядствия в игре.
        создаёт объекты стен и разрушаемых блоков и заполняет окно игры
    
    */
    private void initObstacles()
    {
        //Создание левой стены
        Hitbox leftWall = new Hitbox("leftWall");
        leftWall.setPos(new MathVector(-BALL_SIZE*2,0));
        leftWall.setXLength(BALL_SIZE*2);
        leftWall.setYLength(GameWindow.BG_HEIGHT);
        
        //Создание правой стены
        Hitbox rightWall = new Hitbox("rightWall");
        rightWall.setPos(new MathVector(GameWindow.BG_WIDTH,0));
        rightWall.setXLength(BALL_SIZE*2);
        rightWall.setYLength(GameWindow.BG_HEIGHT);
        
        //Создание верхней границы игрового поля
        Hitbox upWall = new Hitbox("upWall");
        upWall.setPos(new MathVector(0,-BALL_SIZE*2));
        upWall.setXLength(GameWindow.BG_WIDTH);
        upWall.setYLength(BALL_SIZE*2);
        
        //Создание поля окончания игры
        gameOverBox = new Hitbox("GameOverBox");
        gameOverBox.setPos(new MathVector(0,GameWindow.BG_HEIGHT));
        gameOverBox.setXLength(GameWindow.BG_WIDTH);
        gameOverBox.setYLength(BALL_SIZE*2);
        
        //Добавление объектов в массив препятствий
        obstacles.add(leftWall);
        obstacles.add(rightWall);
        obstacles.add(upWall);
        
        //Создание конструктора типовых разрушаемых блоков
        DestroyableBox.DBoxesBuilder Dbuilder = new DestroyableBox.DBoxesBuilder(obstacles);
        
        Dbuilder.setXLen(DESTROYABLE_BOX_XSIZE);
        Dbuilder.setYLen(DESTROYABLE_BOX_YSIZE);
        
        //Создание трех рядов разрушаемых блоков и добавление в массив препятствий
        for(int i = 0; i < 10; i++)
        {
            JLabel tempBox = Dbuilder.createBox(i*Dbuilder.XLen,0);  
            win.getBG().add(tempBox);
        }
        for(int i = 0; i < 10; i++)
        {
            win.getBG().add(Dbuilder.createBox(i*Dbuilder.XLen,Dbuilder.YLen));    
        }
        for(int i = 0; i < 10; i++)
        {
            win.getBG().add(Dbuilder.createBox(i*Dbuilder.XLen,2* Dbuilder.YLen));
        }
        
        win.repaint();
         
    }
    
    /*
        Инициализирует объекты окна и обработчиков нажатия клавиш
    */
    private void initWindow()
    {
        //Создание окна приложения
        frame = new JFrame("Arcanoid");
        win = new GameWindow();
        
        //Инициализация обработчика сигналов с клавиаьтуры
        frame.addKeyListener( new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent evt)
                {    
                    if(evt.getKeyCode() == 82)
                    {
                        isGameStarted = false;
                        isGameOver = false;    
                        restartGame();
                        
                    }
                    //Коды клавиш
                    //A = 65; D = 68
                    //W = 87; S = 83
                    //Esc = 27
                    //space = 32
                    //R = 82
                    
                    if(evt.getKeyCode() == 65)
                    {
                        //Движение платформы влево
                        platform.getVelosity().setX(- Math.abs(ballStartVelosity.getX()*2));
                    }
                    else if(evt.getKeyCode() == 68)
                    {
                        //движение платформы вправо
                        platform.getVelosity().setX(Math.abs(ballStartVelosity.getX()*2));
                    }
                    
                    if(evt.getKeyCode() == 87)
                    {
                        //движение платформы вверх
                        platform.getVelosity().setY(-Math.abs(ballStartVelosity.getX()/2));
                    }
                    else if(evt.getKeyCode() == 83)
                    {
                        //движение платформы вних
                        platform.getVelosity().setY(Math.abs(ballStartVelosity.getX()/2));
                    }
                    
                    if(!isGameStarted == true && evt.getKeyCode() == 32)
                    {
                        isGameStarted = true;
                        ball.setVelosity(ballStartVelosity);
                    }
                }
        }
        );
        
        //При поднятии клавиш движения платформа останавливается
        frame.addKeyListener( new java.awt.event.KeyAdapter() {
            public void keyReleased(java.awt.event.KeyEvent evt)
                {
                       platform.getVelosity().setX(0);
                       platform.getVelosity().setY(0);  
                }
        }
        );
        
        //установка параметров окна приложения
        frame.setVisible(true);
        frame.setBounds(GameWindow.WIN_ON_SCREEN_POS.getX().intValue(), 
                GameWindow.WIN_ON_SCREEN_POS.getY().intValue(), GameWindow.WIN_WIDTH, 
                GameWindow.WIN_HEIGHT);
        frame.setLayout(null);
        frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
        
        //Создание объекта игрового поля
        frame.add(win.initBackground());
    }
    /*
        Запускает начальный момент игры с возможностью перемещения платформы
        с мячом для выбора начального положения для старта игры
    */
    public void doGameBeginingLoop() throws InterruptedException
    {
        //временный вектор местоположения мяча на платформе игрока
        MathVector startBallPos = new MathVector(platform.getPos().getX() + platform.getXLength()/2,
        platform.getPos().getY() - BALL_SIZE - 1);
        
        ball.setPosition(startBallPos);
        ball.update();
        platform.update();
        win.repaint();
        Thread.sleep(20);
    }
    
    /*
        Данная функция проверяет уничтожены ли все разрушаемые блоки на поле.
        Если все блоки разрушены, то изменяет статус игры на законченный 
        и поднимает окно с поздравлением и перезапуском игры.
    */
    public void checkForGameEnd()
    {        
        
        boolean result = true;
        
        //Проверка всех блоков на состояние "разрушен"
        for(Hitbox it : obstacles)
        {
            DestroyableBox box;   
            try{
                //Массив препятствий содержит не только разрушаемые блоки.
                //Преобразование типа не всегда возможно. Необходимо обрабатывать такие ситуации
                box  = (DestroyableBox)it; 
            }
            catch(Exception e)
            {
                //Если блок невозможно преобразовать, то он не подходит для проверки
                //Дополнительных действий с ним не требуется. Пропустить итерацию проверки
                continue;
            }
            if(box.isBroken == true)
            {
                continue;
            }
            //Если блок не сломан, то игра еще не окончена
            if(box.isBroken == false)
            {
                result = false;
                break;
            }  
        }
        //Если результат положительный, то игра окончена
        if(result == true)
        {
            isGameOver = true;
            messageFrame.riseMessage(winningMessage);
        }
    }
    
    /*
        Выполнить один такт игры.
        Подвинуть мяч внутри игрового поля, проверить на наличие коллизий,
        Проверить на окончание игры
    */
    public void doGameLoop() throws InterruptedException
    {
        //Проверка на коллизии мяча
        for( Hitbox itBox : obstacles )
        {  
            itBox.ballCollisionDetection(ball);  
        }
            
        //обновление положения мяча и платформы игрока
        ball.update();
        platform.update();
            
        //Проверка на попадание мяча в поле проигрыша
        if(gameOverBox.isContains(ball.getPosition()) == true)
        {
            this.isGameOver = true;
            this.messageFrame.riseMessage(loseMessage);
        }
            
        checkForGameEnd();
        win.repaint();
        Thread.sleep(20);
    }
    
    /*
        Перезапуск игры
    */
    public void restartGame()
    {
        isGameStarted = false;
        isGameOver = false;
        
        obstacles.clear();
        win.getBG().removeAll();
        
        initObstacles();
        initPlatform();
        initBall();

        frame.repaint();
        
    }
    
    /*
        Функция старта всей игры
    */
    public void startGame() throws InterruptedException
    {
        
        frame.repaint();
        win.repaint();
        
        while(this.isProgramActive == true)
        {
            if(this.isGameStarted == false)
            {
                this.doGameBeginingLoop();
                continue;
            }
            
            if(this.isGameOver != true)
            {
                this.doGameLoop();
                continue;
            }
            
            Thread.sleep(1000);
            
        }
        frame.dispatchEvent(new WindowEvent(frame, WindowEvent.WINDOW_CLOSING));
    }
    
    
    public static void main(String[] args) throws InterruptedException {
        
        Arcanoid game = new Arcanoid();
        
        game.startGame();

    }
}
