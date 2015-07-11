#include "GameScene.h"
#include "ShelfScene.h"
//#include "EndStory.h"

static int SceneNumber = 0;
const int PageNumber = 15;

GameScene::GameScene()
{

}
GameScene::~GameScene()
{

}

bool GameScene::init()
{
	bool ret = false;
	do
	{
		if( ! Layer::init() )
		{
			break;
		}
		String *pString,*SoundString;
		auto visibleSize = Director::getInstance()->getVisibleSize();

		pString = String::createWithFormat("story\\sceneOrder\\scene%d.plist",SceneNumber);
		//  由于 '\'为转义字符 ，所以"\\"实际输出为"\"
		//Dictionary* plistDic = Dictionary::createWithContentsOfFile("H:\Cocos2dx-workspace\TellAStory\Resources\story\sceneOrder\scene0.plist");
		log(pString->getCString());
		//sprintf("story\sceneOrder\scene%d.plist",SceneNumber)
		auto plistDic = Dictionary::createWithContentsOfFile(pString->getCString());
		//plistDic未初始化

		Array* picture_array = (Array*)plistDic->objectForKey("picture");
		Array* point_array = (Array*)plistDic->objectForKey("point");
		//log(picture_array->capacity());
		for(int i = 0; i < picture_array->count();i++)
		{
			auto picture_string = (String*)picture_array->objectAtIndex(i);
			auto sprite = Sprite::create(picture_string->getCString());
			auto point_string = (String*)point_array->objectAtIndex(i);
			auto point = PointFromString(point_string->getCString());

			sprite->setPosition(Vec2(visibleSize.width*point.x,visibleSize.height*point.y));
			//sprite->setScale(AppDelegate::getResRate());
			addChild(sprite,1);
		}

		//next button
		auto normalSprite = Sprite::create("play_next.png");
		auto selectedSprite = Sprite::create("play_next2.png");
		auto menuItemSprite = MenuItemSprite::create(normalSprite,selectedSprite,NULL,menu_selector(GameScene::NextScene));
		auto menu = Menu::createWithItem(menuItemSprite);
		//menu->setPosition(Size::ZERO);
		menu->setPosition(Vec2(visibleSize.width*0.1,visibleSize.height*0.8));
		//menu->setTouchEnabled(true);
		addChild(menu,10);

		if(SceneNumber != 0)
		{
			//Forward button
			normalSprite = Sprite::create("play_forward.png");
			selectedSprite = Sprite::create("play_forward2.png");
			menuItemSprite = MenuItemSprite::create(normalSprite,selectedSprite,NULL,menu_selector(GameScene::ForwardScene));
			menuItemSprite->setPosition(Vec2(visibleSize.width*0.05,visibleSize.height*0.2));
			menu = Menu::createWithItem(menuItemSprite);
			menu->setPosition(Size::ZERO);
			//menu->setTouchEnabled(true);
			addChild(menu,10);
		}
		//setTouchEnabled(false);

	ret = true;
	}while(0);
	return ret;
}

Scene* GameScene::CreateScene()
{
	/*auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;*/
	Scene * scene = NULL;
	do 
	{
		scene = Scene::create();
		CC_BREAK_IF(! scene);

		GameScene *layer = GameScene::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);
	return scene;
}

void GameScene::NextScene(Ref* pSender)
{
	log("NextScene");
	if(SceneNumber >= PageNumber)
	{
		SceneNumber = 0;
		//Director::getInstance()->replaceScene(TransitionJumpZoom::create(1,EndStory::CreateScene()));
	}
	else if(SceneNumber >= 0)
	{
		SceneNumber ++;
		auto transitionFade = TransitionFade::create(1,GameScene::CreateScene());
		Director::getInstance()->replaceScene(transitionFade);
	}
}

void GameScene::ForwardScene(Ref* pSender)
{
	log("ForwardScene");
	if(SceneNumber < 0)
	{
		SceneNumber = 0;
		Director::getInstance()->replaceScene(TransitionShrinkGrow::create(1,ShelfScene::CreateScene()));
	}
	else if(SceneNumber <= PageNumber)
	{
		SceneNumber --;
		Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::CreateScene()));
	}
}