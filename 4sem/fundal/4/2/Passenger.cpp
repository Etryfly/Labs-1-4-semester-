
#include <string>
#include <vector>

class Passenger {
public:
    int weight;
    int currentFloor;
    int targetFloor;
    std::string name;
    int timeOfCall;
    int timeOfLoad;
    std::vector<Passenger> meetings;
};