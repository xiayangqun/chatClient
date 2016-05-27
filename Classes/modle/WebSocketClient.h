//
//  WebSocketClient.hpp
//  chatDemo
//
//  Created by Greg WU on 16/5/27.
//
//

#ifndef WebSocketClient_hpp
#define WebSocketClient_hpp

#include <stdio.h>
#include "network/WebSocket.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"



using namespace cocos2d::network;

class WebSocketClient:public cocos2d::network::WebSocket::Delegate
{

public:
    static WebSocketClient * getInstance();
    virtual ~WebSocketClient();
    void sendMessage(const std::string& commend,const std::string& jsonString);
    void sendMessage(const std::string& commend, rapidjson::Document & jsonObject);
    
public:
  
    
public:
    void close();
    void registerHandler();
    void connect(const std::string& url);
    WebSocket::State getReadyState();
    
    
  
    
protected:
    static WebSocketClient * instance;
    std::map<std::string , std::function<void(const rapidjson::Document& )>> messageHandle ;
    WebSocketClient();
    WebSocket * webSocket;
    
    
public:
    //!!!: implement webSocketDelegate
    virtual void onOpen(WebSocket* ws) override;
    virtual void onMessage(WebSocket* ws, const WebSocket::Data& data) override;
    virtual void onClose(WebSocket* ws) override;
    virtual void onError(WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) override;
};





#endif /* WebSocketClient_hpp */
