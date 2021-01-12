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
    DefaultIO* dio;
    string description;
    friend class uploadFile;
    friend class algorithmSetting;
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

        while(!(line == done) || !(line == "done\n")) {
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

public:
    algorithmSetting(DefaultIO* dio): Command(dio) {
        description = "2.algorithm settings";
    }

    void execute() override {
        dio->write("The current correlation threshold is ");
    }
};

#endif //EX5_COMMANDS_H
