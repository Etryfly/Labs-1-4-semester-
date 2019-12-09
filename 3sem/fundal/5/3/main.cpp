


#include <cctype>
#include <cstdio>
#include <iostream>

using namespace std;



int lenOfInt(int i) {
    int count = 0;
    if (i < 0) count ++;
    while (i != 0) {
        i/=10;
        count++;
    }
    return count;
}

int countOfAlphaInStr(char* str) {
    int count = 0;
    while (*str) {
        if (isalpha(*str)) {
            count++;
        }
        str++;
    }
    return count;
}

class Monom {
private:
    int count;
    char *vars;
    int *degrees;
    int ks;

public:
    Monom(char* str) {

        char* ptr = str;
        count = countOfAlphaInStr(str);

        vars = new char[count];
        degrees = new int[count];
        int i = 0;
        if (*ptr == '<') {
            ptr++;
        }
        if (isdigit(*ptr)) { //5*x^2y^3z
            sscanf(ptr, "%d", &ks);
            ptr += lenOfInt(ks);
        } else {
            ks = 1;
        }
        while (*ptr != '>' && *ptr != 0) {

            if (*ptr == '*') {
                ptr++;
                sscanf(ptr, "%c", &vars[i]);
                ptr++;
            } else if (isalpha(*ptr)) {
                sscanf(ptr, "%c", &vars[i]);
                ptr++;
            }
            if (*ptr == '^') {
                ptr++;
                sscanf(ptr, "%d", &degrees[i]);
                ptr+= lenOfInt(degrees[i]);
            } else if (*ptr){
                degrees[i] = 1;
                if (*ptr == '>') break;
                ptr++;
            }
            i++;
        }
    }


    ~Monom() {
        delete []degrees;
        delete []vars;
    }


    friend Monom operator * (const Monom & left, const Monom& right);
    friend Monom operator / (const Monom & left, const Monom& right);
    friend istream& operator >> (istream& in, Monom& right);
    friend ostream& operator << (ostream& out, const Monom& right);

    Monom&operator *=(const Monom& right) {
        *this = *this * right;
        return *this;
    }

    void setKs(int k) {
        this->ks = k;
    }

    void setDegrees(int* d) {
        degrees = d;
    }

    void setVars(char* v) {
        vars = v;
    }

    char* getVars() {
        return vars;
    }

    int getKs() {
        return ks;
    }

    int getCount() {
        return count;
    }

    void setCount(int c) {
        count = c;
    }

    void print() {
        cout << *this;
        cout << endl;
    }




};

istream& operator >> (istream &in, Monom & right) {
    char buf[BUFSIZ];
    in >> buf;
    right = Monom(buf);
    return in;
}

ostream &operator<<(ostream& out,const Monom &right) {
    if (right.ks != 0) {
        cout << right.ks << '*';
    }
    for (int i = 0; i < right.count; ++i) {
        cout << right.vars[i];
        if (right.degrees[i] != 0 && right.degrees[i] != 1) {
            cout << "^" << right.degrees[i];
        }
    }
    return out;
}

Monom operator*(const Monom &left, const Monom &right) {
    Monom result = left;
    result.ks *= right.ks;
    for (int i = 0; i < right.count; ++i) {
        for (int j = 0; j < left.count; ++j) {
            if (right.vars[i] == result.vars[j]) {
                result.degrees[j] += right.degrees[i];
                break;
            }  else {
                result.vars[result.count] = right.vars[i];
                result.degrees[result.count] = right.degrees[i];
                result.count++;
            }
        }
    }
    return result;
}

int main() {
    Monom a("<5*x^2>");
    a.print();

    Monom b("<3*x^5y^2");
    b.print();

    Monom c = a;
    c *= b;
    c.print();
}