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
};

// hybrid class: holds a HybridAnomalyDetectors and a vector for the
// anomaly reports for the lasts steps.
class hybridAndVec {
public:
    HybridAnomalyDetector* ad2;
    vector<AnomalyReport> anomalyReportVec;
    hybridAndVec() {
        this->ad2 = new HybridAnomalyDetector();
    }
};

// addind hybrid and vector member and description for every command.
// also, every command will be friend of command.
class Command{
    hybridAndVec* hav;
    DefaultIO* dio;
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

    Command(DefaultIO* dio, hybridAndVec* h):dio(dio), hav(h){}
    Command(){}
    virtual void execute()=0;
    virtual ~Command(){}
};

// ----------------- implement here your command classes ------------------


// uploadFile command gets a training file from client,
// reads the file line by line and uploads it to the server.
// then, gets a test file and upload it to the server.
// while the line is not the word "done" the server keeps reading from the file.
class uploadFile: public Command {

public:
    uploadFile(DefaultIO* dio, hybridAndVec* h):Command(dio, h) {
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

        while(!(line == done)) { // || !(line == "done\n")
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

// first displays the current threshold (as default its 0.9).
// then, asks the user to insert new threshold. this actions will be with the help of get ans set methods
// that was added to this exercise and was not in the previous ones.
// if the value of the inserted threshold is not between 0 to 1, call execute again until the
// user inserts a valid value
class algorithmSetting: public Command {

    float thresholdFromDetector;
    float newThreshold = 0;
public:
    algorithmSetting(DefaultIO* dio, hybridAndVec* h):Command(dio, h) {
        description = "2.algorithm settings";
        this->hav = h;
    }

    void execute() override {
        dio->write("The current correlation threshold is ");
        thresholdFromDetector = hav->ad2->getThreshold();
        dio->write(thresholdFromDetector);
        dio->write("\n");
        dio->write("Type a new threshold\n");
        dio->read(&newThreshold);
        if(0 <= newThreshold && newThreshold <= 1) {
            hav->ad2->setThreshold(newThreshold);
            return;
        } else {
            dio->write("please choose a value between 0 and 1.\n");
            dio->read();
            execute();
        }
    }
};

// server will run algorithms on the files the user uploaded previous to this step.
// first creating time series from the training file and then from the test file.
// afterwards, calling learn normal of Hybrid anomaly detector and then detect, which in his turn
// will call the correct detect method.
class anomalyDetection: public Command {

public:
    anomalyDetection(DefaultIO* dio, hybridAndVec* h):Command(dio, h) {
        description = "3.detect anomalies";
        this->hav = h;
    }

    void execute() override {

        TimeSeries ts1("anomalyTrain.csv");
        TimeSeries ts2("anomalyTest.csv");

        hav->ad2->learnNormal(ts1); //with training file
        vector<AnomalyReport> tmp = hav->ad2->detect(ts2);

        for(int i = 0; i <  tmp.size(); i++) {
            hav->anomalyReportVec.push_back(tmp[i]);
        }

        dio->write("anomaly detection complete.\n");
    }
};

// displaying the results of the anomaly report.
// first diaplying time step and then the name of the fetures.
class displayResults: public Command {
    int sizeOfVec = 0;
public:
    displayResults(DefaultIO* dio, hybridAndVec* h):Command(dio, h) {
        description = "4.display results";
        this->hav = h;
    }

    void execute() override {
        sizeOfVec = hav->anomalyReportVec.size();

        for(int i = 0; i < sizeOfVec; i++) {
            dio->write(hav->anomalyReportVec[i].timeStep);
            dio->write("\t");
            dio->write(hav->anomalyReportVec[i].description + "\n");
        }
        dio->write("Done.\n");
    }
};

//
class uploadAndAnalayze:public Command {
    float p, trueP, falseP; // number of anomalies,...
    float n;
public:
    uploadAndAnalayze(DefaultIO* dio, hybridAndVec* h):Command(dio, h) {
        description = "5.upload anomalies and analyze results";
        this->hav = h;
    }

    void execute() override {
        dio->write("Please upload your local anomalies file.\n");
        // TODO upload

        dio->write("Upload complete.\n");

        // TODO
        dio->write("True Positive Rate: ");

        //TODO
        dio->write("False Positive Rate: ");

    }
};

class exitServer: public Command {
public:
    exitServer(DefaultIO* dio, hybridAndVec* h):Command(dio, h) {
        description = "6.exit";
    }

    void execute() override {

    }
};

#endif //EX5_COMMANDS_H
