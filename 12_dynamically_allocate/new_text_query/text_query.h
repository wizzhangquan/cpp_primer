#ifndef _TEXT_QUERY_H__
#define _TEXT_QUERY_H__

#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>

class QueryResult;

class TextQuery {
public:
    typedef std::vector<std::string>::size_type line_no;
    typedef std::map<std::string,
             std::set<line_no>* > word_map_type;

    TextQuery(std::ifstream &);
    QueryResult query(const std::string &sought) const;
private:
    void insert_word_a_line(const std::string &line, 
                            line_no n);

    std::vector<std::string> *file;
    word_map_type *word_map;
};

class QueryResult {
public:
    friend std::ostream &print(std::ostream &, const QueryResult &);
    QueryResult(const std::string &sought, std::vector<std::string> *f,
                std::set<TextQuery::line_no> *l) :
                sought_word(sought), file(f), lines(l) { }
private:
    std::string sought_word;
    std::vector<std::string> *file;
    std::set<TextQuery::line_no> *lines;
};

std::ostream &print(std::ostream &, const QueryResult &);

#endif
