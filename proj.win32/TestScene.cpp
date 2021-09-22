#include "TestScene.h"


#define DFLT_BTN_NORMAL		"assets/button.png"
#define DFLT_BTN_SELECTED	"assets/buttonSelected.png"
#define DFLT_BTN_SCALE		0.5f

#define DFLT_CHAR_JSON		"assets/hero_2.json"
#define DFLT_CHAR_ATLAS		"assets/hero_2.atlas"
#define DFLT_CHAR_SCALE		2.0f



Scene* TestScene::createScene() {
	return TestScene::create();
}


bool TestScene::init()
{
	if (!Scene::init()) {
		return false;
	}
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	// BUTTONS /////////////////////////////////////////////////////
	auto btnAttack = createButton("ATTACK", HeroInput::INPUT_ATTACK, DFLT_BTN_SCALE);
	float btnPosX = origin.x + DFLT_BTN_SCALE * btnAttack->getContentSize().width / 2;
	float btnPosY = origin.y + visibleSize.height - DFLT_BTN_SCALE * btnAttack->getContentSize().height / 2;
	btnAttack->setPosition(Vec2(btnPosX, btnPosY));
	this->addChild(btnAttack, 2);

	auto btnStop = createButton("STOP", HeroInput::INPUT_STOP, DFLT_BTN_SCALE);
	btnPosX += DFLT_BTN_SCALE*btnStop->getContentSize().width;
	btnStop->setPosition(Vec2(btnPosX, btnPosY));
	this->addChild(btnStop, 2);

	// HERO NODE /////////////////////////////////////////////////////
	try {
		hero = new Hero(DFLT_CHAR_JSON, DFLT_CHAR_ATLAS, DFLT_CHAR_SCALE);
		auto skeletonNode = hero->getNode();
		skeletonNode->setPosition(ccp(visibleSize.width / 2, skeletonNode->getContentSize().height));
		this->addChild(skeletonNode, 1);
	}
	catch (const std::exception& except) {
		log(except.what());
		ccMessageBox(except.what(), "Exception thrown");
		Director::getInstance()->end();
	}
	catch (...) {
		log("Something unexpected. Program will be quit.");
		ccMessageBox("Something unexpected. Program will be quit.", "Exception thrown");
		Director::getInstance()->end();
	}
	
	// LISTENER /////////////////////////////////////////////////////
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event) { return true; };
	listener->onTouchMoved = [&](Touch* touch, Event* event) { return true; };
	listener->onTouchEnded = [&](Touch* touch, Event* event) { hero->handleInput(HeroInput::INPUT_MOVE, touch->getLocation()); return true; };
	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

	return true;
}



ui::Button* TestScene::createButton(const string& title, HeroInput input, float scale) {
	auto button = ui::Button::create(DFLT_BTN_NORMAL, DFLT_BTN_SELECTED);
	button->setTitleText(title);
	button->setTitleFontSize(36);
	button->setScale(scale);
	button->setTouchEnabled(true);
	button->setSwallowTouches(true);

	button->addTouchEventListener([this, input](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
			hero->handleInput(input);
	});

	return button;
}
