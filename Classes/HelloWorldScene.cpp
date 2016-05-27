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
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    editBox=cocos2d::ui::EditBox::create(Size(200,50), "HelloWorld.png");
    editBox->setPosition(visibleSize/2);
    addChild(editBox);
    

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
    
}

void HelloWorld::menuCloseCallback(cocos2d::Ref * sender)
{
    auto text=editBox->getText();
    
    rapidjson::Document jsonObject;
    //jsonObject.SetObject();
    auto& alloc=jsonObject.GetAllocator();
    //jsonObject.AddMember("chatMessage","Hello World", alloc);
    WebSocketClient::getInstance()->sendMessage("chat","Hello World");
}





