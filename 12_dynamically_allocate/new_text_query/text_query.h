#ifndef _TEXT_QUERY_H__
#define _TEXT_QUERY_H__

#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>

//class QueryResult;

class TextQuery {
public:
    typedef std::vector<std::string>::size_type line_no;
    typedef std::map<std::string,
             std::set<line_no>* > word_map_type;

    TextQuery(std::ifstream &);
    
private:
    void insert_word_a_line(const std::string &line, 
                            line_no n);

    std::vector<std::string> *file;
    word_map_type *word_map;
};

/*usage test

void run_queries(ifstream &infile) {
    TextQuery tq(infile);
    while (true) {
        cout << "enter word to look for, or q! to quit: ";
        string query_word;
        if ((cin >> query_word) || s == "q!") break;
        
        print(cout, tq.query(s)) << endl;
       
    }
}
*/

#endif
