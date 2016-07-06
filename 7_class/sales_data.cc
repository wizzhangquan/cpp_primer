#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::ostream;

class Sales_data{

friend istream &read(istream &is, Sales_data &item);
friend ostream &print(ostream &os, const Sales_data &item); 
friend Sales_data add(const Sales_data &lhs, const Sales_data &rhs); 

public:
    Sales_data(const string &s, unsigned n, double p):
               bookNo(s), units_sold(n), revenue(p*n) 
               { cout << "init" <<endl;}

    Sales_data() : Sales_data("", 0, 0) {}

    Sales_data(istream &is) : Sales_data() 
            { read(is, *this);}

    Sales_data(const string &s): Sales_data(s, 0, 0) {}

    string isbn() const {return bookNo;}
    Sales_data& combine(const Sales_data&);
private:
    double avg_price() const;

    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0;
};

istream &read(istream &is, Sales_data &item);

/*
Sales_data::Sales_data(istream &is) {
    read(is, *this);
}
*/

double Sales_data::avg_price() const {
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;
}

Sales_data& Sales_data::combine(const Sales_data& rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

istream &read(istream &is, Sales_data &item) {
    double price = 0;
    cout << "Please enter no, units, price" <<endl;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

ostream &print(ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    os << endl;
    return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

int main(void) {
    Sales_data sa("APUE");
    print(cout, sa);   
    sa.combine(string("lala"));
    print(cout, sa);
    sa.combine(cin);
    print(cout, sa);
    return 0;
}

