#pragma once

#include <cocos2d.h>
#include <spine/spine-cocos2dx.h>

#include "Hero.h"

using namespace cocos2d;
using namespace spine;

class Hero;
enum class HeroInput;

class HeroState {
public:
	virtual ~HeroState() {}
	virtual HeroState* changeState(Hero* hero, HeroInput input) = 0;
	virtual void entryState(Hero* hero, const Vec2& data = Vec2()) = 0;
};


class idleState : public HeroState {
public:
	idleState() {}
	virtual ~idleState() override {}
	virtual HeroState* changeState(Hero* hero, HeroInput input) override;
	virtual void entryState(Hero* hero, const Vec2& data = Vec2()) override;
};


class attackState : public HeroState {
public:
	attackState() {}
	virtual ~attackState() override {}
	virtual HeroState* changeState(Hero* hero, HeroInput input) override;
	virtual void entryState(Hero* hero, const Vec2& data = Vec2()) override;
};


class moveState : public HeroState {
public:
	moveState() {}
	virtual ~moveState() override {}
	virtual HeroState* changeState(Hero* hero, HeroInput input) override;
	virtual void entryState(Hero* hero, const Vec2& data = Vec2()) override;
};

