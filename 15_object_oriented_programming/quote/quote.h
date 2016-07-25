#ifndef _QUOTE_H__
#define _QUOTE_H__

#include <string>
#include <iostream>

using std::string;
using std::size_t;
using std::ostream;
using std::cout;
using std::endl;

class Quote {
public:
    friend ostream &operator<<(ostream &, const Quote &); 
    //显然friend没有动态绑定
   
    Quote() { }; //c++98
    //Quote() = default;  //c++11
    Quote(const string &book, double sales_price):
        bookNo(book), price(sales_price) { }
    
    string isbn() const { return bookNo; }

    virtual double net_price(size_t n) const
        { return n*price; }
    virtual ~Quote() { }; //c++98
    //virtual ~Quote() = default; //c++11

    const string print(void) const { return "print Quote"; }
    //没有加virtual也没有动态绑定即运行时绑定
    
    virtual void virtual_print(void) const 
        { cout << "virtual_print: Quote" << endl;}
    
private:
    string bookNo;
protected:
    double price = 0;
};

ostream &
operator<<(ostream &os, const Quote &q) {
    os << "Quote book:" << q.bookNo 
       << " price:" << q.price;
    return os;
}

#endif
