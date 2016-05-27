//
//  NotificationClient.cpp
//  cocos2d_libs
//
//  Created by Greg WU on 16/5/27.
//
//

#include "NotificationClient.h"

// !!!: NotificationClientObserver
NotificationClientObserver::NotificationClientObserver(Ref * target,SEL_Notification call)
{
    _target=target;
    _callBack=call;
}

NotificationClientObserver::~NotificationClientObserver()
{
    
}

void NotificationClientObserver::activtie(NotificationClientData * notificateData)
{
    (_target->*_callBack)(notificateData);
}



// !!!: NotificationClient

NotificationClient * NotificationClient::instance=nullptr;

NotificationClient * NotificationClient::getInstance()
{
    if(!instance)
        instance=new NotificationClient();
    return instance;
}


NotificationClient::~NotificationClient()
{

}


void NotificationClient::addOberserver(const std::string& key ,  NotificationClientObserver * oberserver)
{
    auto& Oberservers=OberserverMap[key];
    Oberservers.push_back(oberserver);
}

void NotificationClient::addOberserver(const std::string& key ,  Ref* target, SEL_Notification callback)
{
    auto oberserver=new NotificationClientObserver(target, callback);
    addOberserver(key, oberserver);
}

void NotificationClient::removeOberserver(const std::string key , Ref * target)
{
    
    if( OberserverMap.find(key)==OberserverMap.end())
        return;
    
    auto& Oberservers=OberserverMap.at(key);
    for( auto itor=Oberservers.begin(); itor!=Oberservers.end() ; )
    {
            if(  (*itor)->_target==target)
            {
                delete (*itor);
                itor=Oberservers.erase(itor);
            }
            else
            {
                itor++;
            }
    }
}

void NotificationClient::postNoticate(const std::string& key,  NotificationClientData * notificateData)
{
    if( OberserverMap.find(key)==OberserverMap.end())
        return;
    
    for(auto& observer : OberserverMap.at(key))
        observer->activtie(notificateData);
}

