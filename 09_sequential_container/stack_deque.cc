#include <iostream>
#include <deque>
#include <stack>

/*
 * stack test
 */

using namespace std;

int main() {
    stack<int, deque<int>> stk;
    int num;
    cout << "how many number do u want push:";
    cin >> num; 
    for (int i=0; i<num; ++i)
        stk.push(i);

    cout << "the stack's top:" 
         << stk.top() << endl;

    cout << "let us pop the stk: " << endl;
    while (!stk.empty()) {
        cout << "pop:"
             << stk.top() << endl;
        stk.pop(); //pop's return is void
    }

    cout << "now stack is empty, now we try top: ";
    //cout << stk.top() << endl;  //it is will segment fault 
    return 0;
}
