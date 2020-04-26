
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Message.h"

#include "AVLTreeNode.h"

using namespace std;

std::vector<string> split(string str) {

    string buf;
    std::vector<string> result;
    if (str == "") return result;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i]== ' ' || str[i] == '\t' || str[i] == 0 || i == str.size()){
            result.push_back(buf);
            buf.clear();
        } else {
            buf+=str[i];
        }
    }

    result.push_back(buf);

    return result;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cout << "Smthng wrong" << endl;
        return 0;
    }

    AVLTreeNode *tree = nullptr;
    for (int i = 1; i < argc; ++i) {

        ifstream istream(argv[i]);
        while (!istream.eof()) {
            string line;
            getline(istream, line);
            vector<string> v = split(line);
            if (v.size() == 0) continue;

            const std::locale loc = std::locale(std::locale::classic(),
                                                new boost::posix_time::time_input_facet("%H:%M:%s"));
            std::istringstream is(v[1]);
            is.imbue(loc);

            boost::posix_time::ptime time;
            is >> time;
           // cout << time;
            Message msg(v[0], time, v[3]);

            tree = tree->insert(tree, msg);
        }

        istream.close();
    }

    int n;

    while (true) {
        cout << "1. Вывод всех сообщений заданного пользователя \n"
                "2. Вывод сообщений пользователя для заданного временного интервала \n"
                "3. Вывод всех сообщений  из  заданного  временного  интервала \n"
                "4. Выход \n";

        cin >> n;

        switch( n) {
            case 1: {
                cout << "Введите имя пользователя\n";
                string str;
                cin >> str;
                vector<Message> v;
                tree->getMessagesByName(tree, str, &v);
                for (Message msg : v) {
                    cout << msg;
                }
            }
                break;

            case 2: {
                cout << "Введите временной интервал в формате HH:MM:SS.MLSCNS HH:MM:SS.MLSCNS \n";
                string t1;
                string t2;
                string name;
                cin >> t1 >> t2;
                cout << "Введите имя\n";
                cin >> name;

                const std::locale loc = std::locale(std::locale::classic(),
                                                    new boost::posix_time::time_input_facet("%H:%M:%s"));
                std::istringstream is(t1);
                is.imbue(loc);

                boost::posix_time::ptime time1;
                boost::posix_time::ptime time2;
                is >> time1;

                is.clear();

                is = istringstream(t2);
                is.imbue(loc);

                is >> time2;

                vector<Message> v;
                tree->getMessagesByUserInInterval(tree, time1, time2,name, &v);
                for (Message msg : v) {
                    cout << msg;
                }
            }
                break;

            case 3: {
                cout << "Введите временной интервал в формате HH:MM:SS.MLSCNS HH:MM:SS.MLSCNS \n";
                string t1;
                string t2;

                cin >> t1 >> t2;

                const std::locale loc = std::locale(std::locale::classic(),
                                                    new boost::posix_time::time_input_facet("%H:%M:%s"));
                std::istringstream is(t1);
                is.imbue(loc);

                boost::posix_time::ptime time1;
                boost::posix_time::ptime time2;
                is >> time1;

                is.clear();

                is = istringstream(t2);
                is.imbue(loc);

                is >> time2;

                vector<Message> v;
                tree->getMessagesInInterval(tree, time1, time2, &v);
                for (Message msg : v) {
                    cout << msg;
                }

            }
            break;

            case 4:
                return 0;
        }
    }
}