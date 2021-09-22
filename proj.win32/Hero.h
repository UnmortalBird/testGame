#pragma once

#include <cocos2d.h>
#include <spine/spine-cocos2dx.h>
#include "HeroState.h"

using namespace cocos2d;

class HeroState;

enum class HeroInput {
	INPUT_STOP		= 0,
	INPUT_MOVE		= 1,
	INPUT_ATTACK	= 2,
	INPUT_TELEPORT	= 3,
	INPUT_GRENADE	= 4,
	INPUT_KRIT		= 5,
	INPUT_SUMMON	= 6,
	INPUT_DEATH		= 7
};


class Hero {
public:
	Hero(const std::string& skeletonJsonFile, const std::string& atlasFile, float scale);
	~Hero();

	virtual void handleInput(HeroInput input, const Vec2& data = Vec2());
	virtual spine::SkeletonAnimation* getNode();

private:
	HeroState* m_pState;
	spine::SkeletonAnimation* m_pSkeletonNode;
};


