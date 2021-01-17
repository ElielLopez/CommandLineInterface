//
// Created by eliel on 11/01/2021.
//

#ifndef EX5_COMMANDS_H
#define EX5_COMMANDS_H

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~DefaultIO(){}

    // you may add additional methods here
};

// you may add here helper classes


// you may edit this class
class Command{
    HybridAnomalyDetector *ad;
    DefaultIO* dio;

    vector<AnomalyReport> anomalyReportVec;
    string description;

    friend class uploadFile;
    friend class algorithmSetting;
    friend class anomalyDetection;
    friend class displayResults;
    friend class uploadAndAnalayze;
    friend class exitServer;

public:

    string getDescription() {
        return description;
    }

    Command(DefaultIO* dio):dio(dio){}
    virtual void execute()=0;
    virtual ~Command(){}
};

// ----------------- implement here your command classes ------------------


// uploadFile command gets a training file from client,
// reads the file line by line and uploads it to the server.
// then, gets a test file and upload it to the server.
class uploadFile: public Command {

public:
    uploadFile(DefaultIO* dio):Command(dio) {
        description = "1.upload a time series csv file";
    }

    void uploadTrainFile() {
        dio->write("Please upload your local train CSV file.\n");
        ofstream anomalyTraincsv;
        anomalyTraincsv.open("anomalyTrain.csv");
        string done = "done";
        string line = dio->read();

        while(!(line == done)) { //  || !(line == "done\n")
            anomalyTraincsv<<line<<"\n";
            line = dio->read();
        }

        anomalyTraincsv.close();
        dio->write("Upload complete.\n");
    }

    void uploadTestFile() {
        dio->write("Please upload your local test CSV file.\n");
        ofstream anomalyTestcsv;
        anomalyTestcsv.open("anomalyTest.csv");
        string done = "done";
        string line = dio->read();

        while(!(line == done) || !(line == "done\n")) {
            anomalyTestcsv<<line<<"\n";
            line = dio->read();
        }
        anomalyTestcsv.close();
        dio->write("Upload complete.\n");
    }

    void execute() override {
        uploadTrainFile();
        uploadTestFile();
    };
};

class algorithmSetting: public Command {

    float thresholdFromDetector;
    float newThreshold = 0;
public:
    algorithmSetting(DefaultIO* dio): Command(dio) {
        description = "2.algorithm settings";
    }

    void execute() override {
        dio->write("The current correlation threshold is ");
        thresholdFromDetector = ad->getThreshold();
        dio->write(thresholdFromDetector);
        dio->write("\n");
        dio->write("Type a new threshold\n");
        dio->read(&newThreshold);
        if(0 <= newThreshold && newThreshold <= 1) {
            ad->setThreshold(newThreshold);
            return;
        } else {
            dio->write("please choose a value between 0 and 1.\n");
            dio->read();
            execute();
        }
    }
};

// server will run algorithms on the files the user uploaded previous to this step.
class anomalyDetection: public Command {

public:
    anomalyDetection(DefaultIO* dio): Command(dio) {
        description = "3.detect anomalies";
    }

    void execute() override {

        TimeSeries ts1("anomalyTrain.csv");
        TimeSeries ts2("anomalyTest.csv");

        ad->learnNormal(ts1); //with training file
        anomalyReportVec = ad->detect(ts2);

        // after server running:
        dio->write("anomaly detection complete.\n");
    }
};

class displayResults: public Command {
    int sizeOfVec = 0;
public:
    displayResults(DefaultIO* dio): Command(dio) {
        description = "4.display results";
    }

    void execute() override {
        sizeOfVec = anomalyReportVec.size();

        for(int i = 0; i < sizeOfVec; i++) {
            dio->write(anomalyReportVec[i].timeStep);
            dio->write("\t");
            dio->write(anomalyReportVec[i].description + "\n");
        }
        dio->write("Done.\n");
    }
};

class uploadAndAnalayze:public Command {
public:
    uploadAndAnalayze(DefaultIO* dio):Command(dio) {
        description = "5.upload anomalies and analyze results";
    }

    void execute() override {
        dio->write("TEST upload&Analyze\n");
    }
};

class exitServer: public Command {
public:
    exitServer(DefaultIO* dio): Command(dio) {
        description = "6.exit";
    }

    void execute() override {

    }
};

#endif //EX5_COMMANDS_H
