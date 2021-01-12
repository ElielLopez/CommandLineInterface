//
// Created by eliel on 12/01/2021.
//

#ifndef EX5_MINCIRCLE_H
#define EX5_MINCIRCLE_H

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include "anomaly_detection_util.h"

using namespace std;

// ------------ DO NOT CHANGE -----------
//class Point{
//public:
//    float x,y;
//    Point(float x,float y):x(x),y(y){}
//};

class Circle{
public:
    Point center;
    float radius;
    Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

class minCircle {

public:

    float dist(Point a, Point b);

    Circle from2points(Point a,Point b);

    Circle from3Points(Point a, Point b, Point c);

    Circle trivial(vector<Point>& P);

    Circle welzl(Point** P,vector<Point> R, size_t n);

    Circle findMinCircle(Point** points,size_t size);
};

#endif //EX5_MINCIRCLE_H
