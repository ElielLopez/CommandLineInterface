#include <math.h>
#include "anomaly_detection_util.h"

using namespace std;

// Average function will return the average of the x elements.
float avg(float* x, int size){

    float average = 0;;
    float sum = 0;

    for(int i = 0; i < size; i++) {
        sum += x[i];
    }

    average = sum / size;

    return average;
}

// returns the variance of X and Y according to the formula:
// I will calculate the avg of X and then create a variable that contain its power in base 2.
// also i need to calculate the average of X but every element will be in power of 2.
float var(float* x, int size){

    float variance = 0;
    float average = 0;
    float powAverage = 0;
    float sumXPow = 0;
    float sumXPowAverage = 0;

    for(int i = 0; i < size; i++) {
        sumXPow += pow(x[i],2);
    }

    sumXPowAverage = sumXPow / size;
    average = avg(x, size);
    powAverage = pow(average, 2);
    variance = sumXPowAverage - powAverage;

    return variance;
}

// returns the covariance of X and Y.
// for X and Y, i will calculate their average and save a variable with their multiplication.
// in addition i will calculate the multiplication of every element in X with his equivalent in Y and sum them up.
// this sum will be divided by the size and will be the average of XY.
float cov(float* x, float* y, int size){

    float covariance = 0;
    float xAvg = 0;
    float yAvg = 0;
    float xyAvg = 0;
    float xySum = 0;

    for(int i = 0; i < size; i++) {
        xySum += x[i] * y[i];
    }

    xAvg = avg(x, size);
    yAvg = avg(y, size);
    xyAvg = xySum / size;
    covariance = xyAvg - xAvg*yAvg;

    return covariance;
}

// returns the Pearson correlation coefficient of X and Y.
// calculates the covariance of X and Y and then the deviation of X and deviation of Y by applying square root on var.
float pearson(float* x, float* y, int size){

    float pearsonCoefficient = 0;
    float covariance = 0;
    float devX = 0;
    float devY = 0;
    float devXY = 0;

    covariance = cov(x, y, size);
    devX = sqrtf(var(x, size));
    devY = sqrtf(var(y, size));
    devXY = devX * devY;
    pearsonCoefficient = covariance / devXY;

    return pearsonCoefficient;
}

// performs a linear regression and returns the line equation
// a = COV(x,y) / VAR(x)
// b = avgY - a * avgX
// i will save the X and Y into local variables, saving the covariance of X and Y and variance of X,
//calculating a and then b wit average of Y and X.
Line linear_reg(Point** points, int size){

    float a = 0, b= 0;
    float covarianceXY;
    float varianceX;
    float avgY = 0;
    float avgX = 0;
    float x[size];
    float y[size];

    for (int j = 0; j < size; j++) {
        x[j] = points[j]->x;
        y[j] = points[j]->y;
    }

    for(int i = 0; i < size; i++) {
        avgY += points[i]->y;
        avgX += points[i]->x;
    }

    avgY = avgY / size;
    avgX = avgX / size;

    covarianceXY = cov(x, y, size);
    varianceX = var(x, size);

    a = covarianceXY / varianceX;
    b = avgY - a * avgX;

    //return Line(a,b); // TODO
    return Line{a,b};
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){

    float deviation = 0;

    deviation = dev(p, linear_reg(points, size));

    return deviation;
}

// returns the deviation between point p and the line
float dev(Point p,Line l){

    float deviation = 0;
    float px = 0;
    float py = 0;
    float lineX = 0;
    float lineY = 0;
    float a = 0;
    float b = 0;

    px = p.x;
    py = p.y;
    a = l.a;
    b = l.b;
    lineY = a * px + b;

    deviation = fabs(lineY - py);
    //deviation = lineY - py;

    return deviation;
}

// returns the maximum deviation. this function was added to help in
// learnNormal and detect functions.
// given a 2 arrays of floats, calculating the deviation of point and saves the maximum value.
float maximumDeviation(float* x, float* y, int size, Line l) {
    float max = 0;
    float deviation = 0;
    //Point p(0,0);
    for(int i = 0; i < size; i++) {
        Point p(x[i], y[i]);
        deviation = dev(p, l);
        if (max < deviation) max = deviation;
    }
    return max;
}