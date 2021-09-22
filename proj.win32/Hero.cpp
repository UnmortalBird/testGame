#include "Hero.h"


Hero::Hero(const std::string& skeletonJsonFile, const std::string& atlasFile, float scale)	{
	try {
		m_pSkeletonNode = spine::SkeletonAnimation::createWithJsonFile(skeletonJsonFile, atlasFile, scale);
		m_pState = new idleState();
		m_pState->entryState(this);
	}	catch (const std::exception& except)	{
		throw except;
	}
	catch (...) {
		throw std::exception("Something unexpected. Program will be quit.");
	}
}


Hero::~Hero() {
	if (m_pState != nullptr)
		delete m_pState;
}


void Hero::handleInput(HeroInput input, const cocos2d::Vec2& data) {
	HeroState* state = m_pState->changeState(this, input);
	if (state != nullptr) {
		delete m_pState;
		m_pState = state;
		state->entryState(this, data);
	}
}


spine::SkeletonAnimation* Hero::getNode() {
	return m_pSkeletonNode;
}