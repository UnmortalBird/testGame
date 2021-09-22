#include "HeroState.h"


HeroState* idleState::changeState(Hero* hero, HeroInput input) {
	if (input == HeroInput::INPUT_MOVE) {
		return new moveState();
	}
	else if (input == HeroInput::INPUT_ATTACK) {
		return new attackState();
	}
	return nullptr;
}


void idleState::entryState(Hero* hero, const Vec2& data) {
	SkeletonAnimation* skeletonNode = hero->getNode();
	skeletonNode->stopAllActions();
	skeletonNode->setAnimation(0, "idle", true);
}


///////////////////////////////////////////////////////////////////////////

HeroState* moveState::changeState(Hero* hero, HeroInput input) {
	if (input == HeroInput::INPUT_MOVE) {
		return new moveState();
	} else if (input == HeroInput::INPUT_STOP) {
		return new idleState();
	}
	else if (input == HeroInput::INPUT_ATTACK) {
		return new attackState();
	}
	return nullptr;
}


void moveState::entryState(Hero* hero, const Vec2& data) {
	SkeletonAnimation* skeletonNode = hero->getNode();
	skeletonNode->stopAllActions();

	float pathX = data.x - skeletonNode->getPosition().x;
	float pathY = data.y - skeletonNode->getPosition().y;

	if (pathX > 0)
		skeletonNode->setScaleX(-1.0);
	else
		skeletonNode->setScaleX(1.0);

	float path = sqrt(pathX * pathX + pathY * pathY);
	float speed = 400.0f;									// per sec
	float time = std::abs(path / speed);
	skeletonNode->setAnimation(0, "move", true);
	
	auto moving = MoveBy::create(time, Vec2(pathX, pathY));
	
	auto callback = CallFunc::create([hero, data]() {
		hero->handleInput(HeroInput::INPUT_STOP, data);	}	);
	
	auto seq = Sequence::create(moving, callback, nullptr);
	skeletonNode->runAction(seq);
}


///////////////////////////////////////////////////////////////////////////
HeroState* attackState::changeState(Hero* hero, HeroInput input) {
	if (input == HeroInput::INPUT_STOP) {
		return new idleState();
	}
	if (input == HeroInput::INPUT_MOVE) {
		return new moveState();
	}
	return nullptr;
}


void attackState::entryState(Hero* hero, const Vec2& data) {
	SkeletonAnimation* skeletonNode = hero->getNode();
	skeletonNode->stopAllActions();
	skeletonNode->setAnimation(0, "attack", true);
}
