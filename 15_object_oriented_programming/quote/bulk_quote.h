#ifndef _BULK_QUOTE_H__
#define _BULK_QUOTE_H__

#include <string>
#include <iostream>
#include "quote.h"

using std::string;
using std::size_t;
using std::ostream;

class Bulk_quote : public Quote {
public:
    friend ostream& operator<<(ostream &, const Bulk_quote&);

    Bulk_quote() = default; //c++11
    //Bulk_quote() { } //c++98
    Bulk_quote(const string &book, double sales_price,
        size_t qty, double disc) :
        Quote(book, sales_price), min_qty(qty), discount(disc) { }

    double net_price(size_t) const override; //c++11
    //virtual double net_price(size_t) const; //c++98

    const string print(void) const { return "print Bulk_quote"; }

    void virtual_print(void) const override 
    //c++11这里的override只是显著标志其改写基类的虚函数而已，不加也是可以的 
        { cout << "virtual_print: Bulk_quote" << endl;}
    
private:
    size_t min_qty = 0;
    double discount = 0.0;
};

ostream &
operator<<(ostream &os, const Bulk_quote &bq) {
    os << "Bulk_quote book:" << bq.isbn()
       << " price:" << bq.price;
    return os;
}

double
Bulk_quote::net_price(size_t cnt) const {
    if (cnt >= min_qty)
        return cnt * (1-discount) * price;
    else
        return cnt * price;
}

#endif
