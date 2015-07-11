#include "HelloWorldScene.h"
#include "AppDelegate.h"
#include "ShelfScene.h"
USING_NS_CC;

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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//添加背景
	auto *background = Sprite::create("bg.png");
	background->setPosition(visibleSize.width * 0.5,visibleSize.height * 0.5);
	//background->setScale(AppDelegate::getResRate());
	this->addChild(background);

	//添加按钮
	auto playItem = MenuItemImage::create(
											"PLAY_btn.png",
											"PLAY_btn2.png",
											CC_CALLBACK_1(HelloWorld::menuPlayCallback,this));
	playItem->setPosition(Vec2(visibleSize.width * 0.8,visibleSize.height * 0.2));
	auto menu = Menu::create(playItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,1);

	//添加heart动画
	Sprite *pSprite;
	SpriteFrameCache *cache;
	cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("ani.plist","ani.png");
	//auto *animFrames = new Vector();
	Vector<SpriteFrame*> animFrames;
	SpriteFrame *frame = cache->getSpriteFrameByName("heart_0.png");
	animFrames.pushBack(frame);
	frame = cache->getSpriteFrameByName("heart_1.png");
	animFrames.pushBack(frame);
	frame = cache->spriteFrameByName("heart_3.png"); 
	animFrames.pushBack(frame);
	frame = cache->spriteFrameByName("heart_2.png"); 
	animFrames.pushBack(frame);
	frame = cache->spriteFrameByName("heart_4.png"); 
	animFrames.pushBack(frame);
	frame = cache->spriteFrameByName("heart_5.png"); 
	animFrames.pushBack(frame);
	frame = cache->spriteFrameByName("heart_6.png"); 
	animFrames.pushBack(frame);
	Animation *animation = Animation::createWithSpriteFrames(animFrames,0.3f);
	pSprite = Sprite::createWithSpriteFrameName("heart_0.png");
	this->addChild(pSprite,80);
	pSprite->setPosition(ccp(visibleSize.width*0.4, visibleSize.height*0.6));
	pSprite->runAction(RepeatForever::create(Animate::create(animation)));

	/*
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
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

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
	*/
    
    return true;
}

void HelloWorld::menuPlayCallback(Ref* pSender)
{
	log("replaceScene(ShelfScene::CreateScene())");
	Director::getInstance()->replaceScene(ShelfScene::CreateScene());
}

/*
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
*/