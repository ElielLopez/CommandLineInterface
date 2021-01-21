//
// Created by eliel on 12/01/2021.
//

#ifndef EX5_SIMPLEANOMALYDETECTOR_H
#define EX5_SIMPLEANOMALYDETECTOR_H

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include "minCircle.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures{
    string feature1,feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    // new fields for the circle representation.
    //Point cf_center;
    //float cf_radius;
    Circle c;
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{

public:

    int tableSize;
    vector<correlatedFeatures> cf;

    float m_threshold;
    float minimumThreshold;

    SimpleAnomalyDetector() {
        m_threshold = 0.9, minimumThreshold = 0.1;
    }

    virtual float getThreshold();
    virtual float setThreshold(float thresh);

    // does not need to be depend on the origin of the information (stream or file...)
    virtual void learnNormal(const TimeSeries& ts);

    // return list of reports. every anomaly report has description and time stamp
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);

    // returns list of correlated features.
    vector<correlatedFeatures> getNormalModel(){
        return cf;
    }

    virtual int getRowsNumber();
    virtual float calcDistance(Point a, Point b);

    // destructor.
    virtual ~SimpleAnomalyDetector();
};

#endif //EX5_SIMPLEANOMALYDETECTOR_H
