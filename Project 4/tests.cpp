/// @filename tests.cpp
/// @date March 7, 2023

/// Provided testing file to implement
/// framework based tests in. The example
/// below uses the Catch testing framework
/// version that uses a single .hpp file.

///* Header:
// * author/student: Maria Bezerra
// * netID: 676493398
// * course: CS 251 - spring 2023
// * assignment: Shapes

/*
 This code is a test file (tests.cpp) that uses the Catch testing framework to test the shape.h and canvaslist.h files.
 The tests verify that the various functions and methods work as expected for the classes Shape and CanvasList.

 The tests verify that default constructors, copy constructors, and assignment operators function correctly.
 There are also tests for adding and removing items to the CanvasList, as well as verifying that the correct item is at
 the expected location. Some of the tests use shapes such as RightTriangle and Circle that inherit from Shape.

 */

// This tells Catch to provide a main()
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "shape.h"
#include "canvaslist.h"

using namespace std;

//testing to get x and y on shape.h
TEST_CASE("Shape default with x and y")
{
    Shape r;
    REQUIRE(r.getX() == 0);
    REQUIRE(r.getY() == 0);
}

TEST_CASE("front: ") {
    CanvasList r;
    REQUIRE(r.front() == 0);
}

TEST_CASE("Default const. Canvas List") {
    CanvasList r;
    //making sure it's empty and size is 0
    REQUIRE(r.isempty() == true);
    REQUIRE(r.size() == 0);
    REQUIRE(r.front() == NULL);
}

TEST_CASE("Copy constructor Canvas List") {
    CanvasList a;


    Shape *s = new Shape(1, 2);
    a.push_back(s);

    s = new RightTriangle(1, 4, 8 , 16);
    a.push_front(s);

    s = new Circle(2,4,6);
    a.insertAfter(0, s);

    CanvasList b(a);
    REQUIRE(b.size() == 3);
    //triangle
    REQUIRE(b.shapeAt(0)->getX() == 1);
    REQUIRE(b.shapeAt(0)->getY() == 4);

    //circle
    REQUIRE(b.shapeAt(1)->getX() == 2);
    REQUIRE(b.shapeAt(1)->getY() == 4);


    //shape
    REQUIRE(b.shapeAt(2)->getX() == 1);
    REQUIRE(b.shapeAt(2)->getY() == 2);
}

//test case for push back on the list
TEST_CASE("CanvasList push_back: ") {
    CanvasList r;

    Shape *s = new Shape(1, 2);
    r.push_back(s);

    s = new RightTriangle(1, 4, 8 , 16);
    r.push_front(s);

    s = new Circle(2,4,6);
    r.insertAfter(0, s);

   //making sure the size is correct after we insert 3 new ones
    REQUIRE(r.size() == 3);

    //shape for right triangle
    REQUIRE(r.shapeAt(0)->getX() == 1);
    REQUIRE(r.shapeAt(0)->getY() == 4);

    //insert after, the circle
    REQUIRE(r.shapeAt(1)->getX() == 2);
    REQUIRE(r.shapeAt(1)->getY() == 4);

    //testing the new shape
    REQUIRE(r.shapeAt(2)->getX() == 1);
    REQUIRE(r.shapeAt(2)->getY() == 2);

}

//test case for push front on the list
TEST_CASE("CanvasList push_front: ") {
    CanvasList r;
    Shape *s = new Shape(1, 3);
    r.push_front(s);
    REQUIRE(r.size() == 1);
}


//test cases for the pop front and back from canvasList
TEST_CASE("CanvasList pop_front, pop_back: ") {
    CanvasList r;

    Shape *s = new Shape(1, 2);
    r.push_back(s);

    s = new RightTriangle(1, 4, 8 , 16);
    r.push_front(s);

    s = new Circle(2,4,6);
    r.insertAfter(0, s);

    //testing for find the triangle by using find and storing the index inside 'a'
    int a = r.find(1,4);

    r.pop_back();
    REQUIRE(r.size() == 2);

    //making sure right triangle is the same
    REQUIRE(r.shapeAt(a)->getX() == 1);
    REQUIRE(r.shapeAt(a)->getY() == 4);

    //making sure circle is the same
    REQUIRE(r.shapeAt(1)->getX() == 2);
    REQUIRE(r.shapeAt(1)->getY() == 4);


    r.pop_front();
    REQUIRE(r.size() == 1);

    //now the circle is at index 0, so making sure it's correct
    REQUIRE(r.shapeAt(0)->getX() == 2);
    REQUIRE(r.shapeAt(0)->getY() == 4);

    r.removeAt(0);
    REQUIRE(r.size() == 0);

}

//checking for overflow etc
TEST_CASE("operator assingning"){
    CanvasList a;
    CanvasList b;

    Shape *s = new Shape(1, 2);

    a.push_back(s);

    s = new RightTriangle(1, 4, 8 , 16);
    a.push_front(s);

    s = new Circle(2,4,6);
    a.insertAfter(0, s);

    //now for b
    b.push_back(s);

    s = new RightTriangle(1, 4, 8 , 16);
    b.push_front(s);

    s = new Circle(2,4,6);
    b.insertAfter(0, s);

    //making them equal
    a = b;

    //checking if they are correct
    a.pop_back();
    REQUIRE(a.size() == 2);

    //making sure right triangle is the same
    REQUIRE(a.shapeAt(0)->getX() == 1);
    REQUIRE(a.shapeAt(0)->getY() == 4);

    //making sure circle is the same
    REQUIRE(a.shapeAt(1)->getX() == 2);
    REQUIRE(a.shapeAt(1)->getY() == 4);


    a.pop_front();
    REQUIRE(a.size() == 1);

    //now the circle is at index 0, so making sure it's correct
    REQUIRE(a.shapeAt(0)->getX() == 2);
    REQUIRE(a.shapeAt(0)->getY() == 4);

    a.removeAt(0);
    REQUIRE(a.size() == 0);
}

TEST_CASE("Test find and shapeAt") {
    CanvasList canvas;
    Circle* circle1 = new Circle(0, 0, 1.0);
    Circle* circle2 = new Circle(2, 2, 1.5);
    Circle* circle3 = new Circle(-2, -2, 0.5);

    canvas.push_back(circle1);
    canvas.push_back(circle2);
    canvas.push_back(circle3);

    REQUIRE(canvas.find(2, 2) == 1);
    REQUIRE(canvas.find(1, 1) == -1);

    Shape* shape = canvas.shapeAt(2);
    REQUIRE(shape == circle3);
    REQUIRE(canvas.shapeAt(5) == nullptr);
}

TEST_CASE("clear and empty"){
    CanvasList r;
    Circle* circle = new Circle(0, 0, 1.0);
    r.push_back(circle);
    r.clear();
    REQUIRE(r.isempty() == true);
}






