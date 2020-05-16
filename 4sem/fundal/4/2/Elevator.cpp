#include <vector>
#include <iostream>
#include "Passenger.cpp"

class Elevator {
public:
    enum state {
        OPEN, CLOSE, UP, DOWN
    };



private:

    int secondsFromFloor;
    state s;
    int maxLoad;
    int currentLoad;
    int floor;

    int timeOfWait;
    int timeOfWork;
    int sumWork;
    int maxWork;
    int countOfOverload;
public:
    std::vector<Passenger> passengers;

    void addPassenger(Passenger p) {
        passengers.push_back(p);
        if (currentLoad > maxLoad) countOfOverload ++;
        else sumWork += p.weight;

    }

    void calculateLoad() {
        currentLoad = 0;
        for (int i = 0; i < passengers.size(); ++i) {
            currentLoad += passengers[i].weight;
        }

        if (currentLoad > maxLoad) countOfOverload ++;
        else if (maxWork < currentLoad) maxWork = currentLoad;


    }

    bool isEmpty() {
        return passengers.empty();
    }




    bool moveOneSecond() {
       // std::cout << floor << " " << currentLoad << std::endl;
        if (s == OPEN) return false;

        if (secondsFromFloor == currentLoad * 5) {
            if (s == UP) floor ++;
            if (s == DOWN ) floor --;
            secondsFromFloor = 0;
            return true;
        }
        secondsFromFloor ++;
        timeOfWork++;
        return false;
    }

    void waitOneSec() {
        timeOfWait++;
    }

    bool isOverLoad() {
        return currentLoad > maxLoad;
    }

    int getTimeOfWait() const {
        return timeOfWait;
    }

    int getTimeOfWork() const {
        return timeOfWork;
    }

    int getSumWork() const {
        return sumWork;
    }

    int getMaxWork() const {
        return maxWork;
    }

    int getCountOfOverload() const {
        return countOfOverload;
    }

    int getFloor() {
        return floor;
    }

    state getState() const {
        return s;
    }

    int getMaxLoad() const {
        return maxLoad;
    }

    int getCurrentLoad() const {
        return currentLoad;
    }

    void setState(state st) {
        s = st;
    }



    Elevator(int maxLoad) : maxLoad{maxLoad}, currentLoad{0} {
        s = OPEN;
        floor = 0;
        secondsFromFloor = 0;
        timeOfWait=0;
        timeOfWork=0;
        sumWork=0;
        maxWork=0;
        countOfOverload=0;
    }
};