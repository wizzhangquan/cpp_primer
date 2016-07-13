#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
 * test swap in container
 */

int main(void) {
    vector<string> svec1, svec2;

    svec1.push_back("zq");
    svec2.push_back("nobody");

    const auto &s1_iter = svec1.begin();
    const auto &s2_iter = svec2.begin();

    cout << "s1_iter : " << *s1_iter << " || "
         << " s2_iter : "<< *s2_iter << endl;
    
    svec1.swap(svec2);
    
    cout << "s1_iter : " << *s1_iter << " || "
         << " s2_iter : "<< *s2_iter << endl;

    cout << svec1[0] << "  ";
    cout << svec2[0] << endl;
    
    return 0;
}
