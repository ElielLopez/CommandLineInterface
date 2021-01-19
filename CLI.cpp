#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->struc = new hybridAndVec;
    //Command **commands = new Command*[6];
    this->commands = new Command*[6];
    this->commands[0] = new uploadFile(dio, struc);
    this->commands[1] = new algorithmSetting(dio, struc);
    this->commands[2] = new anomalyDetection(dio, struc);
    this->commands[3] = new displayResults(dio, struc);
    this->commands[4] = new uploadAndAnalayze(dio, struc);
    this->commands[5] = new exitServer(dio, struc); //TODO call destructor

}

Command** CLI::getCommands() {
    return this->commands;
}

void CLI::menuPrinter() {
    dio->write("Welcome to the Anomaly Detection Server.\n");
    dio->write("Please choose an option:\n");
    for(int i = 0; i < 6; i++) {
        dio->write(this->commands[i]->getDescription() + "\n");
    }
}

float CLI::userChoice() {
    float opt;
    float *option = &opt;
    dio->read(option);
    return opt;
}

void CLI::start(){

    float optSelected = 0;

    while(true) {

        menuPrinter();
        optSelected = userChoice();

        if(optSelected == 6) {
            break;
        }

        Command** commands = getCommands();
        commands[(int)optSelected - 1]->execute();
    }
}

CLI::~CLI() {
}
