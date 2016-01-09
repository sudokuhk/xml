/*************************************************************************
    > File Name: xmldef.cpp
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2016-01-07 22:17:16
 ************************************************************************/

#include <xmldef.h>

#include <log.h>
#include <tinyxml.h>
#include <string.h>

namespace xml
{
    
static char * strcpy(char * dst, const char * src)
{
    char * pdst = dst;
    while ((*pdst ++ = *src ++));
    return dst;
}

CNodeList::CNodeList(void)
{
    bzero(m_path, eXmlPathLimit);
}

CNodeList::~CNodeList(void)
{
}

CNodeList::CNodeList(const CNodeList & lhs)
{
    strcpy(m_path, lhs.m_path);
}

CNodeList & CNodeList::operator=(const CNodeList & lhs)
{
    if (&lhs != this) {
        strcpy(m_path, lhs.m_path);
        XmlElementList::operator=(lhs);
    }
    return *this;
}

CLevelMap::CLevelMap(void)
{
    bzero(m_path, eXmlPathLimit);
}

CLevelMap::~CLevelMap(void)
{
}

CLevelMap::CLevelMap(const CLevelMap & lhs)
{
    strcpy(m_path, lhs.m_path);
}

CLevelMap & CLevelMap::operator=(const CLevelMap & lhs)
{
    if (&lhs != this) {
        strcpy(m_path, lhs.m_path);
        NodeListMap::operator=(lhs);
    }
    return *this;
}

bool CNodeNameCaseLess::operator()(const CNodeName & lhs, const CNodeName & rhs)
{
    //printf("LEFT:%s, RIGHT:%s, %d\n", lhs.c_str(), rhs.c_str(), strcasecmp(lhs.c_str(), rhs.c_str()));
    return strcasecmp(lhs.c_str(), rhs.c_str()) < 0;
}

CNameMap::CNameMap(void)
{
    bzero(m_path, eXmlPathLimit);
}

CNameMap::~CNameMap(void)
{
}

CNameMap::CNameMap(const CNameMap & lhs)
{
    strcpy(m_path, lhs.m_path);
}

CNameMap & CNameMap::operator=(const CNameMap & lhs)
{
    if (&lhs != this) {
        strcpy(m_path, lhs.m_path);
        NameMap::operator=(lhs);
    }
    return *this;
}

}
