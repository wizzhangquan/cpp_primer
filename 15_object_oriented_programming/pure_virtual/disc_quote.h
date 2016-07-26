#ifndef _DISC_QUOTE_H__
#define _DISC_QUOTE_H__

#include <string>
#include "quote.h"

using std::string;
using std::size_t;

class Disc_quote : public Quote {
public:
    Disc_quote() = default; //c++11
    //Disc_quote() { quantity = 0; discount = 0.0; } //c++03

    Disc_quote(const string &book, double price,
               size_t qty, double disc):
                Quote(book, price), 
                quantity(qty), discount(disc) { }

    double net_price(size_t) const = 0; //pure virtual

protected:
    size_t quantity = 0;
    double discount = 0.0;
};

#endif
