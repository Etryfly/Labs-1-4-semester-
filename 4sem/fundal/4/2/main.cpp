#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;


void QUIET (string z, vector <bool> och){
    string r;
    for (int i=6; i>=z.size()-1; i++){
        r.push_back(z[i]);

    }

    int tmp = atoi(r.c_str());
    och[tmp]=true;
}



void COMEot (string z, vector <bool> och){
    string r;
    for (int i=6; i<=z.size()-1; i++){
        r.push_back(z[i]);
    }
    int tmp = atoi(r.c_str());
    int t=och.size()-tmp;
    och.resize(t);
}








void COME (string z, vector <bool> och){
    string r;
    for (int i=5; i<=z.size()-1; i++){
        r.push_back(z[i]);
    }
    int tmp = atoi(r.c_str());
    int t=och.size()+tmp;
    och.resize(t);
    for (int i=och.size()-1-tmp; i<=och.size()-1; i++){
        och[i]=true;
    }
}



void WORRY_C (string z, vector <bool> och){
    int sch=0;
    for (int i=0; i<=och.size()-1; i++){
        if (och[i]==false){
            sch++;
        }
    }
    cout << sch;
}



void WORRY (string z, vector <bool> och){
    string r;
    for (int i=5; i<=z.size()-1; i++){
        r.push_back(z[i]);
    }
    int tmp = atoi(r.c_str());
    och[tmp]=false;
}




int main () {
    int q;
    cin>>q;
    vector <string> X;
    vector <bool> och(1);
    och[0]=true;
    int tmp;
    string z;
    for (int i=0; i<=q-1; i++){
        getline (cin, X[i]);
    }
    for (int i=0; i<=q-1; i++){ //razbor elementov
        if (X[i][0]=='Q'){
            z=X[i];
            QUIET(z,och);
        }
        else if (X[i][0]=='C'){
            if (X[i][5]=='-'){
                z=X[i];
                COMEot(z, och);
            } else {
                z=X[i];
                COME(z, och);
            }
        }  else if (X[i][0]=='W') {
            if (X[i][6]=='C'){
                z=X[i];
                WORRY_C(z, och);
            } else {
                z=X[i];
                WORRY(z, och);
            }

        }
    }
    //cout << "yse";
    return 0;
}
