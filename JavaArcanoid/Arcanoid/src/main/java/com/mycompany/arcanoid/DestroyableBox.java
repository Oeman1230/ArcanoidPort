/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.arcanoid;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
/**
 * Класс разрушаемых блоков
 * Содержит переопределенные методы поля препятствий
 * @author Yury
 */
public class DestroyableBox extends Hitbox{
    
    public DestroyableBox()
    {
        super();
    }
    
    public DestroyableBox(String boxName)
    {
        super(boxName);
    }
    
    public boolean isBroken = false;
    
 
    /*
        Функция проверяет находится ли точка внутри блока
        Если блок сломан, то проверки не осуществляется
    */
    @Override
    public boolean isContains(MathVector vec)
    {
        boolean ret = false;
        
        if(isBroken == true)
        {
            return ret;
        }
        else
        {
            ret = super.isContains(vec);
            
        }
        
        
        return ret;
    }
    
    //Текстура разрушаемого блока
    private JLabel texture;
    
    /*
        Функция создающая разрушаемый блок по заданным параметрам
        Принимает местоположение блока отнотельно игрового поля, размер по 
            вертикали и горизонтали
        Возвращает текстуру разрушаемого блока
    */
    public JLabel createBox(MathVector pos, Integer XLen, Integer YLen)
    {
        this.setPos(pos);
        this.setXLength(XLen);
        this.setYLength(YLen);
        
        //создание объекта текстуры блока
        texture = new JLabel();
        texture.setBackground(Color.GRAY);
        
        texture.setBorder(BorderFactory.createLineBorder(Color.BLUE, 2)); 
        texture.setForeground(Color.GRAY);
        texture.setBounds(this.getPos().getX().intValue(), this.getPos().getY().intValue(),
                this.getXLength().intValue(), this.getYLength().intValue());
        
        texture.setOpaque(true);
        texture.setVisible(true);
        
        isBroken = false;
        
        
        return texture;
    }
    
    /*
        Функция выдачи относительной стороны точки
        По логике игры данный метод будет вызываться только, если коллизия мяча 
        и блока произошла, что должно приводить к его разрушению
    */
    @Override
     public Sides getSide(MathVector vec)
    {
        Sides ret = Sides.NONE;
        
        //стояние разрушение блока скрывает его с поля, но не удаляет из массива препятствий
        isBroken = true;
        texture.setVisible(false);
        texture.repaint();
        
        ret = super.getSide(vec);
        
        
        return ret;
    }
    
    /*
        Класс сборщик типовых разрушаемых блоков. 
        Позволяет создавать множество одинаковых блоков, но в разных точках поля
    */
    public static class DBoxesBuilder
    {
        //Все блоки будут добавляться в один и тот же массив препятствий
        public DBoxesBuilder(ArrayList<Hitbox> obstacles)
        {
            obstaclesRef = obstacles;
        }
        
        
        public Integer XLen = 0;
        public Integer YLen = 0;
        
        public ArrayList<Hitbox> obstaclesRef;
        
        public void setXLen(Integer newLen)
        {
            XLen = newLen;         
        }
        public void setYLen(Integer newLen)
        {
            YLen = newLen;         
        }
        
        /*
            Фунция создающая разрушаемый блок
            Принимает позицию по Х и по Y
            Возвращает текстуру блока
        */
        public JLabel createBox(Integer posX, Integer posY)
        {
            JLabel ret;
            
            DestroyableBox tempBox = new DestroyableBox();
            
            MathVector pos = new MathVector(posX,posY);
            tempBox.setXLength(XLen);
            tempBox.setYLength(YLen);
            ret = tempBox.createBox(pos, XLen, YLen);
            
            obstaclesRef.add(tempBox);
            
            return ret;
            
        }
        
    }
    
    
}
