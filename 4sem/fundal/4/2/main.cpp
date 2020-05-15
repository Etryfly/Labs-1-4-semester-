#include <iostream>
#include <fstream>
#include "Elevator.cpp"
using namespace std;

bool isPassInVectorByName(std::vector<Passenger> v, Passenger p) {
    for (int i = 0; i < v.size(); ++i) {
        if (v[i].name == p.name) return true;
    }
    return false;
}

bool isPassLastOnFloor(vector<vector<Passenger>> p) {
    for (int i = 0; i < p.size(); ++i) {
        if (p[i].empty()) {
            continue;
        } else {
            return true;
        }
    }

    return false;
}

bool isPassLastInElevator(vector<Elevator> e) {
    for (int i = 0; i < e.size(); ++i) {
        if (e[i].isEmpty()) {
            continue;
        } else {
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    int n,k;

    cout << "Введите количество этажей: ";
    cin >> n;
    cout << endl << "Введите количество лифтов:";
    cin >> k;
    vector<Elevator> elevators;
    for (int i = 0; i < k; ++i) {
        elevators.push_back(Elevator(n * 40));
    }
    vector<vector<Passenger>> floors(n);

    bool isServed[n];
    for (int i1 = 0; i1 < n; ++i1) {
        isServed[i1] = false;
    }

    int minTime = 0;
    int maxTime = 0;
    int curTime = 0;

    ifstream istream(argv[1]);
    ofstream out("out");
    while (!istream.eof()) {
        Passenger p;
        istream >> p.name;
        istream >> p.weight;
        istream >> p.currentFloor;
        p.currentFloor --;
        string time;
        istream >> time;
        int t = (time[3] - '0') * 10 + time[4] - '0';
        t+= 60*((time[0] - '0') * 10 + (time[1] - '0'));
        p.timeOfCall = t;
        istream >> p.targetFloor;
        if (t > maxTime) maxTime = t;
        if (t < minTime) minTime = t;

        floors[p.currentFloor].push_back(p);
    }

    for (int j = minTime; j <= maxTime || isPassLastOnFloor(floors) || isPassLastInElevator(elevators); ++j) {
        curTime = j;
        for (int i1 = 0; i1 < n; ++i1) {
            for (int i = 0; i < floors[i1].size(); ++i) {
                for (int c = 0; c < floors[i1].size(); ++c) {
                    if (c != i && isPassInVectorByName(floors[i1][i].meetings, floors[i1][c]) && floors[i1][c].timeOfCall > curTime
                    && floors[i1][i].timeOfCall <= curTime) {
                        floors[i1][i].meetings.push_back(floors[i1][c]);
                        floors[i1][c].meetings.push_back(floors[i1][i]);
                    }
                }
            }
        }


        for (int i = 0; i < elevators.size(); ++i) {
            if (elevators[i].getState() != Elevator::OPEN) { // лифт в пути
                if (elevators[i].moveOneSecond()) { // лифт доехал до этажа
                    elevators[i].setState(Elevator::OPEN);
                    for (int l = 0; l < elevators[i].passengers.size(); ++l) { // проверка выхода из лифта
                        if (elevators[i].passengers[l].targetFloor == elevators[i].getFloor()) {
                            out << elevators[i].passengers[l].name << " " <<
                            elevators[i].passengers[l].timeOfCall << " " <<
                            elevators[i].passengers[l].timeOfLoad << " " <<
                            curTime - elevators[i].passengers[l].timeOfLoad << " " <<
                            endl;
                            for (int m = 0; m < elevators[i].passengers[l].meetings.size(); ++m) {
                                out << elevators[i].passengers[l].meetings[m].name << " ";
                            }
                            elevators[i].passengers.erase(elevators[i].passengers.begin() + l);
                            l--;

                            // Добавить лог выхода
                        }
                    }

                    
                }
            } else { // лифт стоит на этаже
                for (int m = 0; m < floors[elevators[i].getFloor()].size(); ++m) { //
                    if (floors[elevators[i].getFloor()][m].timeOfCall <= curTime) { // пассажир ждет
                        floors[elevators[i].getFloor()][m].timeOfLoad = curTime;

                        for (int l = 0; l < elevators[i].passengers.size(); ++l) {
                            elevators[i].passengers[l].meetings.push_back(floors[elevators[i].getFloor()][m]);
                        }
                        elevators[i].addPassenger(floors[elevators[i].getFloor()][m]);
                        elevators[i].calculateLoad();
                        if (elevators[i].isOverLoad()) {
                            // Добавить лог перегрузки
                            elevators[i].passengers.pop_back();
                            break;
                        } else {
                            floors[elevators[i].getFloor()].erase(floors[elevators[i].getFloor()].begin() + m);
                            // Удаляем m пассажира с этажа, т.к. он зашел в лифт
                            m--;
                        }
                        
                    }
                }
                
                if (elevators[i].isEmpty()) { // лифт свободен, можно проверить вызовы на других этажах
                    int nearestFloorWithPass = -1;
                    int minD = n;
                    int curFloor = elevators[i].getFloor();
                    for (int l = 0; l < n ; ++l) {
                        for (int m = 0; m < floors[l].size(); ++m) {
                            if (floors[l][m].timeOfCall <= curTime) {
                                if (minD >= abs(curFloor - l)) {
                                    minD = abs(curFloor - l);
                                    nearestFloorWithPass = l;
                                }
                            }
                        }
                    }


                    if (nearestFloorWithPass != -1) {
                        elevators[i].setState(Elevator::CLOSE);
                        if (curFloor - nearestFloorWithPass > 0) {
                            elevators[i].setState(Elevator::DOWN);
                        } else if (curFloor - nearestFloorWithPass < 0 ) {
                            elevators[i].setState(Elevator::UP);
                        } else {
                            continue;
                        }
                    }
                } else { //считаем, куда лифт поедет с пассажирами
                    elevators[i].setState(Elevator::CLOSE);
                    int curFloor = elevators[i].getFloor();
                    int target = elevators[i].passengers[0].targetFloor;
                    if (curFloor - target > 0) {
                        elevators[i].setState(Elevator::DOWN);
                    } else if (curFloor - target < 0 ) {
                        elevators[i].setState(Elevator::UP);
                    }
                }
            }
        }
    }

    istream.close();
    out.close();
}