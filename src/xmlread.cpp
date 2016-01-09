/*************************************************************************
    > File Name: xmlread.cpp
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2016-01-07 21:20:16
 ************************************************************************/

#include <xmlread.h>

#include <tinyxml.h>
#include <log.h>
#include <errno.h>

namespace xml
{

CBaseRead::CBaseRead(void) 
    : m_pDocument(NULL)
    , m_pRootNode(NULL)
{
    bzero(m_szFile, eXmlFileNameLimit);
    log_error(LOG_DEBUG, "%s:%d", __FUNCTION__, __LINE__);
}

CBaseRead::~CBaseRead(void) 
{
    bzero(m_szFile, eXmlFileNameLimit);
    uninit();
}

int CBaseRead::uninit(void)
{
    log_error(LOG_DEBUG, "%s:%d", __FUNCTION__, __LINE__);
    
    m_pRootNode = NULL;
    if (m_pDocument != NULL) {
        delete m_pDocument;
        m_pDocument = NULL;
    }
    return 0;
}

int CBaseRead::init(void)
{
    log_error(LOG_DEBUG, "%s:%d", __FUNCTION__, __LINE__);
    
    bool load = false;
    int ret = 0;
            
    uninit();
    
    m_pDocument = new TiXmlDocument();
    load = m_pDocument->LoadFile(m_szFile);
    if (!load) {
        log_error(LOG_DEBUG, "%s:%d", __FUNCTION__, __LINE__);
        
        int err = m_pDocument->ErrorId(); //-->errno
        if (err == EACCES) {
            log_error(LOG_ERR, "%s:%d", m_pDocument->ErrorDesc(), m_szFile);
        } else {
            log_error(LOG_ERR, "%s:%d[%d:%d]", m_pDocument->ErrorDesc(), m_szFile,
                m_pDocument->ErrorRow(), m_pDocument->ErrorCol());
        }
        uninit();
        ret = -1;
    } else {
        m_pRootNode = m_pDocument->RootElement();
        if (m_pRootNode == NULL) {
            uninit();
            ret = -1;
        }
    }
    log_error(LOG_DEBUG, "%s:%d", __FUNCTION__, __LINE__);
    return ret;
}

int get_content(std::string& buf, const char **sz_path, CNameMap & nameMap, 
            const char * nodeName)
{
    log_error(LOG_DEBUG, "%s:%d, key:%s, mapsize:%d", __FUNCTION__, __LINE__, nodeName, nameMap.size());
    int ret = 0;
    *sz_path = nameMap.m_path;
    
    #if LOG_LEVEL == LOG_DEBUG
    for (CNameMap::const_iterator it = nameMap.begin(); it != nameMap.end(); ++it)
        log_error(LOG_DEBUG, "VISIT:Key:%s", it->first.c_str());
    #endif
        
    CNameMap::const_iterator itName = nameMap.find(nodeName);
    if (itName == nameMap.end()) {
        log_error(LOG_DEBUG, "%s:%d, key:%s--empty", __FUNCTION__, __LINE__, nodeName);
        ret = -1;
    } else {
        
        for (CLevelMap::const_iterator itLevel = itName->second.begin();
            itLevel != itName->second.end(); ++ itLevel) {
            log_error(LOG_DEBUG, "%s:%d, key:%s--size:%d", __FUNCTION__, __LINE__, nodeName, itLevel->second.size());
            if (itLevel->second.empty()) {
                continue;
            }
            CNodeList::const_iterator itNode = itLevel->second.begin();
            
            const char * cur_val = (* itNode)->GetText();
            if (cur_val == NULL) {
                cur_val = "";
            }
            buf = cur_val;
            *sz_path = (itLevel->second).m_path;
        }
    }
    log_error(LOG_DEBUG, "GET:%s", buf.c_str());
    return ret;
}

void fill_nameMap(const CLevelMap & levelMap, CNameMap & nameMap)
{
    for (CLevelMap::const_iterator itLevel = levelMap.begin();
        itLevel != levelMap.end(); ++ itLevel) {
        
        const CNodeList & nodeList = itLevel->second;
        for (CNodeList::const_iterator itNode = nodeList.begin();
            itNode != nodeList.end(); ++ itNode) {
                
            TiXmlElement * pChildNode=(* itNode)->FirstChildElement();
            while (pChildNode != NULL) {
                CNodeName node_name     = pChildNode->Value();
				CLevelMap& rmapDomLevel = nameMap[node_name];
				CNodeList& rlstNode     = rmapDomLevel[itLevel->first];
				sprintf(rlstNode.m_path, "%s/%s", itLevel->second.m_path, node_name.c_str());
				log_error(LOG_DEBUG, "VISIT:%s", rlstNode.m_path);
				if(rlstNode.empty()) {
					strcpy(rmapDomLevel.m_path, rlstNode.m_path);
				}
				rlstNode.push_back(pChildNode);
                pChildNode = pChildNode->NextSiblingElement();
            }    
        }
    }
    
    #if LOG_LEVEL == LOG_DEBUG
    log_error(LOG_DEBUG, "NameMap size:%d", nameMap.size());
    for (CNameMap::iterator it = nameMap.begin(); it != nameMap.end(); ++it)
        log_error(LOG_DEBUG, "VISIT:Key:%s, size:%d", it->first.c_str(), it->second.size());
    #endif
}

int convert_value(char & lhs, const std::string & rhs)
{
    lhs = atoi(rhs.c_str());
}

int convert_value(short & lhs, const std::string & rhs)
{
    lhs = atoi(rhs.c_str());
}

int convert_value(int & lhs, const std::string & rhs)
{
    lhs = atoi(rhs.c_str());
}

int convert_value(long & lhs, const std::string & rhs)
{
    lhs = atol(rhs.c_str());
}

int convert_value(long long & lhs, const std::string & rhs)
{
    lhs = atoll(rhs.c_str());
}

int convert_value(float & lhs, const std::string & rhs)
{
    lhs = atof(rhs.c_str());
}

int convert_value(double & lhs, const std::string & rhs)
{
    lhs = atof(rhs.c_str());
}

int convert_value(char * lhs, const std::string & rhs)
{
    strcpy(lhs, rhs.c_str());
}


}