//
// Created by eliel on 11/01/2021.
//

#ifndef EX5_HYBRIDANOMALYDETECTOR_H
#define EX5_HYBRIDANOMALYDETECTOR_H

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {

public:

    vector<AnomalyReport> ar;

    HybridAnomalyDetector();

    // does not need to be depend on the origin of the information (stream or file...)
    virtual void learnNormal(const TimeSeries& ts);

    // return list of reports. every anomaly report has description and time stamp
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);

    virtual ~HybridAnomalyDetector();

};


#endif //EX5_HYBRIDANOMALYDETECTOR_H
