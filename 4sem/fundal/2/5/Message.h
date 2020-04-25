//
// Created by etryfly on 13.04.2020.
//
#include "boost/date_time/posix_time/ptime.hpp"

#ifndef INC_2_MESSAGE_H
#define INC_2_MESSAGE_H

#include <string>

class Message {
public:
    std::string name;
    boost::posix_time::ptime time;
    std::string message;

    Message(std::string name, boost::posix_time::ptime time, std::string msg) : name{name}, time{time}, message{msg} {

    }

    bool operator > (const Message& msg) {
        if (name > msg.name) {
            return true;
        } else if (name < msg.name) {
            return false;
        } else if (time > msg.time) {
            return true;
        } else {
            return false;
        }
    }

    bool operator < (const Message& msg) {
        return !(*this > msg) && (*this != msg);
    }

    friend  bool operator == (const Message& msg1, const Message& msg2);
    friend  bool operator != (const Message& msg1, const Message& msg2);
};

bool operator == (const Message& msg1, const Message& msg2) {
    return msg1.name == msg2.name && msg1.time == msg2.time;
}

bool operator != (const Message& msg1, const Message& msg2) {
    return !(msg1 == msg2);
}

#endif //INC_2_MESSAGE_H
