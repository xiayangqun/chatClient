//
//  LocalData.hpp
//  chatDemo
//
//  Created by Greg WU on 16/5/27.
//
//

#ifndef LocalData_hpp
#define LocalData_hpp

#include <stdio.h>
#include "LocalDataChat.h"


class LocalDataClient
{
public:
    static LocalDataClient * getInstance();
    virtual ~LocalDataClient();
    
protected:
    LocalDataClient();
    static LocalDataClient * instance;
    
public:
    LocalDataChat * dataChat;
    

};

#endif /* LocalData_hpp */
