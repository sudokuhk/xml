/*************************************************************************
    > File Name: test.cpp
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2016-01-08 14:33:39
 ************************************************************************/
//g++ test.cpp xmlread.cpp xmldef.cpp -o test -I. -I../tinyxml -L. -ltinyxml -fpermissive -g

#include <xmlread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

class A
{
public:
    READ_XML_BEGN
    READ_VALUE(a, "a", 1, xml::eValueRequire);
    READ_VALUE(b, "b", "abc", xml::eValueRequire);
    READ_XML_END
    
    int a;
    char b[100];
};

int main()
{
    xml::CBaseRead r;
    A a;

    r.read_xml(a, "a.xml");
    printf("REAd:%d\n", a.a);
   return 0 ;
}
