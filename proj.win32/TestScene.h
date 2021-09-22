#pragma once

#include <cocos2d.h>
#include <spine/spine-cocos2dx.h>
#include <ui/CocosGUI.h>

#include "Hero.h"

using namespace std;
using namespace cocos2d;


class TestScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    CREATE_FUNC(TestScene);

private:
    ui::Button* createButton(const string& title, HeroInput input, float scale);

    Hero* hero;
};
