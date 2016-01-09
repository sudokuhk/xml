/*************************************************************************
    > File Name: xmlread.h
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2016-01-07 21:20:09
 ************************************************************************/

#ifndef __XML_READ_H__
#define __XML_READ_H__

#include <xmldef.h>
#include <typeinfo>
#include <tinyxml.h>

#include <log.h>

namespace xml
{
    template <typename T1, typename T2>
    int read_xml(T1 & value, CNameMap & nameMap, const char * node_name,
        T2 def_value, ENodeValueCfg option);
        
    void fill_nameMap(const CLevelMap & levelMap, CNameMap & nameMap);      
    
    static char * strcpy(char * dst, const char * src)
    {
        char * pdst = dst;
        while ((*pdst ++ = *src ++));
        return dst;
    } 
        
    #define READ_XML_BEGN                                                           \
    public:                                                                         \
        int read_xml(xml::CLevelMap & levelMap, const xml::ENodeValueCfg option) {  \
            int ret     = 0;                                                        \
            bool exists = false;                                                    \
            xml::CNameMap nameMap;                                                  \
            xml::fill_nameMap(levelMap, nameMap);                                   \
            
    #define READ_VALUE(value, node_name, def_value, option)                         \
        {                                                                           \
            snprintf(nameMap.m_path, xml::eXmlPathLimit, "%s/%s",                   \
                levelMap.m_path, node_name);                                        \
            ret = xml::read_xml(value, nameMap, node_name, def_value, option);      \
            exists = (ret == 0);                                                    \
            ret = ret == 0 ? 0 : -1;                                                \
        }                                                                           \
                
    #define READ_XML_END                                                            \
            return ret;                                                             \
        }                                                                           \
        
        
    class CBaseRead
    {
    public:
        CBaseRead(void);
        ~CBaseRead(void);
        
        template<typename T>
        int read_xml(T & obj, const char * filename);
        
    private:
        CBaseRead(const CBaseRead & lhs);
        CBaseRead & operator=(const CBaseRead & lhs);
        
        int init(void);
        int uninit(void);
        
    private:
        TiXmlDocument * m_pDocument;
	    TiXmlElement * m_pRootNode;
	    
	    char m_szFile[eXmlFileNameLimit];
    };
    
    template<typename T>
    int CBaseRead::read_xml(T & obj, const char * filename)
    {
        int ret = 0;
        
        if (filename == NULL) {
            ret = -1;
        } else {
            strcpy(m_szFile, filename);
            
            ret = init();
            if (ret == 0) {
                CLevelMap levelMap;
                levelMap[0].push_back(m_pRootNode);
                strcpy(levelMap[0].m_path, m_pRootNode->Value());
                ret = obj.read_xml(levelMap, eValueRequire);
            }
        }
        return ret; 
    }
    
    int get_content(std::string& buf, const char **sz_path, CNameMap & nameMap, 
            const char * nodeName);
            
    int convert_value(char & lhs, const std::string & rhs);
    int convert_value(short & lhs, const std::string & rhs);
    int convert_value(int & lhs, const std::string & rhs);
    int convert_value(long & lhs, const std::string & rhs); 
    int convert_value(long long & lhs, const std::string & rhs);
    int convert_value(float & lhs, const std::string & rhs); 
    int convert_value(double & lhs, const std::string & rhs);
    int convert_value(char * lhs, const std::string & rhs);    
    
    template <typename T1, typename T2>
    int read_xml(T1 & value, CNameMap & nameMap, const char * node_name,
        T2 def_value, ENodeValueCfg option)
    {
        const char * path = NULL;
        std::string val;
        int ret = get_content(val, &path, nameMap, node_name);
        if (ret == 0) {
            ret = convert_value(value, val);
        } else if (ret == -1) {
            if (option == eValueOptional) {
                //value = def_value;
                ret = 0;
            }
        }
        return ret;
    }
}

#endif
