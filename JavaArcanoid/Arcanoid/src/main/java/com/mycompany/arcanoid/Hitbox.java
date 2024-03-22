/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.arcanoid;

/**
 * Базовый класс объекта препятсвий
 * Данный класс содержит методы и свойства, позволяющие определить в какой точке
 * находится препядствие и где происходит соударение мяча
 * 
 * @author Yury
 */
public class Hitbox {
    
    //Стороны препядствия
    public enum Sides
    {
        UP,
        DOWN, 
        LEFT,
        RIGHT,
        NONE;
        
    }

    public String boxName; 
    
    public Hitbox()
    {
        boxName = "NoName";
    }
    
    public Hitbox(String newName)
    {
        boxName = newName;
    }
    
    //Позиция и размеры препядствия
    private MathVector position;
    private Double XLength;
    private Double YLength;
    
    public MathVector getPos()
    {
        return position;
    }
    
    public void setPos(MathVector newPos)
    {
        position = newPos;
    }
    
    public void setXLength(double len)
    {
        XLength = len;
    }
    public void setYLength(double len)
    {
        YLength = len;
    }
    
    public Double getXLength()
    {
        return XLength;
    }
    public Double getYLength()
    {
        return YLength;
    }
    
    //проверка на попадание точки внутрь поля.
    //Принимает математический вектор
    //Если точка находится внутри поля, то возвращается истина
    public boolean isContains(MathVector vec)
    {
        boolean ret = false;
        
        if(! (this.getPos().getX() <= vec.getX() 
                && vec.getX() <= (this.getPos().getX() + this.getXLength() ) ))
        {
            return ret;
        }
        if((this.getPos().getY() <= vec.getY() 
                && vec.getY() <= (this.getPos().getY() + this.getYLength() ) ))
        {
            ret = true;
        }
       
        return ret;
    }
    /*
        Выдать угол точки относительно центра поля
        Принимает математический вектор
        Возвращает угол  в радианах между точкой и центральным вектором поля
        Который исходит из центра поля вправо
    */
    public Double getAngleInCrossingPoint(MathVector vec)
    {
        Double ret = 0.0;
        
        
        Double cosAngle = 0.0;
        Double sinAngle = 0.0;
        
        Double angle = 0.0;
        
        //Определение угла
        try
        {
            //Временные дополнительные переменные для обработки
            Double Px_plus_XlenDiv2 = (this.getPos().getX() +
                    (this.getXLength()/2) );
            Double Py_plus_YlenDiv2 = (this.getPos().getY() + 
                            (this.getYLength()/2) );
            
            //создание вектора приходящей точки, относительно центра поля
            MathVector VColliding = new MathVector(
                    vec.getX() -  Px_plus_XlenDiv2
                    ,
                    vec.getY() - Py_plus_YlenDiv2
            );
            //Центральный вектор
            MathVector VCenterLine = new MathVector (
                    this.getXLength()/2
                    ,
                    0
            );
            
            //определение косинусной составляющей угла поворота
            Double nomin = ( VCenterLine.getX() * VColliding.getX());
            Double denomin = (VCenterLine.getLenght() * VColliding.getLenght());
            
            cosAngle = Math.acos(nomin/denomin);
            
            //Центральный вектор, направленный из цента поля вверх
            MathVector VYCenter = new MathVector(0,this.getYLength()/2);
            
            nomin = (VYCenter.getY() * VColliding.getY());
            denomin = (VYCenter.getLenght() * VColliding.getLenght() );
            //Нахождение синусной составляющей угла
            sinAngle =  Math.asin(nomin/denomin);

        }
        catch(Exception ex)
        {
            System.out.println("divide to zero");
            return ret;
        }
        
        //Проверка в какой полуплоскости находится проверяемая точка
        if(sinAngle > 0)
        {
            angle = cosAngle;
        }
        else
        {      
            angle = (Math.PI * 2) - cosAngle; 
            
        }
        
        ret = angle;
        
        return ret;
    }
    
    /*
        Функция проверки мяча на пересечение с полем-препятствием
        Принимает объект мяча
        Возвращает истину, если края мяча попадают внутрь этого поля
    */
    public boolean ballCollisionDetection(Ball ball)
    {
        MathVector tempVec = new MathVector(position);
        
        //Центр мяча
        MathVector centerPos = new MathVector(ball.getPosition().getX() + (Arcanoid.BALL_SIZE/2),
        ball.getPosition().getY() + (Arcanoid.BALL_SIZE/2));
        
        //Проверка четырех точек относительно центра мяча на пересечение с полем
        for(int i = 0; i<4; i++)
        {
           //Поворот текущей точки относительно центра
           tempVec.setX(centerPos.getX() +
                    (Arcanoid.BALL_SIZE/2)*(Math.cos(MathVector.PI_2 * i)));
           tempVec.setY(centerPos.getY() +
                    (Arcanoid.BALL_SIZE/2) * (Math.sin(MathVector.PI_2*i)));
           
           
           //Проверка на пересечение
           if(this.isContains(tempVec) == true)
           {
               //В случае попадания мяча внутрь поля выдать относительную сторону
               Hitbox.Sides side = this.getSide(centerPos);
               
               
               /*
                    В случае абсолютно упругого соударения мяча с левой или правой сторой
                    необходимо и достаточно инвертировать горизонтальную состовляющую
                    вектора скорости мяча
                    Аналогично, в случае соударения мяча с верхней или нижней стороной
                    достаточно инвертировать вертикальную составляющую вектора скорости
               */
               switch(side)
               {
                   case UP:
                   {
                       ball.getVelosity().invertY();
                       break;
                   }
                   case DOWN:
                   {

                       ball.getVelosity().invertY();
                       break;
                   }
                   case LEFT:
                   {
                       ball.getVelosity().invertX();
                       break;
                   }
                   case RIGHT:
                   {
                       ball.getVelosity().invertX();
                       break;
                   }
                   default:
                   {
                       break;
                   }
               }
               return true;
           }

        }
        
        
        
        return false;
    }
    
    
    /*
        Функция выдачи относительной стороны точки
        Принимает математический вектор
        Функция вычисляет угол между центральным вектором и вектором от центра к 
        искомой точке и проверяет в какой квадрант попадает точка
    */
    public Sides getSide(MathVector vec)
    {
        Sides ret = Sides.NONE;
        
        Double angle = this.getAngleInCrossingPoint(vec);
        
        //Проверка каждого квадранта
        Double fi_1 = Math.atan(this.getYLength()/this.getXLength());
        if(( 0 <= angle && angle < fi_1)  || (Math.PI * 2 - fi_1 < angle && angle <= Math.PI*2))
        {
            ret = Sides.RIGHT;
        }
        if(fi_1 < angle && angle < Math.PI - fi_1)
        {
            ret = Sides.UP;
        }
        
        if(Math.PI - fi_1 < angle && angle < Math.PI + fi_1)
        {
            ret = Sides.LEFT;
        }
        if(Math.PI + fi_1 < angle && angle < Math.PI * 2 - fi_1)
        {
            ret = Sides.DOWN;
        }
        return ret;
    }
    
    public void update()
    {
        return;
    }
    
}
