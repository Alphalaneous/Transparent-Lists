#include <Geode/Geode.hpp>
#include <Geode/modify/GJListLayer.hpp>
#include <Geode/modify/LevelCell.hpp>
#include <Geode/modify/LevelListCell.hpp>
#include <Geode/modify/GJScoreCell.hpp>
#include <Geode/modify/MapPackCell.hpp>

using namespace geode::prelude;

class $modify(GJListLayer) {

	static GJListLayer* create(BoomListView* p0, char const* p1, cocos2d::ccColor4B p2, float p3, float p4, int p5) {
		auto ret = GJListLayer::create(p0, p1, p2, p3, p4, p5);
		
		if(ret->getColor() == ccColor3B{191,114,62}){
			ret->setColor({0,0,0});
			ret->setOpacity(50.0f);
		}

		return ret;
	}
};

#define makeTransparent(class, method, paramType) \
struct My##class : geode::Modify<My##class, class> { \
	struct Fields {\
		ccColor3B m_lastBG;\
	};\
	void method(paramType* p0){\
		class::method(p0);\
		this->schedule(schedule_selector(My##class::checkBG));\
	}\
	void checkBG(float dt) {\
		CCLayerColor* child = this->getChildByType<CCLayerColor>(0);\
		if(child){\
			if(m_fields->m_lastBG != child->getColor()){\
				m_fields->m_lastBG = child->getColor();\
				if(child->getColor() == ccColor3B{161,88,44}){\
					child->setColor({0,0,0});\
				}\
				else if(child->getColor() == ccColor3B{194,114,62}){\
					child->setColor({80,80,80});\
				}\
				child->setOpacity(50.0f);\
			}\
		}\
	}\
};

makeTransparent(LevelCell, loadFromLevel, GJGameLevel);
makeTransparent(LevelListCell, loadFromList, GJLevelList);
makeTransparent(GJScoreCell, loadFromScore, GJUserScore);
makeTransparent(MapPackCell, loadFromMapPack, GJMapPack);

