#include "timeseries.h"

using namespace std;

// saveData reads a csv file and saving the features names and their values.
void TimeSeries::saveData(const char *fileName) {

    index = 0;
    ifstream myFile(fileName);

    if(myFile.is_open()) {
        // get the first row- the features names
        getline(myFile, line);
        stringstream ss(line);

        // save the features in a map- for every index there is a permanent feature.
        // for example: index 0 will be A and every time i will look for A
        // i will look into a map with key 0
        while(getline(ss, colName, ',')) {

            // removing "\r" from the end of the token
            if(!colName.empty() && colName[colName.size() - 1] == '\r') {
                colName.erase(colName.size() - 1);
            }
            columnFeature.insert({index, colName}); // {0, A}
            //if(ss.peek() == '\r') ss.ignore();
            index++;
        }
    }

    /*
     * for the rest of the file:
     * for every value we convert it into a float and extracting the feature name
     * and inserting into the map the feature name and value
     * after i get the pairs i will insert them into the vector "data"
     * */
    while(getline(myFile, line)) {
        stringstream ss(line);
        featuresAndValues fv;
        index = 0;

        while(getline(ss, token, ',')) {
            val = stof(token);
            colName = columnFeature[index];
            fv.insert({colName, val});
            if(ss.peek() == ',') ss.ignore();
            if(ss.peek() == '\n') ss.ignore();
            index++;
        }
        data.push_back(fv);
    }
    myFile.close();
}

//returns the vector of values of certain feature.
vector<float> TimeSeries::getValues(string feature) const{

    vector<float> valuesVector;

    for(auto iterator = data.begin(); iterator != data.end(); iterator++) {
        valuesVector.push_back(iterator->at(feature));
    }

    return valuesVector;
}

// destructor.
TimeSeries::~TimeSeries() {

    columnFeature.clear();
    data.clear();
}