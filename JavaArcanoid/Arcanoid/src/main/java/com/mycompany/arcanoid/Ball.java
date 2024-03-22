/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.arcanoid;

import javax.swing.*;
import java.awt.*;
/**
 * Класс мяча
 * @author Yury
 */
public class Ball {
    
    public Ball(MathVector positionInGameField, MathVector StartVelosity, 
            Integer fieldHeight)
    {
        position = positionInGameField;
        velosity = StartVelosity;
        this.fieldHeight = fieldHeight;
        
    }

    private MathVector position;
    private MathVector velosity;
    private Integer ballSize;
    private JLabel texture;
    private Integer fieldHeight;
    
    public MathVector getPosition()
    {
        return position;
    }
    
    public void setPosition(MathVector newPos)
    {
        position = newPos;
    }
    
    public MathVector getVelosity()
    {
        return velosity;
    }
    
    public void setVelosity(MathVector newVel)
    {
        velosity = newVel;
    }
   
     /*
        Функция создаёт текстуру мяча по заданным параметрам
        Принимает цвет мяча и его размер
        Возвращает созданную текстуру мяча
    */
     
     public JLabel createBall(Color ballColor, Integer size)
     {
         texture = new JLabel();
         texture.setBackground(ballColor);
         texture.setForeground(ballColor);
         
         ballSize = size;
         
         texture.setBounds(position.getX().intValue(), 
                 position.getY().intValue(),
                 ballSize, ballSize);
         texture.setOpaque(true);
         
         return texture;
         
     }
     //Функция обновления местоположения мяча по заданной скорости
     public void update()
     {
         position.setX(position.getX() + velosity.getX());
         position.setY(position.getY() + velosity.getY());
         
         texture.setLocation(position.getX().intValue(), position.getY().intValue());
     }
}
