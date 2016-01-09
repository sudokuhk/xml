/*************************************************************************
    > File Name: map.cpp
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2016-01-09 14:05:49
 ************************************************************************/

#include <iostream>

#include <map>

int main()
{
    std::map<std::string, int> m;
    m["a"] = 1;
    m["b"] = 2;
    m["c"] = 3;

    for (std::map<std::string, int>::const_iterator it = m.begin(); it != m.end(); ++it)
        std::cout << it->first << " -- " << it->second << std::endl;
}
