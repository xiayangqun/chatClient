//
//  LocalDataChat.hpp
//  chatDemo
//
//  Created by Greg WU on 16/5/27.
//
//

#ifndef LocalDataChat_hpp
#define LocalDataChat_hpp

#include <stdio.h>
#include "../NotificationClient.h"
#include "../Tools.h"


class LocalDataChat:public NotificationClientData
{
public:
    
    void onMessage(const rapidjson::Document& jsonObject);
    
    //接受到聊天记录的时间
    std::string lastTime;
    //接收到聊天记录的内容
    std::string world;
    

    
    
};

#endif /* LocalDataChat_hpp */
