#include <jsoncpp/json/json.h>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "person.h"

using namespace std;

unordered_map<long, Person> ppls;

void sharePlagueWithFriends(Person& p , double p1) {
    p.checked = true;
    for (long id : p.friends) {
        int rng = rand() % 100 + 1;
        if (rng <= p1*100) {
            if (ppls.count(id) == 1) {
                unordered_map<long, Person>::iterator it = ppls.find(id);
                if (it != ppls.end() && !it->second.checked) {
                    it->second.infected = true;
                    sharePlagueWithFriends(it->second, p1);
                }
            }
        }
    }
}

int main() {
    srand(time(0));
    double p1,p2;
    cout << "p1=";
    cin >> p1;
    cout << endl << "p2=";
    cin >> p2;
    cout << endl << "Идет чтение графа из файла\n";

    std::ifstream file("graph.json", std::ifstream::binary);
    Json::Value data;

    Json::Reader reader;
    bool parsingSuccessful = reader.parse( file, data, false );
    file.close();
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        std::cout  << reader.getFormatedErrorMessages()
                   << "\n";
    }


    Json::Value::Members members = data.getMemberNames();


    for (int i = 0; i < members.size(); ++i) {
        Person p;
        p.name = data[members[i]]["first_name"].asString() + " " + data[members[i]]["last_name"].asString();
        p.id = stoi(members[i]);

        Json::Value friends = data[members[i]]["friends_id"];
        for (int j = 0; j < friends.size(); ++j) {
            p.friends.push_back(stol(friends[j].asString()));
        }
        p.infected = false;
        p.healed = false;
        p.checked = false;
        ppls.insert(pair<long, Person>(p.id, p));
    }
    ppls.begin()->second.infected = true;
    sharePlagueWithFriends(ppls.begin()->second, p1);
    for (unordered_map<long, Person>::iterator  it = ppls.begin();it!=ppls.end(); ++it) {

        if (it->second.infected && rand() % 100 <= p2*100 ) {
            it->second.infected = false;
            it->second.healed = true;
        }

    }


    int n;
    while (true) {
        cout << "1. Вывод всех не заразившихся людей\n"
                "2. Вывод всех исцелившихся\n"
                "3. Исцелившиеся люди, окружение которых не исцелилось\n"
                "4. Не заразившиеся люди, окружение которых заразилось\n"
                "5. Выход\n";


        cin >> n;

        switch (n) {

            case 1:
                for (pair<long, Person> p : ppls) {
                    if (!p.second.infected && !p.second.healed) {
                        cout << p.second.id << " " << p.second.name << endl;
                    }
                }
                break;

            case 2:
                for (pair<long, Person> p : ppls) {
                    if (p.second.healed) {
                        cout << p.second.id << " " << p.second.name << endl;
                    }
                }
                break;

            case 3:
                for (pair<long, Person> p : ppls) {
                    bool flag = false;
                    if (p.second.healed) {
                        for (long id : p.second.friends) {
                            if (!ppls[id].healed) {
                                continue;
                            } else {
                                flag = true;
                            }
                        }
                        if (!flag) {
                            cout << p.second.id << " " << p.second.name << endl;
                        }
                    }
                }
                break;

            case 4:
                for (pair<long, Person> p : ppls) {
                    bool flag = false;
                    if (!p.second.infected && !p.second.healed) {
                        for (long id : p.second.friends) {
                            if (ppls[id].infected) {
                                continue;
                            } else {
                                flag = true;
                            }
                        }
                        if (!flag) {
                            cout << p.second.id << " " << p.second.name << endl;
                        }
                    }
                }
                break;



            case 5:
                return 0;

            default:
                cout << "Попробуйте еще раз \n";
                break;
        }

    }
}