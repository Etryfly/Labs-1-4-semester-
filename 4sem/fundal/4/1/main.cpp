#include <boost/algorithm/string.hpp>
#include <fstream>
#include <vector>

using namespace std;

bool maskF(string &str) {
    if (!(str[0] >= 'A' && str[0]<= 'Z')) {
        return false;
    }
    for (int i = 1; i < str.size(); ++i) {
        str[i] = 'x';
    }
    return true;
}

bool maskNameAndO(string &str) {
    if (str.size() == 0) return false;
    if (!(str[0] >= 'A' && str[0]<= 'Z')) {
        return false;
    }
    str[1] = '.';
    str.resize(2);
    return true;
}

bool maskCard(string& str){
    if (str.size() != 16) return false;
    for (int i = 3; i < 14; ++i) {
        str[i] = 'x';
    }
    return true;
}


bool maskEmail(string& str){
    string result = str;
    if (!isalpha(result[0])) return false;
    int indexOfA = -1;
    for (int i = 1; i < str.size(); ++i) {
        if (str[i] == '@') {
            indexOfA = i;
            break;
        }
        result[i]='x';
    }
    if (indexOfA == -1) return false;
    int indexOfDot = -1;

    for (int j = indexOfA + 1; j < str.size(); ++j) {
        if (str[j] == '.') {
            indexOfDot = j;
            break;
        }
        result[j] = 'y';
    }

    if (indexOfDot == -1) return false;

    str = result;
    return true;
}

bool maskIP(string& str){
    int count = 0;

    std::vector<std::string> results;

    boost::split(results, str, [](char c){return c == '.';});
    if (results.size() != 4) {
        return false;
    }
    for (int j = 0; j < 4; ++j) {
        for (int k = 0; k < results[j].size(); ++k) {
            if (!isdigit(results[j][k] )) return false;
        }
        if (!(stoi(results[j]) >= 0 && stoi(results[j]) <= 255)) return false;
    }
    str.clear();
    str.resize(0);
    for (int l = 0; l < 3; ++l) {
        str += "X.";
    }
    str += results[3];
    return true;
}

bool maskPhone(string& str) {
    if (str[0] != '+'  || !isdigit(str[1]) || str[2] != '(' || !isdigit(str[3]) || !isdigit(str[4]) || !isdigit(str[5]) ||
    str[6] != ')' || !isdigit(str[7]) || !isdigit(str[8]) || !isdigit(str[9]) || str[10] != '-' || !isdigit(str[11]) ||
            !isdigit(str[12]) || str[13] != '-' || !isdigit(str[14]) || !isdigit(str[15])) {
        return false;

    }
    str[3] = 'X';
    str[4] = 'X';
    str[5] = 'X';
    str[7] = 'X';
    str[8] = 'X';
    str[9] = 'X';
    return true;
}




int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        ifstream ifstream1(argv[i]);
        while (!ifstream1.eof()) {

            string line;
            getline(ifstream1, line);
            ifstream file(line);
            ofstream of("tmp");
            while (!file.fail()) {
                string dataLine;
                getline(file, dataLine);

                if (dataLine != "") {
                    std::vector<std::string> results;
                    boost::split(results, dataLine, [](char c) { return c == ' '; });

                    maskF(results[0]);
                    maskNameAndO(results[1]);
                    maskNameAndO(results[2]);
                    maskCard(results[3]);
                    maskEmail(results[4]);
                    maskIP(results[5]);
                    maskPhone(results[6]);
                    for (int j = 0; j < results.size(); ++j) {
                        of << results[j] << " ";
                    }
                    of << endl;
                }
            }
            of.close();
            file.close();
            ifstream tmp("tmp");
            ofstream out(line);
            while (!tmp.eof()) {
                string str;
                getline(tmp, str);
                out << str << endl;
            }
            tmp.close();
            out.close();
        }

    }
}