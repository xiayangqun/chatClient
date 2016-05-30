//
//  NotificationClient.hpp
//  cocos2d_libs
//
//  Created by Greg WU on 16/5/27.
//
//

#ifndef NotificationClient_hpp
#define NotificationClient_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;



class NotificationClientData
{
    
public:
    NotificationClientData(){};
    virtual ~NotificationClientData(){};
};

typedef void (Ref::*SEL_Notification)(NotificationClientData * );
#define oberserver_select(function) (SEL_Notification)(&function)


class NotificationClientObserver
{
public:
    
    NotificationClientObserver(Ref * target,SEL_Notification call);
    ~NotificationClientObserver();
    void activtie(NotificationClientData * notificateData );

    Ref * _target;
    SEL_Notification _callBack;
    
};

class NotificationClient
{
public:
    
    static  NotificationClient * getInstance();
    
protected:
    
    virtual ~NotificationClient();
    static NotificationClient * instance;
    std::map<std::string , std::vector<NotificationClientObserver *> > OberserverMap;
    
public:
    void addOberserver(const std::string& key ,  NotificationClientObserver * oberserver);
    void addOberserver(const std::string& key ,  Ref* target, SEL_Notification callback);
    void removeOberserver(const std::string key , Ref * target);
    void postNoticate(const std::string& key,  NotificationClientData *  jsonObject );
    
};
#endif /* NotificationClient_hpp */
