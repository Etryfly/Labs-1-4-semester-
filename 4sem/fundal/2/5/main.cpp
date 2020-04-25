
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

    AVLTree tree;
    for (int i = 1; i < argc; ++i) {

        ifstream istream(argv[i]);
        while (!istream.eof()) {
            string line;
            getline(istream, line);
            vector<string> v = split(line);
            if (v.size() == 0) continue;

            const std::locale loc = std::locale(std::locale::classic(),
                                                new boost::posix_time::time_input_facet("%H:%M:%S%f"));
            std::istringstream is(v[1]);
            is.imbue(loc);

            boost::posix_time::ptime start;
            is >> start;

            Message msg(v[0], start, v[3]);

            tree.insert(msg);
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
                tree.getMessagesByName(tree.getRoot(), str, v);
                for (Message msg : v) {
                    cout << msg.name << " " << msg.time << " : " << msg.message << endl;
                }
            }
                break;



            case 4:
                return 0;
        }
    }
}