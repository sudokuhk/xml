/*************************************************************************
    > File Name: main.cpp
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2016-01-07 14:34:31
 ************************************************************************/

#include <stdio.h>
#include <string>

#include "tinyxml.h"

int main(int argc, char * argv[])
{
    if (argc != 2) {
        printf("Input xml file!\n");
        return 0;        
    }    

    std::string filename(argv[1]);

    TiXmlDocument * document = new TiXmlDocument();
    if (!document->LoadFile(filename.c_str())) {
        printf("Load file failed:%s, error:%s\n", filename.c_str(), document->ErrorDesc());
        delete document;
        return 0;
    }
    document->Print();

    TiXmlElement * rootElement = document->RootElement(); 
    if (rootElement == NULL) {
        printf("root element empty!\n");
        return 0;
    }

    for (TiXmlElement * pChildNode = rootElement->FirstChildElement();
        pChildNode != NULL; pChildNode = pChildNode->NextSiblingElement()) {
        
        const char * cszNodeName = pChildNode->Value();
        printf("%s\n", cszNodeName);
    }
}
