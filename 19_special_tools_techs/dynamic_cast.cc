#include <iostream>
#include <typeinfo>

using namespace std;

//利用typeid来实现equal operator==

class A{
    friend bool operator==(const A&, const A&);
public:
    A(char a = 'a') : a_(a) {cout << "A constructor" << endl;}
    virtual ~A() {cout << "A destructor" << endl;}
    virtual void print() const {cout << "A print : " << a_ << endl;}
protected:
    virtual bool equal(const A &that) const {
        return a_ == that.a_; 
    }
private:
    char a_;
};

bool operator==(const A &lhs, const A &rhs) {
    return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}

class B : public A {
public:
    B(char b = 'b', char a = 'a') : A(a), b_(b) {cout << "B constructor" << endl;}
    virtual ~B() {cout << "B destructor" << endl;}
    virtual void print() const {cout << "B print : " << b_ << endl;}
protected:
    virtual bool equal(const B &that) const {
        const B &r = dynamic_cast<const B&>(that);
        return A::equal(r) && b_ == r.b_;
    }
private:
    char b_;
};

class C : public B {
public:
    C(char c = 'c', char b = 'b', char a = 'a') : B(b, a) , c_(c) {
        cout << "C constructor" << endl;
    }
    virtual ~C() {cout << "C destructor" << endl;}
    virtual void print() const {cout << "C print " << c_ <<  endl;}
protected:
    virtual bool equal(const C &that) const {
        const C &r = dynamic_cast<const C&>(that);
        return B::equal(r) && c_ == r.c_;
    }
private:
    char c_;
};

void judge_pA_equal(const A &p1, const A &p2) {
    if (p1 == p2)
        cout << "p1 == p2 : print" << endl;
    else
        cout << "p1 != p2 : print" << endl;
    p1.print();
    p2.print();
}

int main() {
    A *pc = new C();
    A *pb = new B();
    A *pc1 = new C();
    A &rc = *pc;

    if (B *pb = dynamic_cast< B* >(pc))
        pb->print();
    else
        pc->print();

    try{
        B& rb = dynamic_cast<B&>(rc);
        rb.print();
        cout << "dynamic_cast<B&> ok" << endl;
    }catch (bad_cast bc) {
        bc.what();
        rc.print();
    }
    
    cout << "judge pc & pb" << endl;
    judge_pA_equal(*pc, *pb);

    cout << "judge pc & pc1" << endl;
    judge_pA_equal(*pc, *pc1);
    return 0;
}
