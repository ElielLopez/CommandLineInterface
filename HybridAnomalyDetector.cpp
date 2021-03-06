#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {}

HybridAnomalyDetector::~HybridAnomalyDetector() {
    ar.clear();
}

// the learning will stay the same as before using the SimpleAnomalyDetector
// to learn the data.
void HybridAnomalyDetector::learnNormal(const TimeSeries& ts) {
    SimpleAnomalyDetector::learnNormal(ts);
}

// the detect function will check if the correlation of a given CF is bigger then 0.9 or less then 0.9
// but bigger then 0.5. in the first case, will use the simple anomaly detector.
// int the second case, creating 2 vector of thr correlated features to create a Point**
// for every point, checking the distance from the center of the training set circle of this features then
// checking if the distance is bigger than the threshold of those CF.
// if so, this is an anomaly and it will be save in anomaly report
vector<AnomalyReport> HybridAnomalyDetector::detect(const TimeSeries& ts) {

    vector<AnomalyReport> tempAR;
    vector<float> tmpVec1, tmpVec2;
    string description;
    float distance;
    int sizeOfVector;

    tempAR = move(SimpleAnomalyDetector::detect(ts));

    for(auto it = this->cf.begin(); it != cf.end(); it++) {

        if((it->corrlation > 0.5) && (it->corrlation < 0.9)) {

            tmpVec1 = ts.getValues(it->feature1);
            tmpVec2 = ts.getValues(it->feature2);
            sizeOfVector = tmpVec1.size();

            Point* ps3[sizeOfVector];
            for(int i=0;i<sizeOfVector;i++) {
                ps3[i] = new Point(tmpVec1[i], tmpVec2[i]);
            }

            for(int j = 0; j < sizeOfVector; j++){

                Point p(tmpVec1[j], tmpVec2[j]);
                distance = calcDistance(p, it->c.center);
                if(it->threshold < distance) { //original: it->threshold < distance
                    description = it->feature1 + '-' + it->feature2;
                    tempAR.push_back(AnomalyReport(description, j + 1));
                }
            }
            for(int i=0;i<sizeOfVector;i++) {
                delete ps3[i];
            }
        }
    }

    //tmpVec1.clear();
    //tmpVec2.clear();

    return tempAR;
}

// this functions added for ex5 for the user request.
float HybridAnomalyDetector::getThreshold() {
    return SimpleAnomalyDetector::getThreshold();
}
float HybridAnomalyDetector::setThreshold(float thresh) {
    return SimpleAnomalyDetector::setThreshold(thresh);
}