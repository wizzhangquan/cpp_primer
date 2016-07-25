#include <iostream>
#include <string>
#include "quote.h"
#include "bulk_quote.h"

using namespace std;

int main() {
    Quote q;
    Bulk_quote bq;
    const Quote &cit_bq = bq;
    cout << "q: " << q << endl;
    cout << "bq: " << bq << endl;
    cout << "&cit_bq: " << cit_bq << endl; //看来友元函数并没有多态哦，毕竟不是继承/虚函数
    cout << endl;
 
    cout << "q.print: " << q.print() << endl;
    cout << "bq.print: " << bq.print() << endl;
    cout << "&cit_bq.print: " << cit_bq.print() << endl;
    cout << endl;

    cout << "virtual_print:" << endl;
    q.virtual_print();
    bq.virtual_print();
    cit_bq.virtual_print();
    return 0;
}
