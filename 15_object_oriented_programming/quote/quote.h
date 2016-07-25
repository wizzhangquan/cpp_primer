#ifndef _QUOTE_H__
#define _QUOTE_H__

#include <string>

using std::string;
using std::size_t;

class Quote {
public:
    Quote() { }; //c++98
    //Quote() = default;  //c++11
    Quote(const string &book, double sales_price):
        bookNo(book), price(sales_price) { }
    
    string isbn() const { return bookNo; }

    virtual double net_price(size_t n) const
        { return n*price; }
    virtual ~Quote() { }; //c++98
    //virtual ~Quote() = default; //c++11
private:
    string bookNo;
protected:
    double price ;
};

#endif
