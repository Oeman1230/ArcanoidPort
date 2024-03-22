/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */



package com.mycompany.arcanoid;

/**
 *  Математический вектор
 * @author Yury
 */
public class MathVector {
    
    public static final double PI_2 = (Math.PI / 2); 
    public static final double PI_4 = (Math.PI / 4); 
    public static final double PI3_4 = ((3* Math.PI) / 4); 
    public static final double PI5_4 = ((5* Math.PI) / 4); 
    public static final double PI7_4 = ((7* Math.PI) / 4); 
    
    
    private Double XCoord;
    private Double YCoord;
    
    
    public MathVector(double x, double y)
    {
        XCoord = x;
        YCoord = y;
    }
    
    public MathVector(MathVector newVec)
    {
        XCoord = newVec.getX();
        YCoord = newVec.getY();
    }
    
    public void invertX()
    {
        XCoord = -XCoord;
    }
    public void invertY()
    {
        YCoord = -YCoord;
    }
    
    public Double getX()
    {
        return XCoord;
    }    
    public Double getY()
    {
        return YCoord;
    }
    
    public void setX(double x)
    {
        XCoord = x;
    }
    public void setY(double y)
    {
        YCoord = y;
    }
    
    public Double getLenght()
    {
        double xx = Math.pow(XCoord, 2);
        double yy = Math.pow(YCoord, 2);
        return Math.sqrt(xx + yy);

    }
    
    public void multVec(double mult)
    {
        XCoord *= mult;
        YCoord *= mult;
    }

    public static Double radToDegrees(double radiants)
    {
        return (radiants * 180)/Math.PI;
        
    }
    
    public static void printCoords(MathVector vec)
    {
        System.out.println("posX: " + vec.getX() + " posY: " + vec.getY());
    }
    
}
