#include "ShelfScene.h"

ShelfScene::ShelfScene(){}
ShelfScene::~ShelfScene(){}
bool ShelfScene::init()
{
	
	bool ret = false;
	do
	{
		if( !Layer::init() )
		{
			break;
		}
		log("ShelfScene::init()");

		auto visibleSize = Director::getInstance()->getVisibleSize();

		//按钮的载入 
		//String* pString = String::createWithFormat("shelf.plist");
		auto plistDic = Dictionary::createWithContentsOfFile("shelf.plist");
		auto Dic = (Dictionary*)plistDic->objectForKey("button");

		//Vector<String*> picture_vector;
		//picture_vector = (Vector<String*>)Dic->objectForKey("button_img");
		//Vector <String*> point_vector;
		//Vector <String*> BookId_vector;

		//字典里的数据 好像 必须得 Array 取出
		Array* picture_array = (Array*)Dic->objectForKey("button_img");
		Array* point_array = (Array*)Dic->objectForKey("button_pos");
		Array* BookId_array = (Array*)Dic->objectForKey("button_fun");

		//auto btn_sprite = Sprite::create(((String*)picture_array->getObjectAtIndex(0))->getCString());
		//Sprite* btn_sprite = Sprite::create("stort_1.png");   //资源路径  读取不到
		//btn_sprite->setPosition(visibleSize.width,visibleSize.height);
		//this->addChild(btn_sprite,0);

		for(int i = 0; i < picture_array->count(); i++)
		{
			String* picture_string = (String*)picture_array->objectAtIndex(i);
			auto btn_sprite = Sprite::create(picture_string->getCString());
			auto point_string = (String*)point_array->objectAtIndex(i);
			auto point = PointFromString(point_string->getCString());
			//auto BookId_string = (String*)BookId_array->objectAtIndex(i);
			//int BookId = BookId_string->intValue();//获取BookId

			auto menuItem= MenuItemSprite::create(btn_sprite,btn_sprite,NULL,this,menu_selector(ShelfScene::GoToBook));
			menuItem->setPosition(visibleSize.width * point.x,visibleSize.height * point.y);
			
			auto menu = Menu::createWithItem(menuItem);
			menu->setPosition(Size::ZERO);			
			//menu->setPosition(visibleSize.width * point.x,visibleSize.height * point.y);
			//menu->setTouchEnabled(true);  //??
			addChild(menu,60);
		}
		//图片的载入
		picture_array = (Array*)plistDic->objectForKey("picture");
		point_array = (Array*)plistDic->objectForKey("point");
		for(int i =0; i<picture_array->count();i++)
		{
			auto picture_string = (String*)picture_array->objectAtIndex(i);
			auto sprite = Sprite::create(picture_string->getCString());

			auto point_string = (String*)point_array->objectAtIndex(i);
			auto point = PointFromString(point_string->getCString());

			sprite->setPosition(Vec2(visibleSize.width*point.x,visibleSize.height*point.y));
			//sprite->setScale(AppDelegate::getResRate());
			addChild(sprite,0);
		}



		//动画载入
		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("gameart.plist","gameart.png");
		Dic = (Dictionary*)plistDic->objectForKey("animation");
		picture_array = (Array*)Dic->objectForKey("ani_img");
		Vector<SpriteFrame*> animFrames;
		//auto animFrames = Array::createWithCapacity(picture_array->count());
		for(int i = 0;i < picture_array->count();i++)
		{
			auto picture_string = (String*)picture_array->objectAtIndex(i);
			auto frame = cache->spriteFrameByName(picture_string->getCString());
			//animFrames->addObject(frame);
			animFrames.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(animFrames,0.1f);
		String* picture_string = (String*)picture_array->objectAtIndex(0);
		auto pSprite = Sprite::createWithSpriteFrameName(picture_string->getCString());
		addChild(pSprite,20);
		pSprite->setPosition(visibleSize.width*0.8,visibleSize.height*0.15);
		pSprite->runAction(RepeatForever::create(Animate::create(animation)));

		auto MoveToM = MoveTo::create(1.0f,Vec2(visibleSize.width*0.5,visibleSize.height*0.15));
		auto waiting = DelayTime::create(1);
		auto MoveToL = MoveTo::create(1.0f,Vec2(visibleSize.width*0.2,visibleSize.height*0.15));
		auto fx = FlipX::create(true);
		auto MoveToR = MoveTo::create(1.0f,Vec2(visibleSize.width*0.8,visibleSize.height*0.15));
		auto fx1 = FlipX::create(false);

		auto action = Sequence::create(MoveToM,waiting,MoveToL,fx,MoveToM,waiting,MoveToR,fx1,NULL);
		pSprite->runAction(RepeatForever::create(action));

			//setTouchEnabled(false);
		
		ret = true;
	}while(0);

	return ret;
}

Scene* ShelfScene::CreateScene()
{
	Scene* scene = NULL;
	do
	{
		// 'scene' is an autorelease object
		scene = Scene::create();
		CC_BREAK_IF( !scene);
		ShelfScene *layer = ShelfScene::create();
		CC_BREAK_IF(!layer);
		scene->addChild(layer);

	}while(0);
	return scene;

	/*auto scene = Scene::create();
	auto layer = ShelfScene::create();
	scene->addChild(layer);
	return scene;*/

}

void ShelfScene::GoToBook(Ref *pSender)
{
	log("GoToBook");
	//Director::getInstance()->replaceScene(TransitionJumpZoom::create(1,GameSceme::CreateScene()));
}