#include "MainMenu.h"
#include "level_1.h"

#include "AudioEngine.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

bool MainMenu::init()
{
    if (!Scene::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create("menu/exit.png", "menu/exit_s.png", CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
    closeItem->setPosition(visibleSize.width/2, 2*visibleSize.height/10);

    auto play = MenuItemImage::create("menu/play.png", "menu/play_s.png", CC_CALLBACK_1(MainMenu::menuPlayCallback, this));
    play->setPosition(visibleSize.width / 2, 4 * visibleSize.height / 10);


    auto menu = Menu::create(closeItem, play, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    auto bg = Sprite::create("menu/background.png");
    bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(0 , 0);
    this->addChild(bg, 0);

    auto logo = Sprite::create("menu/LOGO.png");
    float ls = .5 * visibleSize.width / logo->getContentSize().width;
    logo->setScale(ls, ls);
    logo->setPosition(visibleSize.width/2, 3*visibleSize.height/4);
    this->addChild(logo, 0);

    AudioEngine::preload("audio/music/la_grange.mp3");

    AudioEngine::preload("audio/misc/barrel.mp3");
    AudioEngine::preload("audio/misc/door_open.mp3");
    AudioEngine::preload("audio/misc/target.mp3");

    AudioEngine::preload("audio/weapon/punch.mp3");
    AudioEngine::preload("audio/weapon/punch_fail.mp3");
    AudioEngine::preload("audio/weapon/pistol.mp3");
    AudioEngine::preload("audio/weapon/shotgun.mp3");

    AudioEngine::preload("audio/item/item.mp3");
    AudioEngine::preload("audio/item/weaon.mp3");

    AudioEngine::preload("audio/monster/zombie_near.mp3");
    AudioEngine::preload("audio/monster/zombie_hurt.mp3");
    AudioEngine::preload("audio/monster/zombie_near.mp3");
    AudioEngine::preload("audio/monster/imp_death.mp3");
    AudioEngine::preload("audio/monster/imp_hurt.mp3");
    AudioEngine::preload("audio/monster/imp_attack.mp3");
    AudioEngine::preload("audio/monster/impp_explode.mp3");
    AudioEngine::preload("audio/monster/cacodemon_hurt.mp3");
    AudioEngine::preload("audio/monster/cacodemon_death.mp3");
    AudioEngine::preload("audio/monster/cacodemon_attack.mp3");
    AudioEngine::preload("audio/monster/cproj_explode.mp3");

    AudioEngine::preload("audio/player/hurt .mp3");
    AudioEngine::preload("audio/player/death.mp3");

    AudioEngine::setMaxAudioInstance(30);
    int music_id = AudioEngine::play2d("audio/music/la_grange.mp3", 0, .6);
    AudioEngine::setFinishCallback(music_id, [](int id, const std::string& s) {
        int music_id = AudioEngine::play2d("audio/music/enemy.mp3", 0, .6);
        AudioEngine::setFinishCallback(music_id, [](int id, const std::string& s) {
            AudioEngine::play2d("audio/music/running_from_evil.mp3", 0, .6);
        });
    });

    return true;
}


void MainMenu::menuCloseCallback(Ref* pSender){
    Director::getInstance()->end();

    AudioEngine::play2d("audio/item/item.mp3");
}

void MainMenu::menuPlayCallback(Ref* pSender) {
    Director::getInstance()->replaceScene(level_1::create());

    AudioEngine::play2d("audio/item/item.mp3");

}
