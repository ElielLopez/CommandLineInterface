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
public:
    Command(DefaultIO* dio):dio(dio){}
    virtual void execute()=0;
    virtual ~Command(){}
};

//-- command implement --

class uploadCommand: public Command {


};

class settingCommand: public Command {


};

class detectCommand: public Command {


};

class displayCommand: public Command {


};

class uploadAndAnalyzeCommand: public Command {

};

#endif //EX5_COMMANDS_H
