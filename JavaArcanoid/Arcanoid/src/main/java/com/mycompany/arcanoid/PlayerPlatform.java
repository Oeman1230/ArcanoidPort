/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.arcanoid;

import javax.swing.*;
import java.awt.*;
/**
 * Класс платформы игрока
 * Игрок управляет данным блоком с помощью кнопок
 * @author Yury
 */
public class PlayerPlatform extends Hitbox{
    
    //Ссылка на допустимое для перемещения поле
    private Hitbox acceptablePosition;
    
    
    private JLabel texture;
    private MathVector velosity;
    
    
    
    public PlayerPlatform( Hitbox acceptablePosition )
    {
        super();
        this.acceptablePosition = acceptablePosition;
    }
    
    public MathVector getVelosity()
    {
        return velosity;
    }
    
    /*
        Функция проверки мяча на коллизию с платформой
        Принимает объект мяча
        В случае, если мяч соударяется с платформой он дополнительно перемещается 
            выше платформы для исправления застрявания мяча внутри
    */
    @Override
    public boolean ballCollisionDetection(Ball ball)
    {
        boolean ret = false;
        
        ret = super.ballCollisionDetection(ball);
        
        //Подъём мяча наверх платформы при соударении
        if(ret == true)
        {
            ball.getPosition().setY(this.getPos().getY() - Arcanoid.BALL_SIZE-1);

        }
        
        
        return ret;
    }
    
    /*
        Функция создания платформы игрока
        Принимает размеры платформы по горизонтали и вертикали
        Возвращает текстуру платформы
    */
    public JLabel createPlatforn(Integer sizeHorizontal, Integer sizeVertical)
    {
        velosity = new MathVector(0,0);

        //Создание объекта платформы
        texture = new JLabel();
        texture.setBounds(this.getPos().getX().intValue(), this.getPos().getY().intValue(), 
                sizeHorizontal, sizeVertical);
        texture.setOpaque(true);
        texture.setBackground(Color.LIGHT_GRAY);
        texture.setForeground(Color.LIGHT_GRAY);
        texture.setVisible(true);
        texture.setBorder(BorderFactory.createLineBorder(Color.RED, 2));
        
        return texture;
    }
    
    /*
        Функция обновления позиции платформы
        Перемещает платформу в зависимости от направления вектора скорости
        Если платформа переступает за границу допустимого поля, движения не происходит
    */
    @Override
    public void update()
    {
        MathVector nextPos = new MathVector(this.getPos().getX() + this.velosity.getX(),
        this.getPos().getY() + this.velosity.getY());
        
        
        if(acceptablePosition.isContains(nextPos) == true )
        {
            this.setPos(nextPos);
            texture.setLocation(nextPos.getX().intValue(), nextPos.getY().intValue());
        }
        texture.repaint();
        
    }
    
}
