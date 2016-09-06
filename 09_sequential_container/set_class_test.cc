#include <iostream>
#include <set>
#include <utility>
#include <assert.h>

using namespace std;

//仅仅是为了set中的结构体判断

class Data{
public:
    Data(int a_, int b_) :
        a(a_), b(b_) {
        if (a > b) std::swap(a, b);    
    }

    Data(const Data &rhl) :
        a(rhl.a), b(rhl.b) { 
        assert(a<=b);
    }

    ~Data() { }

    bool operator==(const Data &rhl) const {
        if (a == rhl.a && b == rhl.b)
            return true;
        if (a == rhl.b && b == rhl.a)
            return true;
        return false;
    }
    
    //必须实现此方法
    //set中才可以find / count
    //记住两个const
    bool operator<(const Data &rhl) const {
        if (a == rhl.a)
            return b < rhl.b;
        else
            return a < rhl.a;
    }

    int a;
    int b;
};

int main() {
    set<Data> sd;
    Data d1(1, 3), d2(3, 1), d3(1, 1);
    cout << "d1 == d2: ";
    if (d1 == d2)
        cout << " true";
    else
        cout << " false";
    cout << endl;
    
    sd.insert(d1);
    cout << "set<Data> d1 count:" << sd.count(d1) << endl;
    cout << "set<Data> d2 count:" << sd.count(d2) << endl;
    cout << "set<Data> d3 count:" << sd.count(d3) << endl;
    return 0;
}
