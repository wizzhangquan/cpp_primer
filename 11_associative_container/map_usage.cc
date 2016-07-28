#include <iostream>
#include <map>

using namespace std;

/*
 * map的基本使用方法
 */

int main() {
    map<string, size_t> wordcount;
    
    //如果使用[]查询未存在的key,会添加进一个默认值
    //if use at, if key isnot in map ,will throw a out_of_range
    cout << "find foobar in wordcount :" 
         << wordcount["foobar"] << endl;

    /*
    //循环遍历c++11
    for (auto &map_it : wordcount)
        cout << map_it.first << ":" << map_it.second << endl;
    */

    //循环遍历c++03
    for (map<string, size_t>::iterator map_it = wordcount.begin();
            map_it != wordcount.end(); ++map_it)
        cout << map_it->first << ":" << map_it->second << endl;
    
    //插入
    string foobar = "foobar";
    string word = "wizzhangquan";

    pair < map<string, size_t>::iterator, bool> ret;
    //auto ret = wordcount.insert({foobar, 1});//c++11
 
    ret = wordcount.insert({foobar, 1}); //c++03
    if (ret.second == false) {
        cout << foobar << "has in the wordcount" << endl;
        ++ret.first->second; //递增
    } else 
        cout << foobar << "insert success" << endl;

    ret = wordcount.insert({word, 1});
    if (ret.second == false) {
        cout << word << " has in the wordcount" << endl;
        ++ret.first->second; //递增
    } else {
        cout << word << " insert success" << endl;
    } 
    cout << "==========insert end===========" << endl;
    
    //再次遍历 
    for (map<string, size_t>::iterator map_it = wordcount.begin();
            map_it != wordcount.end(); ++map_it)
        cout << map_it->first << ":" << map_it->second << endl;

    return 0;
}
