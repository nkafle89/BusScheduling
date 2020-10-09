#pragma once


class Vehicle
{
private:
    double _x;
    double _y;
    double _cap;
public:
    double getXc(){return _x;}
    void setXc(double x){_x = x;}

    double getYc(){return _y;}
    void setYc(double y){_y = y;}

    double getCap(){return _cap;}
    void setCap(double y){_cap = y;}
    
};