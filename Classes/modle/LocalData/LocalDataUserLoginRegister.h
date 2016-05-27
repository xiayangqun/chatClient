//
//  LocalDataUserLogin.hpp
//  chatDemo
//
//  Created by Greg WU on 16/5/27.
//
//

#ifndef LocalDataUserLogin_hpp
#define LocalDataUserLogin_hpp

#include <stdio.h>
#include "../NotificationClient.h"


class LocalDataUserLoginRegister:public NotificationClientData
{
    
public:
    void onMessageRegister(const rapidjson::Document& jsonObject);
    void onMessageLogin(const rapidjson::Document& jsonObject);
    
    
    std::string userName;
    
};



#endif /* LocalDataUserLogin_hpp */
