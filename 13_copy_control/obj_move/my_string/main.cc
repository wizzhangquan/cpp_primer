#include <iostream>
#include <vector>
#include "String.h"

using namespace std;

void foo(String x)
{
}
 
void bar(const String& x)
{
}
 
String baz()
{
  String ret("world");
  return ret;
}
 
/*
int main()
{
  String s0;
  String s1("hello");
  String s2(s0);
  String s3 = s1;
  s2 = s1;
 
  foo(s1);
  bar(s1);
  foo("temporary foo");
  bar("temporary bar");
  String s4 = baz();
 
  std::vector<String> svec;
  svec.push_back(s0);
  svec.push_back(s1);
  svec.push_back(baz());
  svec.push_back("good job");
}
*/

int main() {
    //test vector.push_back
    vector<String> svec;
    
    String s0= "hello0";
    String s1= "hello1";
    String s2= "hello2";
    String s3= "hello3";
    String s4= "hello4";
    String s5= "hello5";

    cout << s0.c_str() << endl;

    svec.push_back(s0);
    svec.push_back(s1);
    svec.push_back(s2);
    svec.push_back(s3);
    svec.push_back(s4);
    svec.push_back(s5);
    return 0;
}

