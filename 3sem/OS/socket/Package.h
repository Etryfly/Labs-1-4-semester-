//
// Created by etryfly on 30.11.2019.
//

#ifndef FUNDAL_PACKAGE_H
#define FUNDAL_PACKAGE_H


//COMMANDS
#define SEND_NAME 0
#define SEND_FILE 1
#define SEND_CONFIRM 2
#define SEND_STOP 3


#define PORT 6666

typedef struct Package {
    char proto;
    char command;
    int count;
    int number;
    short size;
    char data[1024];
} Package;


#endif //FUNDAL_PACKAGE_H
