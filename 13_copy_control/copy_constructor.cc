#include <iostream>

using std::cout;
using std::endl;

class Point {
public:
    Point(const Point &p) : x(p.x), y(p.y) 
        { cout << "copy constructor point x:" << x << " y:" << y << " this's addr:" << this << " p's addr:" << &p << endl; }
    
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) 
        { cout << "default constructor point x:" << x << " y:" << y << " this's addr:" << this << endl; } 
    
    void print(void) const
        { cout << "my x:" << x << " y:" << y << " this's addr:" << this << endl; }
private:
    int x;
    int y;
};

Point global;

Point foo_bar(Point arg) {
    Point local = arg, *heap = new Point(global);
    heap = &local;
    Point pa[4] = { local, *heap};
    return *heap;
}

int main(void) {
    Point testp = {3, 4};
    const Point &retp = foo_bar(testp);   /* 为何这里使用const & 就可以成功？而非const引用就不可以？ */
    retp.print();
    //Point retp(foo_bar(testp));           /* 为何这里在函数返回的时候调用了拷贝构造函数，但将返回值传入对象中却不调用拷贝构造函数呢 */
    //Point *retpp = NULL;
    //*retpp = foo_bar(testp);
    return 0;
}
