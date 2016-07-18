#include <iostream>

using std::cout;
using std::endl;

class Point {
public:
    Point(const Point &p) : x(p.x), y(p.y) 
        { cout << "copy constructor point x:" << x << " y:" << y << " this's addr:" << this << " p's addr:" << &p << endl; }
    
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) 
        { cout << "default constructor point x:" << x << " y:" << y << " this's addr:" << this << endl; } 

    Point &operator=(const Point & rvalue) {
        x = rvalue.x;  y = rvalue.y; 
        cout << "operator point x:" << x << " y:" << y << " this's addr:" << this << endl;
        return *this;
    }
    
    void print(void) const
        { cout << "my x:" << x << " y:" << y << " this's addr:" << this << endl; }
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
    Point testp(3, 4);
    //const Point &retp = foo_bar(testp);      /* 这里使用const & 就可以成功？而非const引用就不可以？ */
                                               /*: 个人猜测是因为没有源对象 或者说是看不到原对象因为毕竟是返回值 */
    //Point retp = foo_bar(testp);             /* 这里在函数返回的时候调用了拷贝构造函数，但将返回值传入对象中却不调用拷贝构造函数呢 */
                                               /*  个人感觉是编译器的原因：因为函数返回的对象如果再次使用拷贝构造的话，返回的对象就
                                                *  永远不会被使用， 这样浪费空间时间。 于是就直接将其地址给了返回对象。 */
    //Point *retpp = NULL;
    //*retpp = foo_bar(testp);
    //retp.print();
    Point oper_p(1, 2);
    oper_p = testp;                            /* 当不在定义处，而是已经初始化后的对象进行赋值时，会调用operator=*/
    oper_p.print();
    return 0;
}
