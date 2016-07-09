#include <iostream>
#include <vector>

using namespace std;

/*
 * test the insert and erase to change the iterator.
 */

void copy_odd_and_del_even(vector<int> &vi) {
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

int main(void) {
    vector<int> vi = {1,2,3,4,5,6,7,8,9};
    copy_odd_and_del_even(vi);
    for (auto i : vi)
        cout << i << " ";
    cout << endl;
    return 0;
}
