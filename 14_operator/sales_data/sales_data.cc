#include <iostream>
#include <string>
#include "sales_data.h"

using namespace std;

istream &
operator>>(istream &is, SalesData &item) {
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    if (is) //这里检查输入是否成功
        item.revenue = item.units_sold * price;
    else
        item = SalesData();
    return is;
}

ostream &
operator<<(ostream &os, const SalesData &item) {
    os << item.bookNo << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

SalesData::SalesData(istream &is) : SalesData() {
    is >> *this;
}

int main() {
    return 0;
}
