#include <iostream>

using namespace std;

//pimpl : pointer to  implementation
class WidgetImpl {
public:
    WidgetImpl() : data_(0) {}
    WidgetImpl(int d) : data_(d) {}
    WidgetImpl(const WidgetImpl& rhl) : 
        data_(rhl.data_) {}

    WidgetImpl& operator=(const WidgetImpl& rhl){
        data_ = rhl.data_;
        return *this;
    }

    int data() const{
        return data_;
    }
    
    //if WidgetImpl is very complex
    //u can write operator= like this:
    /*
     * WidgetImpl& operator=(const WidgetImpl& rhl) {
     *      Widget temp(rhl);
     *      swap(temp);
     *      return *this;
     * }
     *   or 
     * WidgetImpl& operator=(WidgetImpl rhl) {
     *      swap(rhl);
     *      return *this;
     * }
     * ===> the two function is best!
     */

private:
    int data_;
};

//因为没有调用WidgetImpl's private，所以不需要声明为friend
ostream& operator<<(ostream &out, const WidgetImpl& wi) {
    out << wi.data();
    return out;
}

class Widget {
public:
    Widget() : pImpl(NULL) {}
    Widget(int d) : pImpl(NULL) {
        pImpl = new WidgetImpl(d);
    }
    //三五法则
    Widget(const Widget& rhl) {
        pImpl = new WidgetImpl();
        *pImpl = *(rhl.pImpl);
    }
    ~Widget() {
        if (pImpl != NULL)
            delete pImpl;
    }
 
    //1.public-member-swap
    void swap(Widget& other) throw() {//throw():表示不会抛出异常 C++03， noexcept(true)也是,C++11
        using std::swap;       
        //C++命名查找法则，如果有pImpl有自己的swap会调用之(实参取决之查找规则)
        //如果没有，会接下来查找std::swap的pImpl类型的专属特化版
        //都没有，就调用非一般化的template swap
        swap(pImpl, other.pImpl);
    }

    Widget& operator=(const Widget& rhl) {
        Widget temp(rhl);
        //using std::swap;
        swap(temp);
        return *this;
    }

    void print() const {
        cout << *pImpl << endl;
    }
private:
    WidgetImpl *pImpl;
};

//2.swap
//no-member-no-friend swap
void swap(Widget &lhl, Widget &rhl) throw() {
    lhl.swap(rhl);
}

//3.swap
//对于非template classes
//特化std::swap
namespace std {
    template<>
    void swap<Widget>(Widget &lhl, Widget &rhl) {
        lhl.swap(rhl);
    }
}

int main() {
    Widget w1(1);
    w1.print();
    w1 = 2;
    w1.print();
    return 0;
}
