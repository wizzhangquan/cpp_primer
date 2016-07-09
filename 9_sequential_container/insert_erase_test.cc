#include <iostream>
#include <vector>
#include <list>

using namespace std;

/*
 * test the insert and erase to change the iterator.
 */

void double_odds_and_remove_evens(vector<int> &vi) {
    for (auto iter = vi.begin();
            iter != vi.end();   ) {
        if (*iter % 2 ) {
            iter = vi.insert(iter, *iter);
            iter += 2;
        } else {
            iter = vi.erase(iter);
        }
    }
}

void double_odds_and_remove_evens(list<int> &vi) {
    for (auto iter = vi.begin();
            iter != vi.end();   ) {
        if (*iter % 2 ) {
            iter = vi.insert(iter, *iter);
            advance(iter, 2);             // list cannot iter+=2 --change--> advance
        } else {
            iter = vi.erase(iter);
        }
    }
}

int main(void) {
    vector<int> vi = {1,2,3,4,5,6,7,8,9};
    double_odds_and_remove_evens(vi);
    for (auto i : vi)
        cout << i << " ";
    cout << endl;
    return 0;
}
