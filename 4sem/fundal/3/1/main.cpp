#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Var.cpp"

using namespace std;

std::vector<string> split(string str, char separator) {
    string buf;
    std::vector<string> result;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == separator || str[i] == 0 || i == str.size()) {
            result.push_back(buf);
            buf.clear();
        } else {
            buf += str[i];
        }
    }

    if (buf[buf.size() -1 ] == ';') {
        buf.resize(buf.size() - 1);
    }

    result.push_back(buf);

    return result;
}


void sortByPtr(vector<Var> *v) {
    sort(v->begin(), v->end());
}

void collectTrash(vector<Var> *v) {
    for (int i = 0; i < v->size(); ++i) {
        if ((*v)[i].memoryCell->links == 0) {
            (*v).erase((*v).begin() + i);
            i--;
        }
    }
}

int main(int argc, char *argv[]) {

    cout << "Введите размер кучи в байтах\n";
    int N;
    cin >> N;

    char heap[N];
    vector<Var> vars;
    for (int i = 1; i < argc; ++i) {
        ifstream istream(argv[i]);
        string line;
        while (!istream.fail()) {
            getline(istream, line);
            if (line == "") continue;
            if (line.find('=') != string::npos) { // в строке есть =
                vector<string> words = split(line, '=');

                if (words[1].find("alloc") != string::npos) {
                    const char *p = words[1].c_str();
                    while (*p != '(') {
                        p++;
                    }
                    p++;
                    int n = atoi(p);

                    sortByPtr(&vars);
                    bool isFind = false;

                    for (int j = 1; j < vars.size(); ++j) {
                        if (vars[j - 1].memoryCell != vars[j].memoryCell &&  vars[j].memoryCell->ptr  - vars[j - 1].memoryCell->ptr - vars[j - 1].size >= n) {
                            Var v = Var(new MemoryCell(vars[j - 1].memoryCell->ptr + vars[j - 1].size));
                            v.size = n;
                            v.name = words[0];
                            isFind = true;
                            for (int k = 0; k < vars.size(); ++k) {
                                if (vars[k].name == words[0]) {
                                    vars[k].memoryCell->links--;

                                    vars.erase(vars.begin() + k);
                                    collectTrash(&vars);
                                    break;
                                }
                            }


                            vars.push_back(v);
                            break;
                        }
                    }
                    if (isFind) continue;
                    if (vars.size() == 0 || (heap != vars[0].memoryCell->ptr && heap + n <= vars[0].memoryCell->ptr)) {

                        Var v = Var(new MemoryCell(heap));
                        v.size = n;
                        v.name = words[0];
                        vars.push_back(v);
                    }   else {
                        if (!isFind &&
                            (vars[vars.size() - 1].memoryCell->ptr + vars[vars.size() - 1].size + n < heap + N + 1)) {

                            Var v = Var(new MemoryCell(vars[vars.size() - 1].memoryCell->ptr
                                    + vars[vars.size() - 1].size));
                            v.size = n;
                            v.name = words[0];
                            vars.push_back(v);
                        } else {
                            cout << words[0] <<  ": Место в куче не найдено" << endl;
                        }
                    }

                } else { // var1 = var2;
                    for (Var rval : vars) {
                        if (rval.name == words[1]) {
                            rval.memoryCell->links++;
                            for (int j = 0; j < vars.size(); ++j) {
                                if (vars[j].name == words[0]) {

                                    vars[j].memoryCell->links--;

                                    vars.erase(vars.begin() + j);
                                    break;
                                }
                            }
                            Var var = Var(rval.memoryCell);
                            var.name = words[0];
                            var.size = rval.size;

                            collectTrash(&vars);
                            vars.push_back(var);
                            break;
                        }
                    }
                }
            } else { // dealloc
                const char *p = line.c_str();
                while (*p != '(') {
                    p++;
                }
                p++;
                string name;
                while (*p != ')') {
                    name.push_back(*p++);
                }

                for (int j = 0; j < vars.size(); ++j) {
                    if (vars[j].name == name) {
                        vars[j].memoryCell->links --;

                        for (int k = 0; k < vars.size(); ++k) {
                            if (k != j && vars[k].memoryCell->ptr == vars[j].memoryCell->ptr) {

                                vars[k].memoryCell->links --;
                            }
                        }

                        collectTrash(&vars);
                        break;
                    }
                }

            }
        }
    }

    sortByPtr(&vars);
    char* ptr = heap;
    int countFree = 0;
    int maxFree = 0;
    int countBusy = 0;
    //,

    if (vars.size() == 0) {
        for (int i = 0; i < N; ++i) {
            cout << "-";
            countFree++;
            maxFree++;
        }
    } else {
        for (int i = 0; i < vars.size(); ++i) {
            int c = 0;
            while (ptr != vars[i].memoryCell->ptr && ptr != heap + N) {
                cout << "-";
                countFree++;
                ptr++;
                c++;
            }
            if (c > maxFree) maxFree = c;
            if (ptr >= vars[i].memoryCell->ptr + vars[i].size) continue;
            for (int j = 0; j < vars[i].size; ++j) {

                cout << "x";
                ptr++;
            }


        }
        while (ptr < heap + N) {
            cout << "-";
            ptr++;
        }
    }

    for (int l = 1; l < vars.size(); ++l) {
        if (vars[l-1].memoryCell->ptr + vars[l-1].size != vars[l].memoryCell->ptr) {
            countBusy ++;
        }
    }

    cout << "\nРазмер свободной памяти " << countFree << " байт" << endl;
    cout << "Размер самого длинного свободного блока " << maxFree << " байт" << endl;
    cout << "Количество занятых фрагментов памяти " << countBusy << endl;




}