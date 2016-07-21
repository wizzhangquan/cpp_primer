#ifndef _SALES_DATA_H__
#define _SALES_DATA_H__

#include <iostream>
#include <string>

using std::string;
using std::istream;
using std::ostream;

class SalesData {
friend istream & operator>>(istream&, SalesData &);
friend ostream & operator<<(ostream&, const SalesData &);
public:
    SalesData(const string &s, unsigned int n, double p) :
        bookNo(s), units_sold(n), revenue(n*p) { }
    SalesData() : SalesData("", 0, 0.0f) { }
    SalesData(const string &s) : SalesData(s, 0, 0.0f) { }
    SalesData(istream &);

private:
    double avg_price() const
        { return units_sold > 0 ? revenue/units_sold : 0; }
    string bookNo;
    unsigned int units_sold;
    double revenue ;
};

#endif
