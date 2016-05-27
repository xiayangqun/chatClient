//
//  LocalDataProtocol.hpp
//  chatDemo
//
//  Created by Greg WU on 16/5/27.
//
//

#ifndef LocalDataProtocol_hpp
#define LocalDataProtocol_hpp

#include <stdio.h>
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

class LocalDataProtocol
{
    
public:
    virtual void onMessage(const rapidjson::Document& jsonObject)=0;
    
};

#endif /* LocalDataProtocol_hpp */
