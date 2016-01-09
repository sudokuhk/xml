/*************************************************************************
    > File Name: xmldef.h
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2016-01-07 21:22:17
 ************************************************************************/

#ifndef __XML_DEF_H__
#define __XML_DEF_H__

#include <string>
#include <list>
#include <map>

class TiXmlDocument;
class TiXmlElement;
    
namespace xml
{
    typedef std::list<TiXmlElement *> XmlElementList;
        
    enum {
        eXmlPathLimit       = 1024,
        eXmlFileNameLimit   = 1024,
    }; 
        
    class CNodeList : public XmlElementList
    {
    public:
        CNodeList(void);
        ~CNodeList(void);
        
        CNodeList(const CNodeList & lhs);
        CNodeList & operator=(const CNodeList & lhs);
    public:
        char m_path[eXmlPathLimit];
    };
    
    typedef std::map<int, CNodeList> NodeListMap;
    class CLevelMap : public NodeListMap
    {
    public:
        CLevelMap(void);
        ~CLevelMap(void);
        
        CLevelMap(const CLevelMap & lhs);
        CLevelMap & operator=(const CLevelMap & lhs);
    public:
        char m_path[eXmlPathLimit];
    };
    
    typedef std::string CNodeName;
        
    class CNodeNameCaseLess
    {
    public:
        bool operator()(const CNodeName & lhs, const CNodeName & rhs);
    };
    
    typedef std::map<CNodeName, CLevelMap, CNodeNameCaseLess> NameMap;
        
    class CNameMap : public NameMap
    {
    public:
        CNameMap(void);
        ~CNameMap(void);
        
        CNameMap(const CNameMap & lhs);
        CNameMap & operator=(const CNameMap & lhs);
    public:
        char m_path[eXmlPathLimit];
    };
    
    typedef enum _ENodeValueCfg {
        eValueOptional  = 1 << 0,
        eValueRequire   = 1 << 1,
        
    } ENodeValueCfg;
}

#endif