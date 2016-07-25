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
