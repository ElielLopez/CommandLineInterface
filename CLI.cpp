#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    //Command **commands = new Command*[6];
    this->commands = new Command*[6];
    commands[0] = new uploadFile(dio);
    commands[1] = new algorithmSetting(dio);
    commands[2] = new anomalyDetection(dio);
    commands[3] = new displayResults(dio);
    commands[4] = new uploadAndAnalayze(dio);
    commands[5] = new exitServer(dio); //TODO call destructor

}

void CLI::menuPrinter() {
    dio->write("Welcome to the Anomaly Detection Server.\n");
    dio->write("Please choose an option:\n");
    for(int i = 0; i < 6; i++) {
        dio->write(commands[i]->getDescription() + "\n");
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
//    float *opt = &optSelected;

    while(true) {
        menuPrinter();
        //userChoice();

        optSelected = userChoice();
        if(optSelected == 6) {
            break;
        }
//        dio->read(opt);
//        if(optSelected == 6) {
//            commands[5]->execute();
//        }
//        commands[(int)optSelected - 1]->execute();

//        int option = stoi(dio->read());
//        if(option == 6) {
//            //commands[option - 1]->execute();
//            for(int j = 0; j < 6; j++) {
//                delete commands[j];
//            }
//            delete[] commands;
//            return;
//        }

        commands[(int)optSelected - 1]->execute();
        return;
    }
}

CLI::~CLI() {
}
