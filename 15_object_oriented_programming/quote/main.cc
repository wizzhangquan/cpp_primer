#include <iostream>
#include <string>
#include "quote.h"
#include "bulk_quote.h"

using namespace std;

int main() {
    Quote q;
    Bulk_quote bq;
    const Quote &cit_bq = bq;
    cout << q << endl;
    cout << bq << endl;
    cout << cit_bq << endl; //看来友元函数并没有多态哦，毕竟不是继承/虚函数
    return 0;
}
