#ifndef __MMENU_SCENE_H__
#define __MMENU_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuPlayCallback(Ref* pSender);

    CREATE_FUNC(MainMenu);
};

#endif