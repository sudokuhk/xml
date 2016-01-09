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
    class C
    {
        READ_XML_BEGN
        READ_VALUE(a, "a", 1, xml::eValueRequire);
        READ_VALUE(d, "d", 12.3, xml::eValueRequire);
        READ_XML_END
        
        int a;
        double d;
    };
public:
    READ_XML_BEGN
    READ_VALUE(a, "a", 1, xml::eValueRequire);
    READ_VALUE(b, "b", "abc", xml::eValueRequire);
    READ_OBJ(c, "c", xml::eValueRequire);
    READ_XML_END
    
    int a;
    char b[100];
    C c;
};

int main()
{
    xml::CBaseRead r;
    A a;

    r.read_xml(a, "a.xml");
    printf("READ:%d\n", a.a);
    printf("READ:%s\n", a.b);
    printf("READ:%d\n", a.c.a);
   return 0 ;
}
