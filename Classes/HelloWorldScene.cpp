#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "modle/WebSocketClient.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
 //  you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                50));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    editBox=cocos2d::ui::EditBox::create(Size(200,50), "HelloWorld.png");
    editBox->setPosition(Vec2(  visibleSize.width/2,50 ));
    addChild(editBox);
    
    chatColor[0]=Color4B::RED;
    chatColor[1]=Color4B::WHITE;
    chatColor[2]=Color4B::GREEN;
    chatColor[3]=Color4B::ORANGE;
    chatColor[4]=Color4B::BLUE;
    
    return true;
}

void HelloWorld::onEnter()
{
    Layer::onEnter();
    NotificationClient::getInstance()->addOberserver("chat", this, oberserver_select(HelloWorld::onNewChat));
    
}
void HelloWorld::onExit()
{
    NotificationClient::getInstance()->removeOberserver("chat", this);
    Layer::onExit();
}

void HelloWorld::onNewChat(NotificationClientData * chatData)
{
    LocalDataChat * chat=dynamic_cast<LocalDataChat *>(chatData);
    auto message=chat->lastTime + chat->world;
    showNewChat(message);
}

void HelloWorld::menuCloseCallback(cocos2d::Ref * sender)
{
    auto text=editBox->getText();
    
    if(strcmp(text, "")==0)
        return;
    
    
    rapidjson::Document jsonObject;
    jsonObject.SetObject();
    auto& alloc=jsonObject.GetAllocator();
    
    rapidjson::Value sendMessage;
    sendMessage.SetString(text, strlen(text));
    jsonObject.AddMember("world", sendMessage, alloc);
    WebSocketClient::getInstance()->sendMessage("chat",jsonObject);
    editBox->setText("");
}

void HelloWorld::showNewChat(const  std::string& message)
{
    Label * chatLabel=Label::createWithSystemFont(message.c_str(), "fonts/Marker Felt.ttf", 15);
    
    float fontSize=cocos2d::random(35,40);
    Color4B fontColor=chatColor[cocos2d::random(0, 4)];
    float time=cocos2d::random(5, 10);
    float y=cocos2d::random(100.0f, Director::getInstance()->getVisibleSize().height-100);
    
    chatLabel->setSystemFontSize(fontSize);
    chatLabel->setTextColor(fontColor);
    chatLabel->setPositionX(Director::getInstance()->getVisibleSize().width+50);
    chatLabel->setPositionY(y);
    
    addChild(chatLabel);
    
    
    auto action1=MoveBy::create(time, Vec2(-Director::getInstance()->getVisibleSize().width+100,0)  );
    auto action2=RemoveSelf::create();
    auto seq=Sequence::create(action1,action2, nullptr);
    chatLabel->runAction(seq);
    
}




