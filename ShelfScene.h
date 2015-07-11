#ifndef _SHELF_SCENE_H_
#define _SHELF_SCENE_H_

#include "cocos2d.h"
USING_NS_CC;
class ShelfScene : public Layer
{
public:
	ShelfScene();
	~ShelfScene();

	virtual bool init();
	static Scene* CreateScene();

	CREATE_FUNC(ShelfScene);

protected:
	void GoToBook(Ref* pSender);
private:
	int currentBookId;
};

#endif