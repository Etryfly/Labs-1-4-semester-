

#include <fstream>
#include <vector>
#include <algorithm>
#include <boost/locale.hpp>
#include <boost/algorithm/string.hpp>
#include <codecvt>

using namespace std;




std::vector<string> split(string str) {
    string buf;
    std::vector<string> result;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i]== ' '){
            result.push_back(buf);
            buf.clear();
        } else {
            buf+=str[i];
        }
    }
    return result;
}

void importDictionary(std::vector<string> *dictionary) {
    std::ifstream istream("zdb-win.txt");
    string str;

    while (istream >> str) {

        dictionary->push_back(str);
    }

    istream.close();
}

bool compareStr( wstring a,  wstring b) {
    if (a.size() != b.size()) return false;



    for (int j = 0; j < a.size(); ++j) {
        if (towlower(a[j]) != towlower(b[j])) return false;
    }

    return true;
}

int getGlCount(string str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(str);
    int count = 0;
    for (int j = 0; j < str.size(); ++j) {
        if (std::strchr("аоуыиеёэюя", str[j])) {
            count ++;
        }
    }
    return count;
}

string getWordWithEqualSize(string str, std::vector<string> dictionary) {


    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    std::wstring wide = converter.from_bytes(str);

    for (int i = 0; i < dictionary.size(); ++i) {
        wstring tmp = converter.from_bytes(dictionary[i]);
        if (compareStr(tmp, wide)) {

            for (int j = i; j < dictionary.size(); ++j) {
                if (getGlCount(dictionary[j]) == getGlCount(str) && i != j) {
                    return dictionary[j];
                }
            }

            return "Error";

        }
    }


    for (int k = dictionary.size(); k > 0 ; --k) {
        if (dictionary[k].size() == str.size()) return dictionary[k];
    }


}

int main(int argc, char* argv[]) {
    std::setlocale(LC_ALL, "");
    std::vector<std::string> dictionary;
    importDictionary(&dictionary);

    std::ifstream ifStream(argv[1]);
    std::ofstream ofStream(argv[2]);
    if (!ifStream.is_open()) return 3;
    if (!ofStream.is_open()) return 4;
    int coma = 0, point = 0;
    std::string str;
    while (true) {
        if (ifStream.eof()) break;
        getline(ifStream, str);


        std::vector<std::string> words = split(str);


        for (std::string s : words) {
            coma = 0, point = 0;

            if (s[s.size()-1] == '.' ) {
                s[s.size()-1] = 0;
                point = 1;
            }

            if (s[s.size()-1] == ',' ) {
                s[s.size()-1] = 0;
                coma = 1;
            }
            s = getWordWithEqualSize(s, dictionary);
            ofStream << s;
            if (coma) ofStream << ',';
            if (point) ofStream << '.';
            ofStream << " ";

        }
        ofStream << endl;

    }

    ofStream.close();
    ifStream.close();
}
