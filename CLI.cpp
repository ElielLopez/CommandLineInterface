//
// Created by eliel on 11/01/2021.
//

#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
}

void CLI::start(){

    int option = 0;
    //commands[0] = new uploadCommand();

    while(true) {
        dio->write("Welcome to the Anomaly Detection Server.\n");


        option = 6;
        if(option == 6) {
            return;
        }
        return; // TODO - remove later
    }
}

CLI::~CLI() {

}
