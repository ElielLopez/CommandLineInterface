#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    //commands = new Command*[6];
    commands[0] = new uploadFile(dio);
    commands[1] = new algorithmSetting(dio);
    commands[2]; // = new anomalyDetection(dio);
    commands[3]; // = new displayResults(dio);
    commands[4]; // = new uploadAndAnalayze(dio);
    commands[5]; // = new exit(); //TODO call destructor

}

void CLI::menuPrinter() {
    dio->write("Welcome to the Anomaly Detection Server.\n");
    dio->write("Please choose an option:\n");
    for(int i = 0; i < 2; i++) {
        dio->write(commands[i]->getDescription() + "\n");
    }
}

void CLI::start(){

    float optSelected = 0;

    while(true) {
        menuPrinter();
        return;
    }
}


CLI::~CLI() {
}
