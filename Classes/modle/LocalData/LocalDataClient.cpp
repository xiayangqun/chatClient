//
//  LocalData.cpp
//  chatDemo
//
//  Created by Greg WU on 16/5/27.
//
//

#include "LocalDataClient.h"


LocalDataClient * LocalDataClient::instance=nullptr;

LocalDataClient * LocalDataClient::getInstance()
{
    if(!instance)
        instance=new LocalDataClient();
    return  instance;
}

LocalDataClient::~LocalDataClient()
{
    delete dataChat;
    delete dataUserloginRegister;
}


LocalDataClient::LocalDataClient()
{
    dataChat=new LocalDataChat();
    dataUserloginRegister=new LocalDataUserLoginRegister();
}
