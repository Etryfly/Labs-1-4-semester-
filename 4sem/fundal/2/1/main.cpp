

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
    for (int j = 0; j < wide.size(); ++j) {
        if (std::wcschr(L"аоуыиеёэюя", wide[j])) {
            count ++;
        }
    }
    return count;
}

string getWordWithEqualSize(string str, std::vector<string> dictionary) {

    vector<string> rng;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    std::wstring wide = converter.from_bytes(str);
    int size = getGlCount(str);
    int i,j;
    for (i = 0; i < dictionary.size(); ++i) {
        wstring tmp = converter.from_bytes(dictionary[i]);
        if (compareStr(tmp, wide)) {

            for (j = i; j < dictionary.size(); ++j) {
                if (getGlCount(dictionary[j]) == size && i != j) {
                    rng.push_back(dictionary[j]);
                }
            }

        }
    }

    if (rng.size() == 0) {
        for (j = 0; j < i; ++j) {
            if (getGlCount(dictionary[j]) == size) {
                rng.push_back(dictionary[j]);
            }
        }
    }

    if (rng.size() == 0) {
        return dictionary[rand() % dictionary.size() - 1];
    }

    return rng[rand() % rng.size()/2];


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
