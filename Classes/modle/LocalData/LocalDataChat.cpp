//
//  LocalDataChat.cpp
//  chatDemo
//
//  Created by Greg WU on 16/5/27.
//
//

#include "LocalDataChat.h"

void LocalDataChat::onMessage(const rapidjson::Document& jsonObject)
{
    const auto& clientData=jsonObject["clientData"];
    const auto& serverData=jsonObject["serverData"];
    const auto& commend=jsonObject["commend"];
    
    time_t  timeSince1970=serverData["time"].GetInt64();
    lastTime=Tools::timeSince1970ToTimeString(timeSince1970);
    world=serverData["world"].GetString();
    
    //to 解析数据啦
    NotificationClient::getInstance()->postNoticate(commend.GetString(), this);
}



