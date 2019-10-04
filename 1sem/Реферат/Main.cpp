#include <iostream>
using namespace std;
class A {
private:
    static int count;
public:
    void writeCount() {
        cout << count << endl;
    }
    void countPlus() {
        count++;
    }
};
int A::count = 0;
int main() {
    A a1;
    A a2;
    A a3;
    a1.countPlus();
    a2.countPlus();
    a3.countPlus();
    a1.writeCount(); //3
    a2.writeCount(); //3
    a3.writeCount(); //3
}
