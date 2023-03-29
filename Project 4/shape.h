#pragma once

using namespace std;

class Shape
{
    protected:
        int x;
        int y;

    public: 
        Shape();
        Shape(int x, int y);

        virtual ~Shape(){}
        virtual Shape* copy();

        int getX() const;
        int getY() const;
        void setX(int);
        void setY(int);
        
        virtual void printShape() const;
};

Shape::Shape(int x, int y){ //default
    this->x = x;
    this->y = y;
}

Shape::Shape(){ //constructor
    this->x = 0;
    this->y = 0;
};

Shape *Shape::copy() {
    return new Shape(x, y);
}

int Shape::getX() const {
    return x;
}

void Shape::setX(int value1) {
    this->x = value1;
}

int Shape::getY() const {
    return y;
}

void Shape::setY(int value2) {
    this->y = value2;
}

void Shape::printShape() const {
    cout << "It's a Shape at x: " << x << ", y: " << y << endl;
}

class Circle : public Shape 
{
    private:
        int radius;

    public: 
        Circle();
        Circle(int r);
        Circle(int x, int y, int r);

        virtual ~Circle(){}
        virtual Circle* copy(){
            return new Circle(x, y, radius);
        }
        
        int getRadius() const;
        void setRadius(int);
        
        virtual void printShape() const;
};

Circle::Circle():Shape(){
    this->radius = 0;
}

Circle::Circle(int r):Shape(){
    this->radius = r;
}

Circle::Circle(int x, int y, int r):Shape(x, y){
    this->radius = r;
}

int Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(int value3) {
    this->radius = value3;
}

void Circle::printShape() const{
    cout << "It's a Cirlce at x: " << x << ", y: " << y << ", radius: " << radius << endl;
}



class Rectangle : public Shape 
{
    private:
        int width;
        int height;

    public: 
        Rectangle();
        Rectangle(int w, int h);
        Rectangle(int x, int y, int w, int h);
        
        virtual ~Rectangle(){}
        virtual Rectangle* copy();
        
        int getWidth() const;
        int getHeight() const;
        void setWidth(int);
        void setHeight(int);
        
        virtual void printShape() const;
};

Rectangle::Rectangle():Shape() {
    this->width = 0;
    this->height = 0;
}

Rectangle::Rectangle(int w, int h):Shape(){
    this->width = w;
    this->height = h;
}

Rectangle::Rectangle(int x, int y, int w, int h):Shape(x,y){
    this->width = w;
    this->height = h;
}

int Rectangle::getHeight() const {
    return height;
}

int Rectangle::getWidth() const {
    return width;
}

void Rectangle::setHeight(int value4) {
    this->height = value4;
}

void Rectangle::setWidth(int value5) {
    this->width = value5;
}

Rectangle *Rectangle::copy() {
    return new Rectangle(x, y, width, height);
}

void Rectangle::printShape() const{
    cout << "It's a Rectangle at x: " << x << ", y: " << y <<" with width: " << width <<" and height: " << height << endl;
}


class RightTriangle : public Shape 
{
    private:
        int base;
        int height;

    public: 
        RightTriangle();
        RightTriangle(int b, int h);
        RightTriangle(int x, int y, int b, int h);
        
        virtual ~RightTriangle(){}
        virtual RightTriangle* copy();
        
        int getBase() const;
        int getHeight() const;
        void setBase(int);
        void setHeight(int);

        virtual void printShape() const;
};

RightTriangle::RightTriangle():Shape() {
    this->base = 0;
    this->height = 0;
}


RightTriangle::RightTriangle(int b, int h): Shape(){
    this->height = h;
    this->base = b;
}

RightTriangle::RightTriangle(int x, int y, int b, int h): Shape(x,y){
    this->height = h;
    this->base = b;
}

int RightTriangle::getHeight() const {
    return height;
}

RightTriangle *RightTriangle::copy() {
    return new RightTriangle(x, y, base, height);
}

int RightTriangle::getBase() const {
    return base;
}

void RightTriangle::setHeight(int value6) {
    this->height = value6;
}

void RightTriangle::setBase(int value7) {
    this->base = value7;
}

void RightTriangle::printShape() const{
    cout << "It's a Right Triangle at x: " << x << ", y: " << y <<" with base: " << base <<" and height: " << height << endl;
}