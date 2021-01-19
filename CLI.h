//
// Created by eliel on 11/01/2021.
//

#ifndef EX5_CLI_H
#define EX5_CLI_H

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
    DefaultIO* dio;
    hybridAndVec* struc;

public:
    Command **commands;
    Command **getCommands();
    void menuPrinter();
    float userChoice();

    CLI(DefaultIO* dio);
    void start();
    virtual ~CLI();
};

#endif //EX5_CLI_H
