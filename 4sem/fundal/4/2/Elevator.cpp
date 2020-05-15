#include <vector>
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

public:
    std::vector<Passenger> passengers;

    void addPassenger(Passenger p) {
        passengers.push_back(p);
    }

    void calculateLoad() {
        currentLoad = 0;
        for (int i = 0; i < passengers.size(); ++i) {
            currentLoad += passengers[i].weight;
        }
    }

    bool isEmpty() {
        return passengers.empty();
    }




    bool moveOneSecond() {
        if (s == OPEN) return false;

        if (secondsFromFloor == currentLoad * 5) {
            if (s == UP) floor ++;
            if (s == DOWN ) floor --;
            secondsFromFloor = 0;
            return true;
        }
        secondsFromFloor ++;
        return false;
    }

    bool isOverLoad() {
        return currentLoad > maxLoad;
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
    }
};