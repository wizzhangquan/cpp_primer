#include <iostream>

using namespace std;

class CopyTest {
public:
    static CopyTest& getInstance() {
        static CopyTest instance;
        return instance;
    }

    CopyTest() : a(1) { 
        cout << "default construct"<< endl;
    }

    ~CopyTest() { cout << __func__ << endl; }

    CopyTest(const CopyTest& s) {
        a = s.a;
        cout << "copy construct"<< endl;
    }

    CopyTest& operator=(const CopyTest &rhl) {
        cout << "operator =" << endl;
        a = rhl.a;
        return *this;
    }

private:
    int a;
};

int main() {
    CopyTest &a = CopyTest::getInstance();
    //auto 这里是直接转换为CopyTest 而不是CopyTest &
    auto &b = a;
    return 0;
}
