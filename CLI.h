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
    // you can add data members
public:

    //auto **commands = new Command*[6];
    Command **commands = new Command*[6];

    CLI(DefaultIO* dio);
    void start();
    virtual ~CLI();
};

#endif //EX5_CLI_H
