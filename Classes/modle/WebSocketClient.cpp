//
//  WebSocketClient.cpp
//  chatDemo
//
//  Created by Greg WU on 16/5/27.
//
//

#include "WebSocketClient.h"
#include "LocalData/LocalDataClient.h"

WebSocketClient * WebSocketClient::instance=nullptr;

WebSocketClient * WebSocketClient::getInstance()
{
    if(!instance)
        instance=new WebSocketClient();
    
    return instance;
}


WebSocketClient::WebSocketClient()
{
    webSocket=new WebSocket();
}

WebSocketClient::~WebSocketClient()
{
    webSocket->close();
    delete webSocket;
}

void WebSocketClient::sendMessage(const std::string& commend,const std::string& jsonString)
{
    rapidjson::Document jsonObject;
    jsonObject.Parse<0>(jsonString.c_str());
    sendMessage(commend, jsonObject);
}

void WebSocketClient::sendMessage(const std::string& commend,rapidjson::Document & jsonObject)
{
  // todo
//    jsonObject["commend"]=commend;

    auto& alloct=jsonObject.GetAllocator();
    
    rapidjson::Value commendValue;
    commendValue.SetString(commend.c_str(), commend.length());
    jsonObject.AddMember("commend", commendValue, alloct);
   
    rapidjson::StringBuffer  buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    jsonObject.Accept(writer);
    
    std::string jsonString=buffer.GetString();
    webSocket->send(jsonString);
}


void WebSocketClient::close()
{
    webSocket->close();
}

void WebSocketClient::connect(const std::string& url)
{
    if(getReadyState()==WebSocket::State::CONNECTING)
        webSocket->init(*this, url,nullptr);
    else
        CCLOG("websocket cant be connect !!! %d", (int)getReadyState());
}

WebSocket::State WebSocketClient::getReadyState()
{
    return webSocket->getReadyState();
}

void WebSocketClient::onOpen(WebSocket* ws)
{
    CCLOG("webSocket connect sucessed");
}

void WebSocketClient::onMessage(WebSocket* ws, const WebSocket::Data& data)
{
    rapidjson::Document jsonObject;
    jsonObject.Parse<0>(data.bytes);
    
    if(jsonObject.HasParseError())
    {
        CCLOG("Oops, serverData is not a json format!!!! :%s", data.bytes);
        return;
    }
    
    auto& commend=jsonObject["commend"];
    auto conmmendStr=commend.GetString();
    
   if(messageHandle.find(conmmendStr)==messageHandle.end())
       CCLOG("Oops, there is a commend: %s we dont catched!!!",conmmendStr);
    else
        messageHandle[conmmendStr](jsonObject);
}

void WebSocketClient::onClose(WebSocket* ws)
{
    CCLOG("webSocket connection break!!");
}

void WebSocketClient::onError(WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)
{
    CCLOG("webSocket error , error code is :%d", (int)error);
}


 void WebSocketClient::registerHandler()
{
    LocalDataClient * dataClient=LocalDataClient::getInstance();
    
    messageHandle.insert(std::make_pair("chat",      CC_CALLBACK_1(LocalDataChat::onMessage, dataClient->dataChat)));
    messageHandle.insert(std::make_pair("register", CC_CALLBACK_1(LocalDataUserLoginRegister::onMessageRegister, dataClient->dataUserloginRegister)));
    messageHandle.insert(std::make_pair("login",     CC_CALLBACK_1(LocalDataUserLoginRegister::onMessageLogin, dataClient->dataUserloginRegister)));
    
    //*****
    
    
    
    
    
    
}

