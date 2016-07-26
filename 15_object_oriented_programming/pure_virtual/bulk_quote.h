#ifndef _BULK_QUOTE_H__
#define _BULK_QUOTE_H__

#include <string>
#include "disc_quote.h"

using std::string;
using std::size_t;

class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const string &book, double price,
               size_t qty, double disc):
                Disc_quote(book, price, qty, disc) { }
    
    double net_price(size_t) const override;
};

double
Bulk_quote::net_price(size_t cnt) const {
    if (cnt >= quantity)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

#endif
