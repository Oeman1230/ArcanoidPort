/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.arcanoid;

import java.awt.*;
import javax.swing.*;
/**
 * Класс окна игры
 * Содержит поля и методы связанные с окном игры и игровымм полем
 * @author Yury
 */
public class GameWindow extends JPanel{
    
    //Размеры главного окна
    public static final int WIN_WIDTH = 1200;
    public static final int WIN_HEIGHT = 820;
    
    //размеры игрового поля относительно главного окна
    public static final int BG_WIDTH = 800;
    public static final int BG_HEIGHT = 700;
    
    //Положение главного окна на экране
    public static final MathVector WIN_ON_SCREEN_POS = new MathVector(40,40);
    
    //Положение игрового поля относительно главного окна
    public static final MathVector BG_ON_FRAME_POS = new MathVector(WIN_WIDTH/6, 10);
    
    
    public GameWindow()
    {
        
        this.setBounds(WIN_ON_SCREEN_POS.getX().intValue(), 
                WIN_ON_SCREEN_POS.getY().intValue(), 
                WIN_WIDTH, WIN_HEIGHT);
        
        this.setVisible(true);
       
    }
    public JLabel background;
    
    public JLabel getBG()
    {
        return  background;
    }
    
    public JLabel initBackground()
    {
        background = new JLabel();
        this.add(background);
        
        
        background.setBounds(BG_ON_FRAME_POS.getX().intValue(),
                BG_ON_FRAME_POS.getY().intValue(),
                BG_WIDTH,BG_HEIGHT);
        background.setBackground(Color.BLACK);
        background.setForeground(Color.BLACK);
        background.setOpaque(true);
        background.setVisible(true);
        
        return background;
    }
    
}
