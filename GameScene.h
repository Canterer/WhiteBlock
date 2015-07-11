#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
USING_NS_CC;

class GameScene : public Layer
{
public:
	GameScene();
	~GameScene();

	virtual bool init();

	static Scene* CreateScene();

public:
	void NextScene(Ref* pSender);
	void ForwardScene(Ref* pSender);

private:
	int SoundId;


	CREATE_FUNC(GameScene);
};



#endif