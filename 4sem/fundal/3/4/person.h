//
// Created by etryfly on 30.04.2020.
//

#ifndef INC_1_PERSON_H
#define INC_1_PERSON_H

#include <string>
#include <vector>

class Person {
public:
    std::string name;
    long id;
    std::vector<long> friends;
    bool infected;
    bool healed;
    bool checked;
};

#endif //INC_1_PERSON_H
